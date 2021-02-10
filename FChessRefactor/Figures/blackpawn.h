#ifndef BLACKPAWN_H
#define BLACKPAWN_H

#include "pawn.h"

namespace puppets
{

class BlackPawn : public Pawn
{
public:
    BlackPawn(std::shared_ptr<IBoard> board);

    virtual void reachableCells( Defs::state& result, QPair<int,int>& position );

    virtual bool isValidMove( Defs::MovePrimitive step );

    static bool isValidMove(IBoard* board, Defs::MovePrimitive step);

    static void reachableCells(IBoard* board, Defs::state& result, QPair<int, int>& position);
};

}
#endif // BLACKPAWN_H
