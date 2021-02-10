#include <math.h>
#include <QDebug>

#include "pawn.h"
#include "../Facade/gameplayfacade.h"
#include "../board.h"
#include "../Utils/boardfilter.h"

Defs::EColors globalColor;

namespace puppets
{

Pawn::Pawn(std::shared_ptr<IBoard> board, Defs::EColors color )
    :FigureInterface( board, color, Defs::Pawn )
{
}

bool Pawn::IsSameColor(QPair<int,int>& position, int sign, int offset)
{
    return _board->GetFigureInPosition(position.first + sign, position.second + offset) & _color;
}

bool Pawn::IsMoveValid(Defs::Position from, Defs::Position to, int step)
{
  return IsMoveValid(_board.get(), from, to, step);
}

bool Pawn::IsMoveValid(IBoard* board, Defs::Position from, Defs::Position to, int step)
{
    int i = from.x;
    do
    {
        i += step;
        if (board->GetFigureInPosition(i, to.y))
            return false;
    }
    while(i != to.x);

return true;
}

bool Pawn::IsPositionOccupied(QPair<int,int>& position, int sign, int offset)
{
    return _board->TestPosition(position.first + sign, position.second + offset);
}

void Pawn::CheckAndSetFront(Defs::state& result, int sign, QPair<int,int>& position)
{
    if ( position.second < 0 || VERTICAL_SIZE <= position.second)
        return;

    if ( IsPositionOccupied(position, sign, 0) )
        return;

    if (Defs::isPositionValid(position.first + sign, position.second))
        Defs::setBit( position.first + sign, position.second, result );
}

void Pawn::CheckAndSetFrontDown(int sign, QPair<int,int>& position, Defs::state& result)
{
    if ( position.second - 1 < 0 || VERTICAL_SIZE <= position.second - 1)
        return;

    if ( !IsPositionOccupied(position, sign, -1) || IsSameColor(position, sign, -1) )
        return;

    if (Defs::isPositionValid(position.first + sign, position.second))
        Defs::setBit( position.first + sign, position.second - 1, result );
}

void Pawn::CheckAndSetFrontUp(QPair<int,int>& position, Defs::state& result, int sign)
{
    if ( position.second + 1 < 0 || VERTICAL_SIZE < position.second + 1)
        return;

    if (!IsPositionOccupied(position, sign, 1) || IsSameColor(position, sign, 1))
        return;

    if (Defs::isPositionValid(position.first + sign, position.second))
        Defs::setBit( position.first + sign, position.second + 1, result );
}

QString Pawn::name()
{
    return QString("Pawn");
}

QString Pawn::notation()
{
    return QString("");
}

Defs::ESpecials Pawn::isSpecial(const Defs::MovePrimitive &step)
{
  return isSpecial(_board.get(), step, _color);
    //std::shared_ptr<IBoard> board = GameplayFacade::Instance()->GetBoard();
    //Defs::Cell& piece = _board->cell(step.from);
    //Defs::Position diff = step.to - step.from;
    //Defs::EColors color = (Defs::EColors)(piece.figure & 0x03);
    //int inc = color==Defs::White?1:-1;
    //int line = color==Defs::White?7:0;
    //
    //if (step.to.x == line)
    //{
    //    //Check promotion
    //    return Defs::Promotion;
    //}
    //else if ( diff.x == inc && abs( diff.y ) == 1 )
    //{
    //    //check En passant
    //    Defs::Position pos{step.from.x,step.to.y};
    //    Defs::Cell& cell = _board->cell(pos);
    //    if (cell.figure & Defs::Pawn && !(cell.figure & _color))
    //    {
    //        auto lastMove = board->lastMove();
    //        auto alternateColor = Defs::nextColor(_color);

    //        bool isCorrectFigure = lastMove.figure == (Defs::Pawn | alternateColor);
    //        bool isLastMoveXValid = abs(lastMove.from.x - lastMove.to.x) == 2;
    //        bool isLastMoveYValid = abs(lastMove.from.y - lastMove.to.y) == 0;
    //        bool isCurrentMoveValid = lastMove.to.y == step.to.y;
    //        if (!isCorrectFigure || !isLastMoveXValid || !isLastMoveYValid || !isCurrentMoveValid)
    //        {
    //            return Defs::None;
    //        }

    //        return Defs::EnPassant;
    //    }
    //}


//return Defs::None;
}

Defs::ESpecials Pawn::isSpecial(IBoard* board, const Defs::MovePrimitive &step, Defs::EColors own_color)
{
    Defs::Cell& piece = board->cell(step.from);
    Defs::Position diff = step.to - step.from;
    Defs::EColors color = (Defs::EColors)(piece.figure & 0x03);
    int inc = color==Defs::White?1:-1;
    int line = color==Defs::White?7:0;

    if (step.to.x == line)
    {
        //Check promotion
        return Defs::Promotion;
    }
    else if ( diff.x == inc && abs( diff.y ) == 1 )
    {
        //check En passant
        Defs::Position pos{step.from.x,step.to.y};
        Defs::Cell& cell = board->cell(pos);
        if (cell.figure & Defs::Pawn && !(cell.figure & own_color))
        {
            auto lastMove = board->lastMove();
            auto alternateColor = Defs::nextColor(own_color);

            bool isCorrectFigure = lastMove.figure == (Defs::Pawn | alternateColor);
            bool isLastMoveXValid = abs(lastMove.from.x - lastMove.to.x) == 2;
            bool isLastMoveYValid = abs(lastMove.from.y - lastMove.to.y) == 0;
            bool isCurrentMoveValid = lastMove.to.y == step.to.y;
            if (!isCorrectFigure || !isLastMoveXValid || !isLastMoveYValid || !isCurrentMoveValid)
            {
                return Defs::None;
            }

            return Defs::EnPassant;
        }
    }


return Defs::None;
}

bool Pawn::filterPawns(const Defs::Move &m)
{
    return (m.figure & Defs::Pawn) && !((m.figure & 0x03) & _color);
}

} //end namespace
