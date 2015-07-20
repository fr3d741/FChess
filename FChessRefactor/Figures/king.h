#ifndef KING_H
#define KING_H

#include "../Interfaces/figure.h"

namespace puppets
{

class King : public FigureInterface
{
public:
    King( std::shared_ptr<Board> board, Defs::EColors color );

    virtual bool isValidMove( Defs::MovePrimitive step );

    virtual void reachableCells( Defs::state& , QPair<int,int>&  );

protected:

};

} //end namespace

#endif // KING_H
