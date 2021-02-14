#include "king.h"

#include "../Utils/boardfilter.h"
#include "../Facade/gameplayfacade.h"

static bool IsThereKingInVicinityAt(IBoard* board, Defs::Position pos, Defs::EColors color)
{
  auto alt_color = Defs::nextColor(color);
  if (Defs::isPositionValid(pos.x + 1, pos.y + 1) && board->GetFigureInPosition(pos.x + 1, pos.y + 1) == (Defs::King | alt_color)) return true;
  if (Defs::isPositionValid(pos.x + 1, pos.y) && board->GetFigureInPosition(pos.x + 1, pos.y) == (Defs::King | alt_color)) return true;
  if (Defs::isPositionValid(pos.x + 1, pos.y - 1) && board->GetFigureInPosition(pos.x + 1, pos.y - 1) == (Defs::King | alt_color)) return true;

  if (Defs::isPositionValid(pos.x, pos.y + 1) && board->GetFigureInPosition(pos.x, pos.y + 1) == (Defs::King | alt_color)) return true;
  if (Defs::isPositionValid(pos.x, pos.y - 1) && board->GetFigureInPosition(pos.x, pos.y - 1) == (Defs::King | alt_color)) return true;

  if (Defs::isPositionValid(pos.x - 1, pos.y + 1) && board->GetFigureInPosition(pos.x - 1, pos.y + 1) == (Defs::King | alt_color)) return true;
  if (Defs::isPositionValid(pos.x - 1, pos.y) && board->GetFigureInPosition(pos.x - 1, pos.y) == (Defs::King | alt_color)) return true;
  if (Defs::isPositionValid(pos.x - 1, pos.y - 1) && board->GetFigureInPosition(pos.x - 1, pos.y - 1) == (Defs::King | alt_color)) return true;

  return false;
}

static Defs::ESpecials isSpecial(IBoard* board, const Defs::MovePrimitive& move, Defs::EColors color)
{
  BoardFilter filter(board);

  int direction = move.from.y - move.to.y;
  if (abs(direction) < 2)
    return Defs::None;

  Defs::Position pos = move.from;
  std::function<bool(const Defs::Move&)> filterKingMovement = [pos, color](const Defs::Move& m)->bool {return m.figure == (Defs::King | color); };
  if (!filter.filterHistory(filterKingMovement).isEmpty())
  {
    return Defs::None;
  }

  direction = direction / abs(direction);
  Defs::Position p{ -1, -1 };
  for (int i = move.from.y; 0 <= i && i < VERTICAL_SIZE; i += direction)
  {
    Defs::Position tempp{ move.from.x, i };
    Defs::Cell& c = board->cell(tempp);
    if (c.figure == (Defs::Rook | color))
    {
      p = tempp;
      break;
    }
  }

  if (p.x == -1 || p.y == -1)
    return Defs::None;

  std::function<bool(const Defs::Move&)> filterRookMovement = [p, color](const Defs::Move& m)->bool {return m.figure == (Defs::Rook | color) && m.from == p; };

  return Defs::Castling;
}


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
        return !IsThereKingInVicinityAt(_board.get(), step.to, _color);
    }

    //Castling
    if ( abs( diff.y ) == 2 && diff.x == 0)
    {
        return isSpecial(step) == Defs::Castling;
    }

return false;
}

bool King::isValidMove(IBoard* board, Defs::MovePrimitive step, Defs::EColors color)
{
    Defs::Position diff = step.to - step.from;

    if ( abs( diff.y ) < 2 && abs( diff.x ) < 2 )
    {
        return !IsThereKingInVicinityAt(board, step.to, color);
    }

    //Castling
    if ( abs( diff.y ) == 2 && diff.x == 0)
    {
        return ::isSpecial(board, step, color) == Defs::Castling;
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
    if (abs(direction) < 2)
        return Defs::None;

    Defs::Position pos = move.from;
    std::function<bool(const Defs::Move&)> filterKingMovement = [pos,this](const Defs::Move &m)->bool{return m.figure == (Defs::King | color());};
    if (!filter.filterHistory(filterKingMovement).isEmpty())
    {
        return Defs::None;
    }

    direction = direction / abs(direction);
    Defs::Position p{-1, -1};
    for(int i = move.from.y; 0 <= i && i < VERTICAL_SIZE; i += direction)
    {
        Defs::Position tempp{move.from.x, i};
        Defs::Cell& c = _board->cell(tempp);
        if (c.figure == (Defs::Rook | color()))
        {
            p = tempp;
            break;
        }
    }

    if (p.x == -1 || p.y == -1)
        return Defs::None;

    std::function<bool(const Defs::Move&)> filterRookMovement = [p,this](const Defs::Move &m)->bool{return m.figure == (Defs::Rook | color()) && m.from == p;};

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

} //end namespace
