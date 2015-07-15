#include "gameplayfacade.h"
#include "../Interfaces/player.h"
#include "../Factories/playerfactory.h"
#include "../board.h"
#include "../Observers/gameplayobserver.h"

GameplayFacade::GameplayFacade()
    :QObject()
    ,_playerStack()
    ,_board(0)
{
    _board = std::shared_ptr<Board>(new Board);
    connect( this, SIGNAL(signalBoardChanged(std::shared_ptr<Board>)), GameplayObserver::Instance().get(), SIGNAL(signalBoardChanged(std::shared_ptr<Board>)) );
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

Board *GameplayFacade::GetBoard() const
{
    return _board.get();
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

    emit signalBoardChanged(_board);

return true;
}
