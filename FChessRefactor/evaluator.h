#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Defines.h"

//extern Defs::Cell** Defs::boardState;

class Evaluator
{
    Evaluator();
public:
    static bool isCheckFor(Defs::EColors playerColor, Defs::MovePrimitive move = Defs::MovePrimitive() );

    static bool check( Defs::EColors );

    static bool checkPositions( Defs::EColors, QList< QPair<int,int> >& pointList );
};

#endif // EVALUATOR_H
