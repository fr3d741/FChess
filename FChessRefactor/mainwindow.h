#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QActionGroup>

#include "Defines.h"
#include "Interfaces/player.h"

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

    void slotMove(QVariant data);

protected:
    virtual void closeEvent( QCloseEvent * );

    void makeConnections();

    QString stringify(Defs::Move& move);

private slots:
    void on_actionRestart_triggered();

    void on_actionRotate_Right_triggered();

    void on_actionRotate_Left_triggered();

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

private:
    void SetupDialogUI();

private:
    Ui::MainWindow *ui;
    Ui::NewGameDialog* _dialogUi;

    QString _humanString;
    QString _networkString;
    QString _computerString;
};

#endif // MAINWINDOW_H
