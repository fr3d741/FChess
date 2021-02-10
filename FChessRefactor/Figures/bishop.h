#ifndef BISHOP_H
#define BISHOP_H

#include "../Interfaces/figure.h"

namespace puppets
{

class Bishop : public FigureInterface
{
public:
    Bishop(std::shared_ptr<IBoard> board, Defs::EColors color );

    virtual bool isValidMove( Defs::MovePrimitive step );

    virtual void reachableCells( Defs::state& result, QPair<int,int>& position );

    virtual QString name();

    virtual QString notation();

    static bool isValidMove(IBoard* board, Defs::MovePrimitive step);

    static void reachableCells(IBoard* board, Defs::state& result, QPair<int, int>& position, Defs::EColors color);

protected:
};

} // end namespace

#endif // BISHOP_H
