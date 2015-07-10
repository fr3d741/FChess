#include "gameplayfacade.h"

std::shared_ptr<GameplayFacade> GameplayFacade::_instance;

GameplayFacade::GameplayFacade() :
    QObject()
{
}

std::shared_ptr<GameplayFacade> GameplayFacade::Instance()
{
    if (_instance.get()==nullptr)
    {
        _instance = std::shared_ptr<GameplayFacade>(new GameplayFacade());
    }

    return _instance;
}
