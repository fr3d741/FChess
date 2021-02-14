#include <iostream>
#include <QHBoxLayout>
#include <QListWidget>
#include <QTreeWidget>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_newGameDialog.h"

#include "Players/human.h"
#include "exceptions.h"
#include "Factories/playerfactory.h"
#include "Factories/figurefactory.h"
#include "Interfaces/figure.h"
#include "Interfaces/IBoard.h"
#include "Facade/gameplayfacade.h"
#include "Facade/uifacade.h"
#include "Observers/gameplayobserver.h"
#include "Observers/messenger.h"
#include "Proxy/visualproxy.h"


MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    ,_dialogUi(new Ui::NewGameDialog)
    ,_humanString("Human")
    ,_networkString("Network")
    ,_computerString("Computer")
{
    VisualProxy::CreateInstance(this);
    ui->setupUi(this);
    setWindowTitle( QString( "FChess %1").arg(RELEASE_VERSION) );

    //***********************************

    ui->boardPlaceholder->setMinimumSize( CELL_TEXTURE_W * HORIZONTAL_SIZE, CELL_TEXTURE_H * VERTICAL_SIZE);
    ui->boardPlaceholder->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );

    QHBoxLayout* layout = new QHBoxLayout;
    ui->boardPlaceholder->setLayout( layout );

    QWidget* _display = UiFacade::Instance()->CreateDisplayWidget(ui->boardPlaceholder);

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
    connect( ui->moveHistoryWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*) ), this, SLOT( slotSetState(QListWidgetItem*) ) );


    connect( Messenger::Instance().get(), SIGNAL(signalMessageToGUI(QString)), SLOT(slotReceivedMessage(QString)));
    connect( GameplayObserver::Instance().get(), SIGNAL(signalPlayerChanged(std::shared_ptr<Player>)), SLOT(slotActualizeGUI(std::shared_ptr<Player>)) );
    connect( GameplayObserver::Instance().get(), SIGNAL(signalCheckForPlayer(Defs::EColors)), SLOT(slotCheck(Defs::EColors)));
    connect( GameplayFacade::Instance().get(), SIGNAL(signalValidMove(QVariant)), SLOT(slotMove(QVariant)));
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
    ui->undoLastButton->setEnabled( false );
}

void MainWindow::slotCheck(Defs::EColors player)
{
    ui->logWindow->addItem(QString("%1 player in Check!").arg(player==Defs::White?"White":"Black"));
}

void MainWindow::slotMove(QVariant data) 
{
  Defs::MovePrimitive m = data.value<Defs::MovePrimitive>();
  auto msg = QString("Moved [%1, %2] -> [%3, %4]").arg(m.from.x).arg(m.from.y).arg(m.to.x).arg(m.to.x);
  auto item = new QListWidgetItem(msg);
  item->setData(Qt::UserRole, QVariant(ui->moveHistoryWidget->count()));
  ui->moveHistoryWidget->addItem(item);
  ui->moveHistoryWidget->scrollToBottom();
}

void MainWindow::slotSetState(QListWidgetItem* item) 
{
  auto index = item->data(Qt::UserRole).toInt();;
  GameplayFacade::Instance()->setBoardToState(index);
  for (int i = ui->moveHistoryWidget->count() - 1; index < i; --i) {
    delete ui->moveHistoryWidget->takeItem(i);
  }
  UiFacade::Instance()->UpdateUi();
}

void MainWindow::slotUndoLastMove()
{
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
        ui->actionRestart->setEnabled(true);
        UiFacade::Instance()->NextPlayer(GameplayFacade::Instance()->currentPlayer());
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
        UiFacade::Instance()->NextPlayer(p);

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
    _dialogUi->blackPlayerBox->addItem(_computerString);
    _dialogUi->blackPlayerBox->addItem(_networkString);

    _dialogUi->whitePlayerBox->addItem(_humanString);
    _dialogUi->whitePlayerBox->addItem(_computerString);
    _dialogUi->whitePlayerBox->addItem(_networkString);

    _dialogUi->strategyBoxBlack->addItem("Random");
    _dialogUi->strategyBoxBlack->addItem("MinMax");
    _dialogUi->strategyBoxWhite->addItem("Random");
    _dialogUi->strategyBoxWhite->addItem("MinMax");
}

void MainWindow::on_actionRestart_triggered()
{
    auto instance = GameplayFacade::Instance();
    instance->start();
    UiFacade::Instance()->UpdateUi();
}

void MainWindow::on_actionRotate_Right_triggered()
{
}

void MainWindow::on_actionRotate_Left_triggered()
{

}

void MainWindow::on_actionSave_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, "", ".");
    QFile output(file);
    QTextStream stream(&output);
    output.open(QIODevice::WriteOnly);

    if (!output.isOpen())
        return;

    auto instance = GameplayFacade::Instance();
    QString state = instance->SaveState();
    stream << state;
}

void MainWindow::on_actionLoad_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, "Select the file for load", ".");
    QFile input(file);
    input.open(QIODevice::ReadOnly);

    QTextStream stream(&input);

    QString content = stream.readAll();
    auto instance = GameplayFacade::Instance();
    instance->LoadState(content);
}
