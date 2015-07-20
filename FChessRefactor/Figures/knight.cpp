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
    Defs::Cell** boardState = _board->BoardState();

    if ( xFrom < 0 || yFrom < 0 || HORIZONTAL_SIZE <= xFrom || VERTICAL_SIZE <= yFrom )
    {
        return;
    }


    occupied = Defs::testBit( xFrom, yFrom, _board->WhiteBlackState()._board );
    sameColor = boardState[xFrom][yFrom].figure & _color;
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
