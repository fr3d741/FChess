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
    bool occupied = false;
    bool sameColor = false;
    Defs::Cell** boardState = _board->BoardState();

    if ( _color == Defs::White )
    {
        if ( position.first == 1 && position.first + 2 < HORIZONTAL_SIZE )
        {
            occupied = Defs::testBit( position.first + 2, position.second, _board->WhiteBlackState()._board );
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
            occupied = Defs::testBit( position.first - 2, position.second, _board->WhiteBlackState()._board );
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
            occupied = Defs::testBit( position.first + sign, position.second - 1, _board->WhiteBlackState()._board );
            sameColor = boardState[position.first + sign][position.second - 1].figure & _color;
            if ( occupied && !sameColor )
            {
                Defs::setBit( position.first + sign, position.second - 1, result );
            }
        }

        if ( 0 <= position.second && position.second < VERTICAL_SIZE )
        {
            occupied = Defs::testBit( position.first + sign, position.second, _board->WhiteBlackState()._board );
            if ( !occupied )
            {
                Defs::setBit( position.first + sign, position.second, result );
            }
        }

        if ( 0 <= position.second + 1 && position.second + 1 < VERTICAL_SIZE )
        {
            occupied = Defs::testBit( position.first + sign, position.second + 1, _board->WhiteBlackState()._board );
            sameColor = boardState[position.first + sign][position.second + 1].figure & _color;
            if ( occupied && !sameColor )
            {
                Defs::setBit( position.first + sign, position.second + 1, result );
            }
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
