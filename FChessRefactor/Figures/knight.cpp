#include "knight.h"
#include "../board.h"

namespace puppets
{

Knight::Knight( QString path, Defs::EColors color, Defs::EFigures figure )
    :FigureInterface( path, color, figure )
{
}

bool Knight::isValidMove( Defs::Move step )
{
    int diff1 = step.to.first - step.from.first;
    int diff2 = step.to.second - step.from.second;
    int adiff1 = abs( diff1 );
    int adiff2 = abs( diff2 );

    if ( ( adiff1 == 2 && adiff2 == 1 ) || ( adiff1 == 1 && adiff2 == 2 ) )
    {
        return true;
    }

return false;
}

void Knight::checkRange( int xFrom, int yFrom, Defs::state& resultState )
{
    bool occupied = false;
    bool sameColor = false;

    if ( xFrom < 0 || yFrom < 0 || HORIZONTAL_SIZE <= xFrom || VERTICAL_SIZE <= yFrom )
    {
        return;
    }


    occupied = Defs::testBit( xFrom, yFrom, Defs::WhiteBlackState._board );
    sameColor = Board::boardState[xFrom][yFrom].figure & _color;
    if ( !occupied || !sameColor )
    {
        Defs::setBit( xFrom, yFrom, resultState );
    }
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

} //end namespace
