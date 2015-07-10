#include <math.h>
#include "pawn.h"


namespace puppets
{

Pawn::Pawn( QString path, Defs::EColors color, Defs::EFigures figure )
    :FigureInterface( path, color, figure )
{
}

bool Pawn::isValidMove( Defs::Move step )
{
    //step
    int dist = step.to.first - step.from.first;
    int distSecond = step.to.second - step.from.second;

    //TODO: check for En passant
    if ( _color == Defs::White )
    {
        //step in forward 0 -> 7
        if ( ( dist == 1 || ( dist == 2 && step.from.first == 1 ) ) && step.to.second == step.from.second )
        {
            for( int i = step.from.first + 1; i <= step.to.first; ++i  )
            {
                if ( Defs::boardState[i][step.to.second].figure )
                {
                    qDebug("False1: %d, %d", step.from.first, step.from.second );
                    qDebug("False2: %d, %d", step.to.first, step.to.second );
                    qDebug("False3: %d, %d, %d", i, step.to.second, Defs::boardState[i][step.to.second].figure );
                    return false;
                }
            }
            return true;
        }
        else if ( dist == 1 && abs( distSecond ) == 1 )
        {
            if ( Defs::boardState[step.to.first][step.to.second].figure )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    else if ( _color == Defs::Black )
    {
        // step back 7 -> 0
        if ( ( dist == -1 || ( dist == -2 && step.from.first == 6 ) ) && step.to.second == step.from.second )
        {
            for( int i = step.from.first - 1; i < step.to.first; --i  )
            {
                if ( Defs::boardState[i][step.to.second].figure )
                {
                    return false;
                }
            }
            return true;
        }
        else if ( dist == -1 && abs( distSecond ) == 1 )
        {
            if ( Defs::boardState[step.to.first][step.to.second].figure )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

return false;
}

void Pawn::reachableCells( Defs::state& result, QPair<int,int>& position )
{
    int sign = 1;
    bool occupied = false;
    bool sameColor = false;

    if ( _color == Defs::White )
    {
        if ( position.first == 1 && position.first + 2 < HORIZONTAL_SIZE )
        {
            occupied = Defs::testBit( position.first + 2, position.second, Defs::WhiteBlackState._board );
            if ( !occupied )
            {
                Defs::setBit( position.first + 2, position.second, result );
            }
        }

    }
    else if ( _color == Defs::Black )
    {
        if ( position.first == 6 && 0 <= position.first - 2 )
        {
            occupied = Defs::testBit( position.first - 2, position.second, Defs::WhiteBlackState._board );
            if ( !occupied )
            {
                Defs::setBit( position.first - 2, position.second, result );
            }
        }

        sign = -1;
    }

    if ( 0 <= position.first + sign && position.first + sign < HORIZONTAL_SIZE )
    {
        if ( 0 <= position.second - 1 && position.second - 1 < VERTICAL_SIZE )
        {
            occupied = Defs::testBit( position.first + sign, position.second - 1, Defs::WhiteBlackState._board );
            sameColor = Defs::boardState[position.first + sign][position.second - 1].figure & _color;
            if ( occupied && !sameColor )
            {
                Defs::setBit( position.first + sign, position.second - 1, result );
            }
        }

        if ( 0 <= position.second && position.second < VERTICAL_SIZE )
        {
            occupied = Defs::testBit( position.first + sign, position.second, Defs::WhiteBlackState._board );
            if ( !occupied )
            {
                Defs::setBit( position.first + sign, position.second, result );
            }
        }

        if ( 0 <= position.second + 1 && position.second + 1 < VERTICAL_SIZE )
        {
            occupied = Defs::testBit( position.first + sign, position.second + 1, Defs::WhiteBlackState._board );
            sameColor = Defs::boardState[position.first + sign][position.second + 1].figure & _color;
            if ( occupied && !sameColor )
            {
                Defs::setBit( position.first + sign, position.second + 1, result );
            }
        }
    }
}

} //end namespace
