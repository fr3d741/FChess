#include "bishop.h"
#include "../board.h"

static bool IsInputRangeInvalid(int xFrom, int yFrom, int xTo, int yTo)
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
  if (IsInputRangeInvalid(xFrom, yFrom, xTo, yTo))
    return;

  int diff_x = xTo - xFrom;
  int diff_y = yTo - yFrom;

  if (diff_x)
    diff_x = diff_x / abs(diff_x);

  if (diff_y)
    diff_y = diff_y / abs(diff_y);

  for (int i = xFrom, j = yFrom; i <= xTo && j <= yTo; i += diff_x, j += diff_y)
  {
    if (board->TestPosition(i, j))
    {
      if (!(color & board->GetFigureInPosition(i, j)))
        Defs::setBit(i, j, resultState);

      break;
    }

    Defs::setBit(i, j, resultState);
  }
}

namespace puppets
{

Bishop::Bishop(std::shared_ptr<IBoard> board, Defs::EColors color)
    :FigureInterface( board, color, Defs::Bishop )
{
}

bool Bishop::isValidMove( Defs::MovePrimitive step )
{
  return isValidMove(_board.get(), step);
}

bool Bishop::isValidMove(IBoard* board, Defs::MovePrimitive step)
{
    Defs::Position diff = step.to - step.from;
    int stepY = 0;
    int stepX = 0;

    if ( !diff.x || !diff.y || abs(diff.x) != abs(diff.y) )
        return false;

    if (diff.y)
        stepY = diff.y / abs(diff.y);

    if (diff.x)
        stepX = diff.x / abs(diff.x);

    int count = std::max(abs(diff.x), abs(diff.y));
    for ( int x = step.from.x + stepX, y = step.from.y + stepY, i = 1; i < count; x += stepX, y += stepY, ++i )
    {
        if ( board->GetFigureInPosition(x, y) )
            return false;
    }

return true;
}

void Bishop::reachableCells( Defs::state& result, QPair<int,int>& position )
{
    checkRange(_board.get(), position.first + 1  , position.second + 1   , HORIZONTAL_SIZE - 1, VERTICAL_SIZE - 1, result, _color );
    checkRange(_board.get(), position.first - 1  , position.second - 1   , 0                 , 0                 , result, _color);

    checkRange(_board.get(), position.first - 1  , position.second + 1   , 0                 , VERTICAL_SIZE - 1, result, _color);
    checkRange(_board.get(), position.first + 1  , position.second - 1   , HORIZONTAL_SIZE   , 0                , result, _color);
}

void Bishop::reachableCells(IBoard* board, Defs::state& result, QPair<int, int>& position, Defs::EColors color)
{
    checkRange(board, position.first + 1  , position.second + 1   , HORIZONTAL_SIZE - 1, VERTICAL_SIZE - 1, result, color );
    checkRange(board, position.first - 1  , position.second - 1   , 0                 , 0                 , result, color);

    checkRange(board, position.first - 1  , position.second + 1   , 0                 , VERTICAL_SIZE - 1, result, color);
    checkRange(board, position.first + 1  , position.second - 1   , HORIZONTAL_SIZE   , 0                , result, color);
}

QString Bishop::name()
{
    return QString("Bishop");
}

QString Bishop::notation()
{
    return QString("B");
}

} //end namespace
