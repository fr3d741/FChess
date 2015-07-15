#include "gameplayfacade.h"
#include "../Interfaces/player.h"
#include "../Factories/playerfactory.h"
#include "../board.h"
#include "../gameplayobserver.h"

std::shared_ptr<GameplayFacade> GameplayFacade::_instance;

GameplayFacade::GameplayFacade()
    :QObject()
    ,_playerStack()
    ,_board(0)
{
    _board = new Board(this);
    connect( this, SIGNAL(signalBoardChanged(std::shared_ptr<Board>)), GameplayObserver::Instance().get(), SIGNAL(signalBoardChanged(std::shared_ptr<Board>)) );
}

std::shared_ptr<GameplayFacade> GameplayFacade::Instance()
{
    if (_instance.get()==nullptr)
    {
        _instance = std::shared_ptr<GameplayFacade>(new GameplayFacade());
    }

    return _instance;
}

std::shared_ptr<Player> GameplayFacade::currentPlayer()
{
    return _playerStack.first();
}

void GameplayFacade::nextPlayer()
{
    std::shared_ptr<Player> player = _playerStack.takeFirst();
    _playerStack.push_back(player);
}

void GameplayFacade::addHumanPlayer(Defs::EColors playerColor)
{
    _playerStack.push_back(PlayerFactory::createPlayer(playerColor, Defs::Human));
}

const Board *GameplayFacade::GetBoard() const
{
    return _board;
}

bool GameplayFacade::start()
{
    if ( _playerStack.isEmpty() )
    {
        //no players => exit
        return false;
    }

    //_started = true;
    _board->init();

    emit signalBoardChanged(std::shared_ptr<Board>(_board));

return true;
}
