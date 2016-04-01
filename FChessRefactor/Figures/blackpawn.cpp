#include "blackpawn.h"
#include "../board.h"

namespace puppets
{

BlackPawn::BlackPawn(std::shared_ptr<Board> board)
    :Pawn(board, Defs::Black)
{
}

void BlackPawn::reachableCells(Defs::state &result, QPair<int, int> &position)
{
    int sign = -1;

    if ( position.first == 6 && 0 <= position.first - 2 )
    {
        if ( !IsPositionOccupied(position, -2, 0) )
        {
            Defs::setBit( position.first - 2, position.second, result );
        }
    }

    if ( position.first + sign < 0 && HORIZONTAL_SIZE <= position.first + sign )
        return;

    CheckAndSetFrontDown(sign, position, result);

    CheckAndSetFront(result, sign, position);

    CheckAndSetFrontUp(position, result, sign);
}

bool BlackPawn::isValidMove(Defs::MovePrimitive step)
{
    Defs::Position diff = step.to - step.from;
    int stepDiff = -1;
    int line = 6;

    Defs::ESpecials specType = isSpecial(step);

    //move forward
    if ( ( diff.x == stepDiff || ( diff.x == (2*stepDiff) && step.from.x == line ) ) && diff.y == 0 )
    {
        for( int i = step.from.x + stepDiff; i != step.to.x; i += stepDiff )
        {
            if (i == step.to.x)
                break;

            if ( _board->GetFigureInPosition(i, step.to.y) )
            {
                return false;
            }
        }
        return true;
    }
    else if ( diff.x == stepDiff && abs( diff.y ) == 1 )
    {
        if (specType == Defs::EnPassant)
            return true;

        //take a sidestep
        return _board->at(step.to).figure != 0;
    }

return false;
}

}
