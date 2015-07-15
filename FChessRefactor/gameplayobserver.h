#ifndef GAMEPLAYOBSERVER_H
#define GAMEPLAYOBSERVER_H

class Board;

#include <memory>
#include <QObject>

class GameplayObserver : public QObject
{
    Q_OBJECT
    static std::shared_ptr<GameplayObserver> _instance;

    explicit GameplayObserver();

public:
    static std::shared_ptr<GameplayObserver> Instance();

signals:
    void signalBoardChanged(std::shared_ptr<Board>);

public slots:

};

#endif // GAMEPLAYOBSERVER_H
