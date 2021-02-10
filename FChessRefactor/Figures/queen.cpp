#include "queen.h"
#include "../board.h"

static bool IsPositionOccupied(IBoard* board, int i, int j)
{
  return board->TestPosition(i, j);
}

static bool IsSameColorFigureOnPosition(IBoard* board, int i, int j, Defs::EColors color)
{
  return color & board->GetFigureInPosition(i, j);
}

static bool IsPositionCoordinatesValid(int i, int j)
{
  return 0 <= i && i < HORIZONTAL_SIZE &&
    0 <= j && j < VERTICAL_SIZE;
}

static void checkRange(IBoard* board, int xFrom, int yFrom, int xDiff, int yDiff, Defs::state& resultState, Defs::EColors color)
{
  for (int i = xFrom, j = yFrom; IsPositionCoordinatesValid(i, j); i += xDiff, j += yDiff)
  {
    if (IsPositionOccupied(board, i, j))
    {
      if (!IsSameColorFigureOnPosition(board, i, j, color))
        Defs::setBit(i, j, resultState);

      break;
    }

    Defs::setBit(i, j, resultState);
  }
}

namespace puppets
{

Queen::Queen(std::shared_ptr<IBoard> board, Defs::EColors color )
    :FigureInterface( board, color, Defs::Queen )
{
}

bool Queen::isValidMove(Defs::MovePrimitive step )
{
    Defs::Position diff = step.to - step.from;
    int stepY = 0;
    int stepX = 0;

    if ( diff.y )
        stepY = diff.y / abs(diff.y);

    if (diff.x )
        stepX = diff.x / abs(diff.x);

    if (abs( diff.x ) != abs( diff.y ) && diff.x && diff.y)
        return false;

    int count = std::max(abs(diff.x), abs(diff.y));
    for ( int x = step.from.x + stepX, y = step.from.y + stepY, i = 1; i < count; x += stepX, y += stepY, ++i )
    {
        if ( _board->GetFigureInPosition(x, y) )
            return false;
    }

return true;
}

bool Queen::isValidMove(IBoard* board, Defs::MovePrimitive step )
{
    Defs::Position diff = step.to - step.from;
    int stepY = 0;
    int stepX = 0;

    if ( diff.y )
        stepY = diff.y / abs(diff.y);

    if (diff.x )
        stepX = diff.x / abs(diff.x);

    if (abs( diff.x ) != abs( diff.y ) && diff.x && diff.y)
        return false;

    int count = std::max(abs(diff.x), abs(diff.y));
    for ( int x = step.from.x + stepX, y = step.from.y + stepY, i = 1; i < count; x += stepX, y += stepY, ++i )
    {
        if ( board->GetFigureInPosition(x, y) )
            return false;
    }

return true;
}

void Queen::reachableCells( Defs::state& result, QPair<int,int>& position )
{
  reachableCells(_board.get(), result, position, _color);
    //checkRange( position.first + 1  , position.second + 1   , +1, +1, result );
    //checkRange( position.first - 1  , position.second - 1   , -1, -1, result );

    //checkRange( position.first - 1  , position.second + 1   , -1, +1, result );
    //checkRange( position.first + 1  , position.second - 1   , +1, -1, result );

    //checkRange( position.first + 1  , position.second       , +1, 0, result );
    //checkRange( position.first - 1  , position.second       , -1, 0, result );

    //checkRange( position.first      , position.second + 1   , 0, +1, result );
    //checkRange( position.first      , position.second - 1   , 0, -1, result );
}

void Queen::reachableCells(IBoard* board, Defs::state& result, QPair<int, int>& position, Defs::EColors color)
{
    checkRange(board, position.first + 1  , position.second + 1   , +1, +1, result, color);
    checkRange(board, position.first - 1  , position.second - 1   , -1, -1, result, color);

    checkRange(board, position.first - 1  , position.second + 1   , -1, +1, result, color);
    checkRange(board, position.first + 1  , position.second - 1   , +1, -1, result, color);

    checkRange(board, position.first + 1  , position.second       , +1, 0, result, color);
    checkRange(board, position.first - 1  , position.second       , -1, 0, result, color);

    checkRange(board, position.first      , position.second + 1   , 0, +1, result, color);
    checkRange(board, position.first      , position.second - 1   , 0, -1, result, color);
}

QString Queen::name()
{
    return QString("Queen");
}

QString Queen::notation()
{
    return QString("Q");
}

} //end namespace
