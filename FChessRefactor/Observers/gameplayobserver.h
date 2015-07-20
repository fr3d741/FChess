#ifndef GAMEPLAYOBSERVER_H
#define GAMEPLAYOBSERVER_H

class Board;

#include <memory>
#include <QObject>
#include <QVariant>

#include "../Interfaces/singleton.h"

class GameplayObserver : public QObject, public Singleton<GameplayObserver>
{
    friend class Singleton<GameplayObserver>;
    Q_OBJECT

    explicit GameplayObserver();

public:

signals:
    void signalBoardChanged(std::shared_ptr<Board>);

    void signalMouseOver(int cellX, int cellY);

    void signalCellSelected(int cellX, int cellY);

    void signalMove(QVariant);

    void signalPlayerChanged();

public slots:

};

#endif // GAMEPLAYOBSERVER_H
