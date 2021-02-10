#ifndef GAMEPLAYFACADE_H
#define GAMEPLAYFACADE_H

class Player;
class Board;
class IBoard;

#include <memory>
#include <QObject>
#include <QList>
#include <QVariant>

#include "../Defines.h"
#include "../Interfaces/singleton.h"
#include "../Interfaces/iserializable.h"

class GameplayFacade : public QObject, public Singleton<GameplayFacade>, public ISerializable
{
    Q_OBJECT
    friend class Singleton<GameplayFacade>;

    QList<std::shared_ptr<Player>>          _playerStack;
    std::shared_ptr<Board>                  _board;
    QList<Defs::MovePrimitive>              _moveHistory;

    explicit GameplayFacade();
public:

    std::shared_ptr<Player> currentPlayer();

    void nextPlayer();

    void addHumanPlayer(Defs::EColors playerColor);

    std::shared_ptr<Player> addPlayer( Defs::EPlayers playerType, Defs::EColors playerColor);

    std::shared_ptr<IBoard> GetBoard() const;

    void Reset();

    bool start();

    void setBoardToState(int index);

signals:
    void signalCheckForPlayer(Defs::EColors player);

    void signalBoardChanged(std::shared_ptr<IBoard>);

    void signalNextPlayer(std::shared_ptr<Player>);

public slots:
    void slotMove(QVariant variant);

protected:
    Defs::Move construct(Defs::MovePrimitive& m);

    // ISerializable interface
public:
    QString SaveState() override;
    void LoadState(QString state) override;
};

#endif // GAMEPLAYFACADE_H
