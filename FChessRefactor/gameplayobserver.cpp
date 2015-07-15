#include "gameplayobserver.h"

std::shared_ptr<GameplayObserver> GameplayObserver::_instance;

GameplayObserver::GameplayObserver() :
    QObject()
{
}

std::shared_ptr<GameplayObserver> GameplayObserver::Instance()
{
    if (_instance.get() == nullptr)
    {
        _instance = std::shared_ptr<GameplayObserver>(new GameplayObserver);
    }

return _instance;
}
