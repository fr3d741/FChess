#pragma once

#include <Defines.h>

class IBoard;

class FigureGlobals {
public:
  FigureGlobals() = delete;
  ~FigureGlobals() = delete;

  static bool isValidMove(IBoard* board, Defs::EColors color, Ftype figure, Defs::MovePrimitive move);
  static bool isValidMove(IBoard* board, Ftype figure, Defs::MovePrimitive move);
  static void reachableCells(IBoard* board, Defs::state& result, QPair<int, int>& position, Defs::EColors color);
};