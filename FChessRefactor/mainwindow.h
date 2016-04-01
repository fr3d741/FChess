#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include "board.h"
#include "Visual/display.h"

namespace Ui {
class MainWindow;
class NewGameDialog;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
    
public slots:
    /*!
    * \brief sets new player to the board
    */
    void slotSetupPlayer();

    /*!
    * \brief handles message coming from classes
    */
    void slotReceivedMessage( QString );

    /*!
    * \brief refreshes GUI elements
    */
    void slotActualizeGUI(std::shared_ptr<Player> player);

    void init();

    /*!
    * \brief starts the game
    */
    void start( QAction* action = 0);

    /*!
    * \brief reverts last move
    */
    void slotUndoLastMove();

    /*!
    * \brief refreshes GUI elements
    */
    void slotRefresh();

    void slotCheck(Defs::EColors player);

protected:
    virtual void closeEvent( QCloseEvent * );

    void makeConnections();

    void addPlayerAction( QString& action, QMenu* menu, QActionGroup* agroup );

    QString stringify(Defs::Move& move);

private:
    void SetupDialogUI();

private:
    Ui::MainWindow *ui;
    Ui::NewGameDialog* _dialogUi;
    chessVisialization::Display* _display;

    QString _humanString;
    QString _networkString;
    QString _computerString;
};

#endif // MAINWINDOW_H
