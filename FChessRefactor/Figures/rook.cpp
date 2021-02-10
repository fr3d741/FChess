#include <iostream>
#include "../board.h"
#include "rook.h"

static bool IsPositionOccupied(IBoard* board, int i, int j)
{
  return board->TestPosition(i, j);
}

static bool IsSameColorFigureOnPosition(IBoard* board, int i, int j, Defs::EColors color)
{
  return color & board->GetFigureInPosition(i, j);
}

static bool IsInputRangeInvalid(int yFrom, int xTo, int yTo, int xFrom)
{
  return xFrom < 0 ||
    yFrom < 0 ||
    xTo < 0 ||
    yTo < 0 ||
    HORIZONTAL_SIZE <= xFrom ||
    VERTICAL_SIZE <= yFrom ||
    HORIZONTAL_SIZE <= xTo ||
    VERTICAL_SIZE <= yTo;
}

static void checkRange(IBoard* board, int xFrom, int yFrom, int xTo, int yTo, Defs::state& resultState, Defs::EColors color)
{
  if (IsInputRangeInvalid(yFrom, xTo, yTo, xFrom))
    return;

  int diff_x = xTo - xFrom;
  int diff_y = yTo - yFrom;
  if (diff_x)
    diff_x = diff_x / abs(diff_x);

  if (diff_y)
    diff_y = diff_y / abs(diff_y);

  if (!diff_x && !diff_x)
    return;

  for (int i = xFrom, j = yFrom; i <= xTo && j <= yTo; i += diff_x, j += diff_y)
  {
    if (IsPositionOccupied(board, i, j))
    {
      if (!IsSameColorFigureOnPosition(board, i, j, color))
      {
        Defs::setBit(i, j, resultState);
      }
      break;
    }

    Defs::setBit(i, j, resultState);
  }
}


namespace puppets
{

Rook::Rook(std::shared_ptr<IBoard> board, Defs::EColors color )
    :FigureInterface( board, color, Defs::Rook )
{
}

bool Rook::isValidMove(Defs::MovePrimitive step )
{
    Defs::Position diff = step.to - step.from;
    int stepY = 0;
    int stepX = 0;

    if (diff.x && diff.y)
        return false;

    if (diff.y) stepY = diff.y / abs(diff.y);
    else if (diff.x) stepX = diff.x / abs(diff.x);

    int count = std::max(abs(diff.x), abs(diff.y));

    for ( int x = step.from.x + stepX, y = step.from.y + stepY, i = 1; i < count; x += stepX, y += stepY, ++i )
    {
        if ( _board->GetFigureInPosition(x, y) )
        {
            return false;
        }
    }

return true;
}

bool Rook::isValidMove(IBoard* board, Defs::MovePrimitive step)
{
    Defs::Position diff = step.to - step.from;
    int stepY = 0;
    int stepX = 0;

    if (diff.x && diff.y)
        return false;

    if (diff.y) stepY = diff.y / abs(diff.y);
    else if (diff.x) stepX = diff.x / abs(diff.x);

    int count = std::max(abs(diff.x), abs(diff.y));

    for ( int x = step.from.x + stepX, y = step.from.y + stepY, i = 1; i < count; x += stepX, y += stepY, ++i )
    {
        if ( board->GetFigureInPosition(x, y) )
        {
            return false;
        }
    }

return true;
}

void Rook::reachableCells( Defs::state& result, QPair<int,int>& position )
{
  reachableCells(_board.get(), result, position, _color);
}

void Rook::reachableCells(IBoard* board, Defs::state& result, QPair<int, int>& position, Defs::EColors color)
{
    checkRange(board, position.first + 1  , position.second       , HORIZONTAL_SIZE - 1, position.second  , result, color);
    checkRange(board, position.first - 1  , position.second       , 0                 , position.second   , result, color);

    checkRange(board, position.first      , position.second + 1   , position.first    , VERTICAL_SIZE - 1 , result, color);
    checkRange(board, position.first      , position.second - 1   , position.first    , 0                 , result, color);
}

QString Rook::name()
{
    return QString("Rook");
}

QString Rook::notation()
{
    return QString("R");
}

} //end namespace

