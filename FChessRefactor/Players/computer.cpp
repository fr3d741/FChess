#include <QDebug>

#include "computer.h"

#include "../Observers/gameplayobserver.h"
#include "../Facade/gameplayfacade.h"
#include "../board.h"
#include "../AI/data.h"
#include "../Factories/figurefactory.h"
#include "../Interfaces/figure.h"
#include "../AI/Strategies/randomstrategy.h"

Computer::Computer(Defs::EColors color, QObject *parent)
    :Player(color, parent)
    ,_cellOverCursor()
    ,_root()
    ,_rootValid(false)
    ,_decisionTree()
    ,_strategy(new Ai::RandomStrategy)
{
    auto instance = GameplayObserver::Instance();
    connect(instance.get(), SIGNAL(signalPlayerChanged(std::shared_ptr<Player>)), SLOT(slotPlayerChanged(std::shared_ptr<Player>)));
    connect(this, SIGNAL(signalMove(QVariant)), GameplayObserver::Instance().get(), SIGNAL(signalMove(QVariant)));
}

std::pair< int, int >& Computer::cellOverCursor()
{
    return _cellOverCursor;
}

void Computer::SetStrategy(std::shared_ptr<Ai::IStrategy> strategy)
{
    _strategy = strategy;
}

void Computer::slotPlayerChanged(std::shared_ptr<Player> player)
{
    if (player.get() != this)
        return;

    auto instance = GameplayFacade::Instance();
    std::shared_ptr<IBoard> board = instance->GetBoard();

    _decisionTree.BuildTree(board, color());
    auto selected = _strategy->SelectNode(&_decisionTree);

    Defs::MovePrimitive move;
    move.from.x = selected->move.from.x;
    move.from.y = selected->move.from.y;
    move.to.x = selected->move.to.x;
    move.to.y = selected->move.to.y;
    emit signalMove(QVariant::fromValue(move));
}

