#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Defines.h"

class Evaluator
{
    Evaluator();
public:
    static bool isCheckFor(Defs::EColors playerColor, Defs::Move move = Defs::Move() );

    static bool checkPositions( Defs::EColors, QList< QPair<int,int> >& pointList );

    static Defs::ESpecials defineSpecial(Defs::MovePrimitive& move);
};

#endif // EVALUATOR_H
