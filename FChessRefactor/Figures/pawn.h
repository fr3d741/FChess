#ifndef PAWN_H
#define PAWN_H

#include "../Interfaces/figure.h"

namespace puppets
{

class Pawn : public FigureInterface
{
public:
    Pawn(std::shared_ptr<Board> board, Defs::EColors color);

    virtual bool isValidMove( Defs::MovePrimitive step );

    virtual void reachableCells( Defs::state& result, QPair<int,int>& position );

    virtual QString name();

    virtual QString notation();

    virtual Defs::ESpecials isSpecial(const Defs::MovePrimitive& step);

protected:
    bool filterPawns(const Defs::Move& m);

};

} //end namespace

#endif // PAWN_H
