#include <math.h>
#include <QDebug>

#include "pawn.h"
#include "../Facade/gameplayfacade.h"
#include "../board.h"

Defs::EColors globalColor;

namespace puppets
{

Pawn::Pawn(std::shared_ptr<Board> board, Defs::EColors color )
    :FigureInterface( board, color, Defs::Pawn )
{
}

bool Pawn::isValidMove( Defs::MovePrimitive step )
{
    Defs::Cell** boardState = _board->BoardState();
    //step
    Defs::Position diff = step.to - step.from;
    int inc = _color==Defs::White?1:-1;
    int line = _color==Defs::White?1:6;

    Defs::ESpecials specType = isSpecial(step);

    //move forward
    if ( ( diff.x == inc || ( diff.x == (2*inc) && step.from.x == line ) ) && diff.y == 0 )
    {
        for( int i = step.from.x + inc; i != step.to.x; i += inc )
        {
            if (i == step.to.x)
                break;

            if ( boardState[i][step.to.y].figure )
            {
                return false;
            }
        }
        return true;
    }
    else if ( diff.x == inc && abs( diff.y ) == 1 )
    {
        if (specType == Defs::EnPassant)
            return true;

        //take a sidestep
        return _board->at(step.to).figure != 0;
    }

return false;
}

void Pawn::reachableCells( Defs::state& result, QPair<int,int>& position )
{
    int sign = 1;
    Defs::Cell** boardState = _board->BoardState();

    if ( _color == Defs::White )
    {
        if ( position.first == 1 && position.first + 2 < HORIZONTAL_SIZE )
        {
            if ( !IsPositionOccupied(position, 2, 0) )
            {
                Defs::setBit( position.first + 2, position.second, result );
            }
        }

    }
    else if ( _color == Defs::Black )
    {
        if ( position.first == 6 && 0 <= position.first - 2 )
        {
            if ( !IsPositionOccupied(position, -2, 0) )
            {
                Defs::setBit( position.first - 2, position.second, result );
            }
        }

        sign = -1;
    }

    if ( position.first + sign < 0 && HORIZONTAL_SIZE <= position.first + sign )
        return;

    CheckAndSetFrontDown(sign, position, boardState, result);

    CheckAndSetFront(result, sign, position);

    CheckAndSetFrontUp(position, result, boardState, sign);
}

bool Pawn::IsSameColor(QPair<int,int>& position, Defs::Cell** boardState, int sign, int offset)
{
    return boardState[position.first + sign][position.second + offset].figure & _color;
}

bool Pawn::IsPositionOccupied(QPair<int,int>& position, int sign, int offset)
{
    return Defs::testBit( position.first + sign, position.second + offset, _board->WhiteBlackState()._board );
}

void Pawn::CheckAndSetFront(Defs::state& result, int sign, QPair<int,int>& position)
{
    if ( 0 <= position.second && position.second < VERTICAL_SIZE )
    {
        if ( !IsPositionOccupied(position, sign, 0) )
        {
            Defs::setBit( position.first + sign, position.second, result );
        }
    }
}

void Pawn::CheckAndSetFrontDown(int sign, QPair<int,int>& position, Defs::Cell** boardState, Defs::state& result)
{
    if ( 0 <= position.second - 1 && position.second - 1 < VERTICAL_SIZE )
    {
        if ( IsPositionOccupied(position, sign, -1) &&
             !IsSameColor(position, boardState, sign, -1) )
        {
            Defs::setBit( position.first + sign, position.second - 1, result );
        }
    }
}

void Pawn::CheckAndSetFrontUp(QPair<int,int>& position, Defs::state& result, Defs::Cell** boardState, int sign)
{
    if ( 0 <= position.second + 1 && position.second + 1 < VERTICAL_SIZE )
    {
        if (IsPositionOccupied(position, sign, 1) &&
            !IsSameColor(position, boardState, sign, 1))
        {
            Defs::setBit( position.first + sign, position.second + 1, result );
        }
    }
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
    std::shared_ptr<Board> board = GameplayFacade::Instance()->GetBoard();
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
        Defs::Cell& cell = _board->cell(pos);
        if (cell.figure & Defs::Pawn && !(cell.figure & _color))
        {
            std::function<bool(const Defs::Move&)> fn = [pos,this](const Defs::Move &m)->bool{return (m.figure & Defs::Pawn)
                                                                                            && !((m.figure & 0x03) & this->color())
                                                                                            && m.to == pos;};
            auto filteredHistory = board->filterHistory(fn);
            auto lastMove = board->lastMove();
            auto lastDiff = lastMove.to - lastMove.from;
            if (filteredHistory.size() == 1 && filteredHistory.takeFirst() == lastMove && abs(lastDiff.x) == 2)
            {
                return Defs::Castling;
            }
        }
    }


return Defs::None;
}

bool Pawn::filterPawns(const Defs::Move &m)
{
    int color = m.figure & 0x03;
return (m.figure & Defs::Pawn) && !(color & _color);
}

} //end namespace
