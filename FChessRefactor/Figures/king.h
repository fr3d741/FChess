#ifndef KING_H
#define KING_H

#include "../figure.h"

namespace puppets
{

class King : public Figure
{
public:
    King( QString path, Defs::EColors color, Defs::EFigures figure );

    virtual bool isValidMove( Defs::Move step );

    virtual void reachableCells( Defs::state& , QPair<int,int>&  );

protected:

};

} //end namespace

#endif // KING_H
