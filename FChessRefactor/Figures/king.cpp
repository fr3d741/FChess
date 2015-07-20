#include "king.h"

namespace puppets
{

King::King(std::shared_ptr<Board> board, Defs::EColors color )
    :FigureInterface( board, color, Defs::King )
{
}

bool King::isValidMove(Defs::MovePrimitive step )
{
    int diff1 = step.to.first - step.from.first;
    int diff2 = step.to.second - step.from.second;

    if ( abs( diff1 ) < 2 && abs( diff2 ) < 2 )
    {
        return true;
    }

    if ( abs( diff2 ) == 2 )
    {
        return true;
    }

return false;
}

void King::reachableCells( Defs::state& , QPair<int,int>& )
{
}

} //end namespace
