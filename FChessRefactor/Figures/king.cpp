#include "king.h"

namespace puppets
{

King::King(std::shared_ptr<IBoard> board, Defs::EColors color )
    :FigureInterface( board, color, Defs::King )
{
}

bool King::isValidMove(Defs::MovePrimitive step )
{
    Defs::Position diff = step.to - step.from;

    if ( abs( diff.y ) < 2 && abs( diff.x ) < 2 )
    {
        return true;
    }

    //Castling
    if ( abs( diff.y ) == 2 )
    {
        return true;
    }

return false;
}

void King::reachableCells( Defs::state& , QPair<int,int>& )
{
}

} //end namespace


QString puppets::King::name()
{
    return QString("King");
}

QString puppets::King::notation()
{
    return QString("K");
}
