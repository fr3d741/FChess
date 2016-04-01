#ifndef ROOK_H
#define ROOK_H

#include "../Interfaces/figure.h"

namespace puppets
{

class Rook : public FigureInterface
{
public:
    Rook(std::shared_ptr<Board> board, Defs::EColors color);

    virtual bool isValidMove( Defs::MovePrimitive step );

    virtual void reachableCells( Defs::state& result, QPair<int,int>& position );

    virtual QString name();

    virtual QString notation();

protected:
    /*!
    * \brief checks the given range for which cell is empty, uses a step value of +/- 1 depending on range
    */
    virtual void checkRange( int xFrom, int yFrom, int xTo, int yTo, Defs::state& resultState );

    bool IsInputRangeInvalid(int yFrom, int xTo, int yTo, int xFrom);
};

}

#endif // ROOK_H
