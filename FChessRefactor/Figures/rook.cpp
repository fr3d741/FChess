#include <iostream>
#include "../board.h"
#include "rook.h"

namespace puppets
{

Rook::Rook( QString path, Defs::EColors color, Defs::EFigures figure )
    :FigureInterface( path, color, figure )
{
}

bool Rook::isValidMove( Defs::Move step )
{
    int diff1 = step.to.first - step.from.first;
    int diff2 = step.to.second - step.from.second;
    int step1 = 0;
    int step2 = 0;

    if ( diff1 )
    {
        step1 = diff1 / abs(diff1);
    }

    if (diff2)
    {
        step2 = diff2 / abs(diff2);
    }

    if ( !diff1 && diff2 )
    {
        for ( int i = step.from.second + step2; i != step.to.second; i += step2 )
        {
            if ( Board::boardState[step.from.first][i].figure )
            {
                return false;
            }
        }

        return true;
    }
    else if ( diff1 && !diff2 )
    {
        for ( int i = step.from.first + step1; i != step.to.first; i += step1 )
        {
            if ( Board::boardState[i][step.from.second].figure )
            {
                return false;
            }
        }
        return true;
    }

return false;
}

void Rook::reachableCells( Defs::state& result, QPair<int,int>& position )
{
    checkRange( position.first + 1  , position.second       , HORIZONTAL_SIZE - 1, position.second  , result );
    checkRange( position.first - 1  , position.second       , 0                 , position.second   , result );

    checkRange( position.first      , position.second + 1   , position.first    , VERTICAL_SIZE - 1 , result );
    checkRange( position.first      , position.second - 1   , position.first    , 0                 , result );
}

void Rook::checkRange( int xFrom, int yFrom, int xTo, int yTo, Defs::state& resultState )
{
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
            occupied = Defs::testBit( i, j, Defs::WhiteBlackState._board );

            if ( !occupied )
            {
                Defs::setBit( i, j, resultState );
            }
            else if ( occupied )
            {
                // same color
                finish = true;
                if ( !(_color & Board::boardState[i][j].figure ) )
                {
                    Defs::setBit( i, j, resultState );
                }
            }
        }
    }
}

} //end namespace

