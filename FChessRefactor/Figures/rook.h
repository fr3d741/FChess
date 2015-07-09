#ifndef ROOK_H
#define ROOK_H

#include "../figure.h"

namespace puppets
{

class Rook : public Figure
{
public:
    Rook( QString path, Defs::EColors color, Defs::EFigures figure );

    virtual bool isValidMove( Defs::Move step );

    virtual void reachableCells( Defs::state& result, QPair<int,int>& position );
protected:
    /*!
    * \brief checks the given range for which cell is empty, uses a step value of +/- 1 depending on range
    */
    virtual void checkRange( int xFrom, int yFrom, int xTo, int yTo, Defs::state& resultState );
};

}

#endif // ROOK_H
