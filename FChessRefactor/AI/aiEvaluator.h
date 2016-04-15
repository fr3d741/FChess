#ifndef EVALUATOR_H
#define EVALUATOR_H

class IBoard;

#include "../Defines.h"

namespace Ai
{

bool isPlayerInCheck(Defs::EColors playerColor, std::shared_ptr<IBoard> board);

bool checkPositions(Defs::EColors, std::shared_ptr<IBoard> board, QList< QPair<int,int> >& pointList);

Defs::ESpecials defineSpecial(Defs::MovePrimitive& move, std::shared_ptr<IBoard> board);

}

#endif // EVALUATOR_H
