#include "gameplayobserver.h"

std::shared_ptr<GameplayObserver> GameplayObserver::_instance;

GameplayObserver::GameplayObserver() :
    QObject()
{
}
