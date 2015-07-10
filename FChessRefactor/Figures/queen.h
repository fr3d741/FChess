#ifndef QUEEN_H
#define QUEEN_H

#include "../Interfaces/figure.h"

namespace puppets
{

class Queen : public FigureInterface
{
public:
    Queen( QString path, Defs::EColors color, Defs::EFigures figure );

    virtual bool isValidMove( Defs::Move step );

    virtual void reachableCells( Defs::state& result, QPair<int,int>& position );

protected:
    virtual void checkRange( int xFrom, int yFrom, int xDiff, int yDiff, Defs::state& resultState );

};

} //end namespace

#endif // QUEEN_H
