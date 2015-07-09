#include <iostream>
#include <QHBoxLayout>
#include <QListWidget>
#include <QTreeWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Players/human.h"
#include "exceptions.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    ,_display(0)
    ,_chessBoard(0)
{
    ui->setupUi(this);
    setWindowTitle( QString( "FChess %1").arg(RELEASE_VERSION) );

    //***********************************
    QMenu* whiteplayers = new QMenu( "White", ui->menuPlayers );
    QActionGroup* agroup = new QActionGroup( whiteplayers );
    ui->menuPlayers->addMenu( whiteplayers );
    addPlayerAction( QString( "Human" ), whiteplayers, agroup );
    addPlayerAction( QString( "Remote Human" ), whiteplayers, agroup );


    QMenu* blackplayers = new QMenu( "Black", ui->menuPlayers );
    QActionGroup* agroup2 = new QActionGroup( blackplayers );
    ui->menuPlayers->addMenu( blackplayers );
    addPlayerAction( QString( "Human" ), blackplayers, agroup2 );
    addPlayerAction( QString( "Remote Human" ), blackplayers, agroup2 );

    //***********************************

    _chessBoard = new Board();
    _chessBoard->setNumberOfPlayers( 2 );

    ui->boardPlaceholder->setMinimumSize( CELL_TEXTURE_W * HORIZONTAL_SIZE, CELL_TEXTURE_H * VERTICAL_SIZE);
    ui->boardPlaceholder->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );

    QHBoxLayout* layout = new QHBoxLayout;
    ui->boardPlaceholder->setLayout( layout );

    _display = new chessVisialization::Display( ui->boardPlaceholder );
    _display->setBoard( _chessBoard );
    _display->setMinimumSize( 10, 10 );
    _display->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

    layout->addWidget(_display);

    slotRefresh();
    makeConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makeConnections()
{
    connect( ui->actionStart,   SIGNAL( triggered() ),  this, SLOT( start() ) );
    connect( ui->actionExit,    SIGNAL( triggered() ),  qApp, SLOT( quit() ) );
    connect( ui->undoLastButton,SIGNAL( pressed() ),    this, SLOT( slotUndoLastMove() ) );

    connect( _display, SIGNAL( signalMessage( QString ) ),     SLOT( slotReceivedMessage( QString ) ) );

    connect( _chessBoard, SIGNAL( signalBoardChanged() ),           SLOT( slotRefresh() ) );
    connect( _chessBoard, SIGNAL( signalBoardChanged() ),  _display,SLOT( boardChanged() ) );
    connect( _chessBoard, SIGNAL( signalMessage( QString ) ),       SLOT( slotReceivedMessage( QString ) ) );
    connect( _chessBoard, SIGNAL( signalPlayerChanged() ),          SLOT( slotActualizeGUI() ) );
}

void MainWindow::addPlayerAction( QString& action, QMenu* menu, QActionGroup* agroup )
{
    QAction* act = menu->addAction(action);
    act->setCheckable(true);
    if ( agroup )
    {
        agroup->addAction( act );
    }
    connect( act, SIGNAL(triggered()), SLOT(slotSetupPlayer()) );
}

void MainWindow::slotRefresh()
{
    if ( _chessBoard->started() )
    {
        if ( !_chessBoard->stack().isEmpty() )
        {
            ui->undoLastButton->setEnabled( true );
			return;
        }
    }

    ui->undoLastButton->setEnabled( false );
}

void MainWindow::slotUndoLastMove()
{
    if ( _chessBoard->started() )
    {
        _chessBoard->revertStep();
        _display->boardChanged();
        _display->repaint();
    }
}

void MainWindow::slotSetupPlayer()
{
    int colorIndex = -1;
    try
    {
        QAction* sndr = dynamic_cast< QAction* >( sender() );
        if ( sndr )
        {
            QMenu* menu = dynamic_cast< QMenu* >( sndr->parent() );
            if ( menu )
            {
                if ( menu->title() == "White" )
                {
                    colorIndex = 0;
                    Player* player = PlayerFactory::instance()->createPlayer( Defs::White, sndr->text() );
                    _chessBoard->setPlayer( 0, player );
                    connect( player, SIGNAL( signalMessage( QString ) ),                  SLOT( slotReceivedMessage( QString ) ) );
                    connect( player, SIGNAL( signalCellPressed( int, int ) ), _chessBoard,SLOT( cellPressed(int,int) ) );
                    connect( player, SIGNAL( signalCellChanged( int, int) ),  _display,   SLOT( slotCellChanged( int, int ) ) );
                    connect( player, SIGNAL( signalEventFiltered() ),         _display,   SLOT( boardChanged() ) );
                }
                else if ( menu->title() == "Black" )
                {
                    Player* player = PlayerFactory::instance()->createPlayer( Defs::Black, sndr->text() );
                    colorIndex = 1;
                    _chessBoard->setPlayer( 1, player );
                    connect( player, SIGNAL( signalMessage( QString ) ),                  SLOT( slotReceivedMessage( QString ) ) );
                    connect( player, SIGNAL( signalCellPressed( int, int ) ), _chessBoard,SLOT( cellPressed(int,int) ) );
                    connect( player, SIGNAL( signalCellChanged( int, int) ),  _display,   SLOT( slotCellChanged( int, int ) ) );
                    connect( player, SIGNAL( signalEventFiltered() ),         _display,   SLOT( boardChanged() ) );
                }
            }
        }
    }
    catch ( NetworkException& nex )
    {
        std::cout << nex.what() << std::endl;
        _chessBoard->deletePlayer( colorIndex );
    }
    catch ( std::bad_alloc& allex )
    {
        //problem with memory allocation => quit
        std::cout << allex.what() << std::endl;
        QApplication::quit();
    }
    catch ( std::exception& ex )
    {
        //unidentified problem => quit
        std::cout << ex.what() << std::endl;
        QApplication::quit();
    }
}

void MainWindow::start( QAction* )
{
    QAction* sndrAction = dynamic_cast< QAction* >( sender() );
    if ( _chessBoard->start() && sndrAction )
    {
        sndrAction->setText("Restart");
        _display->installEventFilter( _chessBoard->currentPlayer() );
        _display->boardChanged();
		_display->update();
    }
}

void MainWindow::slotReceivedMessage( QString str )
{
    ui->logWindow->insertItem(0, str );
}

void MainWindow::init()
{
}

void MainWindow::slotActualizeGUI()
{
    Player* p = _chessBoard->currentPlayer();
    QString str;
    if ( p )
    {
        _display->installEventFilter( p );

        if ( p->color() == Defs::White )
        {
            str = "White";
        }
        else if ( p->color() == Defs::Black )
        {
            str = "Black";
        }
        else
        {
            str = "No Player";
        }
    }

    ui->currentPlayer->setText( str );
}

void MainWindow::closeEvent( QCloseEvent * )
{
    QApplication::quit();
}

