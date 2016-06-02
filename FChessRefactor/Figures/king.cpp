#include "king.h"

#include "../Utils/boardfilter.h"
#include "../Facade/gameplayfacade.h"

namespace puppets
{

King::King(std::shared_ptr<IBoard> board, Defs::EColors color )
    :FigureInterface( board, color, Defs::King )
{
}

bool King::isValidMove(Defs::MovePrimitive step )
{
    Defs::Position diff = step.to - step.from;

    if ( abs( diff.y ) < 2 && abs( diff.x ) < 2 )
    {
        return !IsThereKingInVicinityAt(step.to);
    }

    //Castling
    if ( abs( diff.y ) == 2 && diff.x == 0)
    {
        return isSpecial(step) == Defs::Castling;
    }

return false;
}

void King::reachableCells( Defs::state& , QPair<int,int>& )
{
}

Defs::ESpecials King::isSpecial(const Defs::MovePrimitive &move)
{
    std::shared_ptr<IBoard> board = GameplayFacade::Instance()->GetBoard();
    BoardFilter filter(board);

    int direction = move.from.y - move.to.y;
    if (direction < 2)
        return Defs::None;

    Defs::Position pos = move.from;
    std::function<bool(const Defs::Move&)> filterKingMovement = [pos,this](const Defs::Move &m)->bool{return m.figure == (Defs::King | color());};
    if (!filter.filterHistory(filterKingMovement).isEmpty())
    {
        return Defs::None;
    }

    direction = direction / abs(direction);
    Defs::Position p{-1, -1};
    for(int i = move.from.y; i <= 0 && i < VERTICAL_SIZE; i += direction)
    {
        Defs::Position tempp{move.from.x, i};
        if (_board->cell(p).figure == (Defs::Rook | color()))
        {
            p = tempp;
            break;
        }
    }

    if (p.x == -1 || p.y == -1)
        return Defs::None;

    std::function<bool(const Defs::Move&)> filterRookMovement = [p,this](const Defs::Move &m)->bool{return m.figure == (Defs::Rook & color()) && m.from == p;};

return Defs::Castling;
}


QString King::name()
{
    return QString("King");
}

QString King::notation()
{
    return QString("K");
}

bool King::IsThereKingInVicinityAt(Defs::Position pos)
{
    auto alt_color = Defs::nextColor(color());
    if (Defs::isPositionValid(pos.x + 1, pos.y + 1) && _board->GetFigureInPosition(pos.x + 1, pos.y + 1) == (Defs::King | alt_color)) return true;
    if (Defs::isPositionValid(pos.x + 1, pos.y)     && _board->GetFigureInPosition(pos.x + 1, pos.y) == (Defs::King | alt_color)) return true;
    if (Defs::isPositionValid(pos.x + 1, pos.y - 1) && _board->GetFigureInPosition(pos.x + 1, pos.y - 1) == (Defs::King | alt_color)) return true;

    if (Defs::isPositionValid(pos.x, pos.y + 1) && _board->GetFigureInPosition(pos.x, pos.y + 1) == (Defs::King | alt_color)) return true;
    if (Defs::isPositionValid(pos.x, pos.y - 1) && _board->GetFigureInPosition(pos.x, pos.y - 1) == (Defs::King | alt_color)) return true;

    if (Defs::isPositionValid(pos.x - 1, pos.y + 1) && _board->GetFigureInPosition(pos.x - 1, pos.y + 1) == (Defs::King | alt_color)) return true;
    if (Defs::isPositionValid(pos.x - 1, pos.y)     && _board->GetFigureInPosition(pos.x - 1, pos.y) == (Defs::King | alt_color)) return true;
    if (Defs::isPositionValid(pos.x - 1, pos.y - 1) && _board->GetFigureInPosition(pos.x - 1, pos.y - 1) == (Defs::King | alt_color)) return true;

return false;
}

} //end namespace
