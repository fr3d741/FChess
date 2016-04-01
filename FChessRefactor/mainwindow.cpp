#include <iostream>
#include <QHBoxLayout>
#include <QListWidget>
#include <QTreeWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_newGameDialog.h"

#include "Players/human.h"
#include "exceptions.h"
#include "Factories/playerfactory.h"
#include "Factories/figurefactory.h"
#include "Interfaces/figure.h"
#include "Facade/gameplayfacade.h"
#include "Observers/gameplayobserver.h"
#include "Proxy/visualproxy.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    ,_dialogUi(new Ui::NewGameDialog)
    ,_display(0)
    ,_humanString("Human")
    ,_networkString("Network")
    ,_computerString("Computer")
{
    VisualProxy::CreateInstance(this);
    ui->setupUi(this);

    setWindowTitle( QString( "FChess %1").arg(RELEASE_VERSION) );

    //***********************************
//    QMenu* whiteplayers = new QMenu( "White", ui->menuPlayers );
//    QActionGroup* agroup = new QActionGroup( whiteplayers );
//    ui->menuPlayers->addMenu( whiteplayers );
//    addPlayerAction( QString( "Human" ), whiteplayers, agroup );
//    addPlayerAction( QString( "Remote Human" ), whiteplayers, agroup );


//    QMenu* blackplayers = new QMenu( "Black", ui->menuPlayers );
//    QActionGroup* agroup2 = new QActionGroup( blackplayers );
//    ui->menuPlayers->addMenu( blackplayers );
//    addPlayerAction( QString( "Human" ), blackplayers, agroup2 );
//    addPlayerAction( QString( "Remote Human" ), blackplayers, agroup2 );

    ui->boardPlaceholder->setMinimumSize( CELL_TEXTURE_W * HORIZONTAL_SIZE, CELL_TEXTURE_H * VERTICAL_SIZE);
    ui->boardPlaceholder->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );

    QHBoxLayout* layout = new QHBoxLayout;
    ui->boardPlaceholder->setLayout( layout );

    _display = new chessVisialization::Display( ui->boardPlaceholder );
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
    connect( GameplayObserver::Instance().get(), SIGNAL(signalPlayerChanged(std::shared_ptr<Player>)), SLOT(slotActualizeGUI(std::shared_ptr<Player>)) );
    connect( GameplayObserver::Instance().get(), SIGNAL(signalCheckForPlayer(Defs::EColors)), SLOT(slotCheck(Defs::EColors)));
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

QString MainWindow::stringify(Defs::Move &move)
{
    auto instance = puppets::FigureFactory::createFigure(nullptr, Defs::White, move.figure);
    QString txt = instance->notation();
    static std::vector<QString> letters{"a","b","c","d","e","f","g","h"};



return txt;
}

void MainWindow::slotRefresh()
{
//    if ( _chessBoard->started() )
//    {
//        if ( !_chessBoard->stack().isEmpty() )
//        {
//            ui->undoLastButton->setEnabled( true );
//			return;
//        }
//    }

    ui->undoLastButton->setEnabled( false );
}

void MainWindow::slotCheck(Defs::EColors player)
{
    ui->logWindow->addItem(QString("%1 player in Check!").arg(player==Defs::White?"White":"Black"));
}

void MainWindow::slotUndoLastMove()
{
//    if ( _chessBoard->started() )
//    {
//        _chessBoard->revertStep();
//        _display->boardChanged();
//        _display->repaint();
//    }
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
                    GameplayFacade::Instance()->addHumanPlayer(Defs::White);
                }
                else if ( menu->title() == "Black" )
                {
                    GameplayFacade::Instance()->addHumanPlayer(Defs::Black);
                }
            }
        }
    }
    catch ( NetworkException& nex )
    {
        std::cout << nex.what() << std::endl;
        //_chessBoard->deletePlayer( colorIndex );
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
    QDialog* startingDialog = new QDialog(this);
    _dialogUi->setupUi(startingDialog);
    SetupDialogUI();

    if (startingDialog->exec() != QDialog::Accepted)
        return;

    auto instance = GameplayFacade::Instance();
    instance->Reset();
    instance->addPlayer((Defs::EPlayers)_dialogUi->whitePlayerBox->currentIndex(), Defs::White);
    instance->addPlayer((Defs::EPlayers)_dialogUi->blackPlayerBox->currentIndex(), Defs::Black);

    if ( instance->start() && sndrAction )
    {
        sndrAction->setText("Restart");
        _display->installEventFilter( GameplayFacade::Instance()->currentPlayer().get() );
		_display->update();
    }
    startingDialog->deleteLater();
}

void MainWindow::slotReceivedMessage( QString str )
{
    ui->logWindow->insertItem(0, str );
}

void MainWindow::init()
{
}

void MainWindow::slotActualizeGUI(std::shared_ptr<Player> player)
{
    std::shared_ptr<Player> p = player;
    QString str;
    if ( p.get() )
    {
        _display->installEventFilter( p.get() );

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

void MainWindow::SetupDialogUI()
{
    _dialogUi->blackPlayerBox->addItem(_humanString);
    _dialogUi->blackPlayerBox->addItem(_networkString);
    _dialogUi->blackPlayerBox->addItem(_computerString);

    _dialogUi->whitePlayerBox->addItem(_humanString);
    _dialogUi->whitePlayerBox->addItem(_networkString);
    _dialogUi->whitePlayerBox->addItem(_computerString);
}
