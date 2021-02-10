#include "knight.h"
#include "../board.h"

static bool IsPositionOccupied(IBoard* board, int i, int j)
{
  return board->TestPosition(i, j);
}

static bool IsSameColorFigureOnPosition(IBoard* board, int i, int j, Defs::EColors color)
{
  return color & board->GetFigureInPosition(i, j);
}

static void checkRange(IBoard* board, int xFrom, int yFrom, Defs::state& resultState, Defs::EColors color)
{
  if (xFrom < 0 || yFrom < 0 || HORIZONTAL_SIZE <= xFrom || VERTICAL_SIZE <= yFrom)
    return;

  if (!IsPositionOccupied(board, xFrom, yFrom) || !IsSameColorFigureOnPosition(board, xFrom, yFrom, color))
    Defs::setBit(xFrom, yFrom, resultState);
}

namespace puppets
{

Knight::Knight(std::shared_ptr<IBoard> board, Defs::EColors color )
    :FigureInterface( board, color, Defs::Knight )
{
}

bool Knight::isValidMove(Defs::MovePrimitive step )
{
    Defs::Position diff = step.to - step.from;
    int adiff1 = abs( diff.y );
    int adiff2 = abs( diff.x );

    if ( ( adiff1 == 2 && adiff2 == 1 ) ||
         ( adiff1 == 1 && adiff2 == 2 ) )
    {
        return true;
    }

return false;
}

bool Knight::isValidMove(IBoard* /*board*/, Defs::MovePrimitive step )
{
    Defs::Position diff = step.to - step.from;
    int adiff1 = abs( diff.y );
    int adiff2 = abs( diff.x );

    if ( ( adiff1 == 2 && adiff2 == 1 ) ||
         ( adiff1 == 1 && adiff2 == 2 ) )
    {
        return true;
    }

return false;
}

void Knight::reachableCells( Defs::state& result, QPair<int,int>& position )
{
  checkRange(_board.get(), position.first + 2, position.second - 1, result, _color);
  checkRange(_board.get(), position.first + 2, position.second + 1, result, _color);
  checkRange(_board.get(), position.first - 2, position.second - 1, result, _color);
  checkRange(_board.get(), position.first - 2, position.second + 1, result, _color);

  checkRange(_board.get(), position.first + 1, position.second - 2, result, _color);
  checkRange(_board.get(), position.first + 1, position.second + 2, result, _color);
  checkRange(_board.get(), position.first - 1, position.second - 2, result, _color);
  checkRange(_board.get(), position.first - 1, position.second + 2, result, _color);
}

void Knight::reachableCells(IBoard* board, Defs::state& result, QPair<int,int>& position, Defs::EColors color )
{
    checkRange(board, position.first + 2, position.second - 1, result, color);
    checkRange(board, position.first + 2, position.second + 1, result, color);
    checkRange(board, position.first - 2, position.second - 1, result, color);
    checkRange(board, position.first - 2, position.second + 1, result, color);

    checkRange(board, position.first + 1, position.second - 2, result, color);
    checkRange(board, position.first + 1, position.second + 2, result, color);
    checkRange(board, position.first - 1, position.second - 2, result, color);
    checkRange(board, position.first - 1, position.second + 2, result, color);
}

QString Knight::name()
{
    return QString("Knight");
}

QString Knight::notation()
{
    return QString("N");
}

} //end namespace
