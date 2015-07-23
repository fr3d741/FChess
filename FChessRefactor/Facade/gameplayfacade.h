#ifndef GAMEPLAYFACADE_H
#define GAMEPLAYFACADE_H

class Player;
class Board;

#include <memory>
#include <QObject>
#include <QList>
#include <QVariant>

#include "../Defines.h"
#include "../Interfaces/singleton.h"

class GameplayFacade : public QObject, public Singleton<GameplayFacade>
{
    friend class Singleton<GameplayFacade>;
    Q_OBJECT

    QList<std::shared_ptr<Player>>          _playerStack;
    std::shared_ptr<Board>                  _board;

    explicit GameplayFacade();
public:

    std::shared_ptr<Player> currentPlayer();

    void nextPlayer();

    void addHumanPlayer(Defs::EColors playerColor);

    std::shared_ptr<Board> GetBoard() const;

    bool start();
signals:
    void signalBoardChanged(std::shared_ptr<Board>);

    void signalNextPlayer();

public slots:
    void slotMove(QVariant variant);

protected:

};

#endif // GAMEPLAYFACADE_H
