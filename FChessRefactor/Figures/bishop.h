#ifndef BISHOP_H
#define BISHOP_H

#include "../figure.h"

namespace puppets
{

class Bishop : public Figure
{
public:
    Bishop( QString path, Defs::EColors color, Defs::EFigures figure );

    virtual bool isValidMove( Defs::Move step );

    virtual void reachableCells( Defs::state& result, QPair<int,int>& position );

protected:
    virtual void checkRange( int xFrom, int yFrom, int xTo, int yTo, Defs::state& resultState );

};

} // end namespace

#endif // BISHOP_H
