#include "knight.h"
#include "../board.h"

namespace puppets
{

Knight::Knight(std::shared_ptr<Board> board, Defs::EColors color )
    :FigureInterface( board, color, Defs::Knight )
{
}

bool Knight::isValidMove(Defs::MovePrimitive step )
{
    Defs::Position diff = step.to - step.from;
    int adiff1 = abs( diff.y );
    int adiff2 = abs( diff.x );

    if ( ( adiff1 == 2 && adiff2 == 1 ) ||
         ( adiff1 == 1 && adiff2 == 2 ) )
    {
        return true;
    }

return false;
}

void Knight::checkRange( int xFrom, int yFrom, Defs::state& resultState )
{
    if ( xFrom < 0 || yFrom < 0 || HORIZONTAL_SIZE <= xFrom || VERTICAL_SIZE <= yFrom )
        return;

    if ( !IsPositionOccupied(xFrom, yFrom) || !IsSameColorFigureOnPosition(xFrom, yFrom) )
        Defs::setBit( xFrom, yFrom, resultState );
}

void Knight::reachableCells( Defs::state& result, QPair<int,int>& position )
{
    checkRange( position.first + 2, position.second - 1, result );
    checkRange( position.first + 2, position.second + 1, result );
    checkRange( position.first - 2, position.second - 1, result );
    checkRange( position.first - 2, position.second + 1, result );

    checkRange( position.first + 1, position.second - 2, result );
    checkRange( position.first + 1, position.second + 2, result );
    checkRange( position.first - 1, position.second - 2, result );
    checkRange( position.first - 1, position.second + 2, result );

}

QString Knight::name()
{
    return QString("Knight");
}

QString Knight::notation()
{
    return QString("N");
}

} //end namespace
