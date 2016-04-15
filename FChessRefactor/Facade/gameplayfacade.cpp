#include <QDebug>
#include "gameplayfacade.h"
#include "../Interfaces/player.h"
#include "../Factories/playerfactory.h"
#include "../board.h"
#include "../Observers/gameplayobserver.h"
#include "../Utils/validator.h"
#include "../evaluator.h"
#include "../Proxy/visualproxy.h"

GameplayFacade::GameplayFacade()
    :QObject()
    ,_playerStack()
    ,_board(0)
{
    _board = std::shared_ptr<Board>(new Board);
    connect( this, SIGNAL(signalBoardChanged(std::shared_ptr<IBoard>)), GameplayObserver::Instance().get(), SIGNAL(signalBoardChanged(std::shared_ptr<IBoard>)) );
    connect(this, SIGNAL(signalNextPlayer(std::shared_ptr<Player>)), GameplayObserver::Instance().get(), SIGNAL(signalPlayerChanged(std::shared_ptr<Player>)));
    connect( GameplayObserver::Instance().get(), SIGNAL(signalMove(QVariant)),  SLOT(slotMove(QVariant)) );
    connect(this, SIGNAL(signalCheckForPlayer(Defs::EColors)), GameplayObserver::Instance().get(), SIGNAL(signalCheckForPlayer(Defs::EColors)));
}

std::shared_ptr<Player> GameplayFacade::currentPlayer()
{
    return _playerStack.first();
}

void GameplayFacade::nextPlayer()
{
    std::shared_ptr<Player> player = _playerStack.takeFirst();
    _playerStack.push_back(player);
    Defs::EColors nextPlayer = _playerStack.front()->color();
    if (Evaluator::isCheckFor(nextPlayer))
    {
        emit signalCheckForPlayer(nextPlayer);
    }
    emit signalNextPlayer(currentPlayer());
}

void GameplayFacade::addHumanPlayer(Defs::EColors playerColor)
{
    _playerStack.push_back(PlayerFactory::createPlayer(playerColor, Defs::Human));
}

std::shared_ptr<Player> GameplayFacade::addPlayer(Defs::EPlayers playerType, Defs::EColors playerColor)
{
    std::shared_ptr<Player> player = PlayerFactory::createPlayer(playerColor, playerType);
    _playerStack.push_back(player);
return player;
}

std::shared_ptr<IBoard> GameplayFacade::GetBoard() const
{
    return _board;
}

void GameplayFacade::Reset()
{
    _playerStack.clear();
    _board->init();
}

bool GameplayFacade::start()
{
    if ( _playerStack.isEmpty() )
    {
        //no players => exit
        return false;
    }

    _board->init();

    emit signalBoardChanged(_board);
    emit signalNextPlayer(currentPlayer());

    return true;
}

void GameplayFacade::slotMove(QVariant variant)
{
    std::shared_ptr<Player> player = currentPlayer();
    Defs::MovePrimitive m = variant.value<Defs::MovePrimitive>();
    Defs::Move move = construct(m);

    move.special = m.special = Evaluator::defineSpecial(m);
    if (m.special == Defs::Promotion)
        move.figure = VisualProxy::Instance()->FigurePicker(player->color()) | player->color();

    bool isValidForPlayer = Validator::isValidMove(m, player->color());
    bool isThereCheck = Evaluator::isCheckFor(player->color(), move);
    if (!isValidForPlayer || isThereCheck)
    {
        emit signalNextPlayer(currentPlayer());
        return;
    }

    _board->applyMove(move);
    emit signalBoardChanged(_board);
    nextPlayer();
}

Defs::Move GameplayFacade::construct(Defs::MovePrimitive &m)
{
    Defs::Move move;
    move = m;
    move.fromCell = _board->cell(m.from);
    move.toCell = _board->cell(m.to);
    move.figure = move.fromCell.figure;

    return move;
}
