#include "queen.h"

namespace puppets
{

Queen::Queen( QString path, Defs::EColors color, Defs::EFigures figure )
    :Figure( path, color, figure )
{
}

bool Queen::isValidMove( Defs::Move step )
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

    if ( abs( diff1 ) == abs( diff2 ) )
    {
        for ( int i = step.from.first + step1, j = step.from.second + step2; i != step.to.first || j != step.to.second; i += step1, j += step2 )
        {
            if ( Defs::boardState[i][j].figure )
            {
                return false;
            }
        }

        return true;
    }
    else if ( !diff1 && diff2 )
    {
        for ( int i = step.from.second + step2; i != step.to.second; i += step2 )
        {
            if ( Defs::boardState[step.from.first][i].figure )
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
            if ( Defs::boardState[i][step.from.second].figure )
            {
                return false;
            }
        }

        return true;
    }


return false;
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

void Queen::checkRange( int xFrom, int yFrom, int xDiff, int yDiff, Defs::state& resultState )
{
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

            occupied = Defs::testBit( i, j, Defs::WhiteBlackState._board );

			if ( !occupied )
            {
                Defs::setBit( i, j, resultState );
            }
            else if ( occupied )
            {
                // same color
                finish = true;
                if ( !(_color & Defs::boardState[i][j].figure ) )
                {
                    Defs::setBit( i, j, resultState );
                }
            }
        }
    }
}

} //end namespace
