#pragma once

#include <Defines.h>

class IBoard;

class FigureGlobals {
public:
  FigureGlobals() = delete;
  ~FigureGlobals() = delete;

  static bool isValidMove(IBoard* board, Defs::EColors color, int figure, Defs::MovePrimitive move);
  static bool isValidMove(IBoard* board, int figure, Defs::MovePrimitive move);
};