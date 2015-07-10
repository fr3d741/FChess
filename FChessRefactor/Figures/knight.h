#ifndef KNIGHT_H
#define KNIGHT_H

#include "../Interfaces/figure.h"

namespace puppets
{

class Knight : public FigureInterface
{
public:
    Knight( QString path, Defs::EColors color, Defs::EFigures figure );

    virtual bool isValidMove( Defs::Move step );

    virtual void reachableCells( Defs::state& result, QPair<int,int>& position );

protected:
    virtual void checkRange( int xFrom, int yFrom, Defs::state& resultState );

};

} //end namespace

#endif // KNIGHT_H
