#ifndef WHITEPAWN_H
#define WHITEPAWN_H

#include "pawn.h"

namespace puppets {

class WhitePawn : public Pawn
{
public:
    WhitePawn(std::shared_ptr<Board> board);

    virtual void reachableCells( Defs::state& result, QPair<int,int>& position );

    virtual bool isValidMove( Defs::MovePrimitive step );
};

}

#endif // WHITEPAWN_H
