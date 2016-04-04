#ifndef GAMEPLAYOBSERVER_H
#define GAMEPLAYOBSERVER_H

class IBoard;
class Player;

#include <memory>
#include <QObject>
#include <QVariant>

#include "../Interfaces/singleton.h"
#include "../Defines.h"

class GameplayObserver : public QObject, public Singleton<GameplayObserver>
{
    friend class Singleton<GameplayObserver>;
    Q_OBJECT

    explicit GameplayObserver();

public:

signals:
    void signalCheckForPlayer(Defs::EColors player);

    void signalBoardChanged(std::shared_ptr<IBoard>);

    void signalMouseOver(int cellX, int cellY);

    void signalCellSelected(int cellX, int cellY);

    void signalMove(QVariant);

    void signalPlayerChanged(std::shared_ptr<Player>);

public slots:

};

#endif // GAMEPLAYOBSERVER_H
