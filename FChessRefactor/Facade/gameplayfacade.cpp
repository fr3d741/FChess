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
    connect( this, SIGNAL(signalBoardChanged(std::shared_ptr<Board>)), GameplayObserver::Instance().get(), SIGNAL(signalBoardChanged(std::shared_ptr<Board>)) );
    connect(this, SIGNAL(signalNextPlayer()), GameplayObserver::Instance().get(), SIGNAL(signalPlayerChanged()));
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
    emit signalNextPlayer();
}

void GameplayFacade::addHumanPlayer(Defs::EColors playerColor)
{
    _playerStack.push_back(PlayerFactory::createPlayer(playerColor, Defs::Human));
}

std::shared_ptr<Board> GameplayFacade::GetBoard() const
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

    emit signalBoardChanged(_board);
    emit signalNextPlayer();

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

    if (!Validator::isValidMove(m, player->color()) || Evaluator::isCheckFor(player->color(), move))
    {
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
