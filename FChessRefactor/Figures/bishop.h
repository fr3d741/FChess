#ifndef BISHOP_H
#define BISHOP_H

#include "../Interfaces/figure.h"

namespace puppets
{

class Bishop : public FigureInterface
{
public:
    Bishop( std::shared_ptr<Board> board, Defs::EColors color );

    virtual bool isValidMove( Defs::MovePrimitive step );

    virtual void reachableCells( Defs::state& result, QPair<int,int>& position );

    virtual QString name();

    virtual QString notation();

protected:
    virtual void checkRange( int xFrom, int yFrom, int xTo, int yTo, Defs::state& resultState );

    bool IsInputRangeInvalid(int xFrom, int yFrom, int xTo, int yTo);
};

} // end namespace

#endif // BISHOP_H
