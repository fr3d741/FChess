#ifndef KNIGHT_H
#define KNIGHT_H

#include "../Interfaces/figure.h"

namespace puppets
{

class Knight : public FigureInterface
{
public:
    Knight(std::shared_ptr<Board> board, Defs::EColors color);

    virtual bool isValidMove( Defs::MovePrimitive step );

    virtual void reachableCells( Defs::state& result, QPair<int,int>& position );

protected:
    virtual void checkRange( int xFrom, int yFrom, Defs::state& resultState );

};

} //end namespace

#endif // KNIGHT_H
