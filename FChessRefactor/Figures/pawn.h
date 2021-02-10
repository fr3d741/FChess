#ifndef PAWN_H
#define PAWN_H

#include "../Interfaces/figure.h"

namespace puppets
{

class Pawn : public FigureInterface
{
public:
    Pawn(std::shared_ptr<IBoard> board, Defs::EColors color);

    virtual QString name();

    virtual QString notation();

    virtual Defs::ESpecials isSpecial(const Defs::MovePrimitive& step);

    static Defs::ESpecials isSpecial(IBoard* board, const Defs::MovePrimitive& step, Defs::EColors color);
    static bool IsMoveValid(IBoard* board, Defs::Position from, Defs::Position to, int step);
    static bool IsPositionOccupied(IBoard* board, QPair<int, int>& position, int sign, int offset);

protected:
    bool filterPawns(const Defs::Move& m);

    static void CheckAndSetFront(IBoard* board, Defs::state& result, int sign, QPair<int, int>& position, Defs::EColors color);

    static void CheckAndSetFrontDown(IBoard* board, int sign, QPair<int, int>& position, Defs::state& result, Defs::EColors color);

    static void CheckAndSetFrontUp(IBoard* board, QPair<int, int>& position, Defs::state& result, int sign, Defs::EColors color);

    bool IsMoveValid(Defs::Position from, Defs::Position to, int step);
};

} //end namespace

#endif // PAWN_H
