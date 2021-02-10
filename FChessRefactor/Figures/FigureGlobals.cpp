#include <Figures/FigureGlobals.h>
#include <Figures/whitepawn.h>
#include <Figures/blackpawn.h>
#include <Figures/knight.h>
#include <Figures/rook.h>
#include <Figures/bishop.h>
#include <Figures/king.h>
#include <Figures/queen.h>

#include <exceptions.h>

using namespace puppets;

bool FigureGlobals::isValidMove(IBoard* board, int figure, Defs::MovePrimitive move){

  auto color = (Defs::EColors)(figure & 0x3);
  return isValidMove(board, color, figure, move);
}

bool FigureGlobals::isValidMove(IBoard* board, Defs::EColors color, int figure, Defs::MovePrimitive move) {

  //auto color = (Defs::EColors)(figure & 0x3);
  auto puppet = (Defs::EFigures)(figure & 0xFC);

  switch (puppet)
  {
  case Defs::Pawn:
    switch (color)
    {
    case Defs::White:
      return WhitePawn::isValidMove(board, move);
    case Defs::Black:
      return BlackPawn::isValidMove(board, move);
    default:
      throw new InvalidArgumentException(__FILE__ + __LINE__);
    }
    break;
  case Defs::Knight:
    return Knight::isValidMove(board, move);
  case Defs::Rook:
    return Rook::isValidMove(board, move);
  case Defs::Bishop:
    return Bishop::isValidMove(board, move);
  case Defs::King:
    return King::isValidMove(board, move, color);
  case Defs::Queen:
    return Queen::isValidMove(board, move);
  default:
    throw new InvalidArgumentException(__FILE__ + __LINE__);
  }
}