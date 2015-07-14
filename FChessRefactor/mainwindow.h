#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include "board.h"
#include "Visual/display.h"

namespace Ui {
class MainWindow;
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
    void slotActualizeGUI();

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

protected:
    virtual void closeEvent( QCloseEvent * );

    void makeConnections();

    void addPlayerAction( QString& action, QMenu* menu, QActionGroup* agroup );

private:
    Ui::MainWindow *ui;

    chessVisialization::Display* _display;

    //Board*          _chessBoard;
};

#endif // MAINWINDOW_H
