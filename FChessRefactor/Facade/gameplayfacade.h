#ifndef GAMEPLAYFACADE_H
#define GAMEPLAYFACADE_H

class Player;
class Board;

#include <memory>
#include <QObject>
#include <QList>

#include "../Defines.h"

class GameplayFacade : public QObject
{
    Q_OBJECT

    static std::shared_ptr<GameplayFacade>  _instance;
    QList<std::shared_ptr<Player>>          _playerStack;
    Board*                                  _board;

    explicit GameplayFacade();
public:
    static std::shared_ptr<GameplayFacade> Instance();

    std::shared_ptr<Player> currentPlayer();

    void nextPlayer();

    void addHumanPlayer(Defs::EColors playerColor);

    Board* GetBoard() const;

    bool start();
signals:

public slots:

};

#endif // GAMEPLAYFACADE_H
