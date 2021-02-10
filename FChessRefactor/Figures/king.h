#ifndef KING_H
#define KING_H

#include "../Interfaces/figure.h"

namespace puppets
{

class King : public FigureInterface
{
public:
    King(std::shared_ptr<IBoard> board, Defs::EColors color );

    static bool isValidMove(IBoard* board, Defs::MovePrimitive step, Defs::EColors color);

    virtual bool isValidMove( Defs::MovePrimitive step );

    virtual void reachableCells( Defs::state& , QPair<int,int>&  );

    virtual Defs::ESpecials isSpecial(const Defs::MovePrimitive& move);

    virtual QString name();

    virtual QString notation();
private:
};

} //end namespace

#endif // KING_H
