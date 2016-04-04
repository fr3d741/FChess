#include "computer.h"

#include "../Observers/gameplayobserver.h"
#include "../Facade/gameplayfacade.h"
#include "../board.h"
#include "../AI/data.h"
#include "../Factories/figurefactory.h"

Computer::Computer(Defs::EColors color, QObject *parent)
    :Player(color, parent)
{
    auto instance = GameplayObserver::Instance();
    connect(instance.get(), SIGNAL(signalPlayerChanged(std::shared_ptr<Player>)), SLOT(slotPlayerChanged(std::shared_ptr<Player>)));
}

std::pair< int, int >& Computer::cellOverCursor()
{
    return _cellOverCursor;
}

void Computer::slotPlayerChanged(std::shared_ptr<Player> player)
{
    if (player.get() != this)
        return;

    auto instance = GameplayFacade::Instance();
    std::shared_ptr<IBoard> board = instance->GetBoard();
    AiData::Figure* state = new AiData::Figure[64];
    for(int i = 0, c = 0; i < 8; ++i)
        for(int j = 0; j < 8; ++j, ++c)
            state[c].data = (AInt8)board->GetFigureInPosition(i, j);

    AiData::StateNode root;
    root.value = AiData::ValueOfState(state, 8, 8, color());
    for(int i = 0; i < 64; ++i)
    {
//        puppets::FigureFactory::createFigure()
//        state[i].type
    }
}
