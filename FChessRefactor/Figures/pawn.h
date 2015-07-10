#ifndef PAWN_H
#define PAWN_H

#include "../Interfaces/figure.h"

namespace puppets
{

class Pawn : public FigureInterface
{
public:
    Pawn( QString path, Defs::EColors color, Defs::EFigures figure );

    virtual bool isValidMove( Defs::Move step );

    virtual void reachableCells( Defs::state& result, QPair<int,int>& position );

protected:

};

} //end namespace

#endif // PAWN_H
