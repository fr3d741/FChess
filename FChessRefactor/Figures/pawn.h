#ifndef PAWN_H
#define PAWN_H

#include "../Interfaces/figure.h"

namespace puppets
{

class Pawn : public FigureInterface
{
public:
    Pawn(std::shared_ptr<Board> board, Defs::EColors color);

    virtual QString name();

    virtual QString notation();

    virtual Defs::ESpecials isSpecial(const Defs::MovePrimitive& step);

protected:
    bool filterPawns(const Defs::Move& m);

    void CheckAndSetFront(Defs::state& result, int sign, QPair<int,int>& position);

    void CheckAndSetFrontDown(int sign, QPair<int,int>& position, Defs::Cell** boardState, Defs::state& result);

    void CheckAndSetFrontUp(QPair<int,int>& position, Defs::state& result, Defs::Cell** boardState, int sign);

    bool IsPositionOccupied(QPair<int,int>& position, int sign, int offset);

    bool IsSameColor(QPair<int,int>& position, Defs::Cell** boardState, int sign, int offset);
};

} //end namespace

#endif // PAWN_H
