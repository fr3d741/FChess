#include "queen.h"
#include "../board.h"

namespace puppets
{

Queen::Queen(std::shared_ptr<Board> board, Defs::EColors color )
    :FigureInterface( board, color, Defs::Queen )
{
}

bool Queen::isValidMove(Defs::MovePrimitive step )
{
    Defs::Cell** boardState = _board->BoardState();
    Defs::Position diff = step.to - step.from;
    int stepY = 0;
    int stepX = 0;

    if ( diff.y != 0 )
    {
        stepY = diff.y / abs(diff.y);
    }

    if (diff.x != 0)
    {
        stepX = diff.x / abs(diff.x);
    }

    if (abs( diff.x ) != abs( diff.y ) && diff.x && diff.y)
        return false;

    int count = std::max(abs(diff.x), abs(diff.y));
    for ( int x = step.from.x + stepX, y = step.from.y + stepY, i = 1; i < count; x += stepX, y += stepY, ++i )
    {
        if ( boardState[x][y].figure )
        {
            return false;
        }
    }

return true;
}

void Queen::reachableCells( Defs::state& result, QPair<int,int>& position )
{
    //qDebug("Queen::reachableCells + ");
    checkRange( position.first + 1  , position.second + 1   , +1, +1, result );
    checkRange( position.first - 1  , position.second - 1   , -1, -1, result );

    checkRange( position.first - 1  , position.second + 1   , -1, +1, result );
    checkRange( position.first + 1  , position.second - 1   , +1, -1, result );

    checkRange( position.first + 1  , position.second       , +1, 0, result );
    checkRange( position.first - 1  , position.second       , -1, 0, result );

    checkRange( position.first      , position.second + 1   , 0, +1, result );
    checkRange( position.first      , position.second - 1   , 0, -1, result );

    //qDebug("Queen::reachableCells - ");
}

QString Queen::name()
{
    return QString("Queen");
}

QString Queen::notation()
{
    return QString("Q");
}

void Queen::checkRange( int xFrom, int yFrom, int xDiff, int yDiff, Defs::state& resultState )
{
    Defs::Cell** boardState = _board->BoardState();
    int diff_x = xDiff;
    int diff_y = yDiff;

    bool occupied = false;
    bool finish = false;
    {
        for ( int i = xFrom, j = yFrom; !finish; i += diff_x, j += diff_y )
        {
            if ( i < 0 || HORIZONTAL_SIZE <= i || j < 0 || VERTICAL_SIZE <= j )
            {
                break;
            }

            occupied = Defs::testBit( i, j, _board->WhiteBlackState()._board );

			if ( !occupied )
            {
                Defs::setBit( i, j, resultState );
            }
            else if ( occupied )
            {
                // same color
                finish = true;
                if ( !(_color & boardState[i][j].figure ) )
                {
                    Defs::setBit( i, j, resultState );
                }
            }
        }
    }
}

} //end namespace
