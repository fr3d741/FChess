#include <iostream>
#include "../board.h"
#include "rook.h"

namespace puppets
{

Rook::Rook(std::shared_ptr<Board> board, Defs::EColors color )
    :FigureInterface( board, color, Defs::Rook )
{
}

bool Rook::isValidMove(Defs::MovePrimitive step )
{
    Defs::Cell** boardState = _board->BoardState();
    Defs::Position diff = step.to - step.from;
    int stepY = 0;
    int stepX = 0;

    if ( diff.y != 0 )
    {
        stepY = diff.y / abs(diff.y);
    }
    else if (diff.x != 0)
    {
        stepX = diff.x / abs(diff.x);
    }

    if (diff.x != 0 && diff.y != 0)
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

void Rook::reachableCells( Defs::state& result, QPair<int,int>& position )
{
    checkRange( position.first + 1  , position.second       , HORIZONTAL_SIZE - 1, position.second  , result );
    checkRange( position.first - 1  , position.second       , 0                 , position.second   , result );

    checkRange( position.first      , position.second + 1   , position.first    , VERTICAL_SIZE - 1 , result );
    checkRange( position.first      , position.second - 1   , position.first    , 0                 , result );
}

QString Rook::name()
{
    return QString("Rook");
}

QString Rook::notation()
{
    return QString("R");
}

void Rook::checkRange( int xFrom, int yFrom, int xTo, int yTo, Defs::state& resultState )
{
    Defs::Cell** boardState = _board->BoardState();
    if ( xFrom < 0 || yFrom < 0 || xTo < 0 || yTo < 0 || HORIZONTAL_SIZE <= xFrom || VERTICAL_SIZE <= yFrom || HORIZONTAL_SIZE <= xTo || VERTICAL_SIZE <= yTo )
    {
        return;
    }

    int diff_x = xTo - xFrom;
    int diff_y = yTo - yFrom;
    if ( diff_x )
    {
        diff_x = diff_x / abs( diff_x );
    }

    if ( diff_y )
    {
        diff_y = diff_y / abs( diff_y );
    }

	if ( !diff_x && !diff_x )
	{
		return;
	}

    bool occupied = false;
    bool finish = false;
    {
        for ( int i = xFrom, j = yFrom; i <= xTo && j <= yTo && !finish; i += diff_x, j += diff_y )
        {
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

