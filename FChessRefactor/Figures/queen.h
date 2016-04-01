#ifndef QUEEN_H
#define QUEEN_H

#include "../Interfaces/figure.h"

namespace puppets
{

class Queen : public FigureInterface
{
public:
    Queen(std::shared_ptr<Board> board, Defs::EColors color);

    virtual bool isValidMove( Defs::MovePrimitive step );

    virtual void reachableCells( Defs::state& result, QPair<int,int>& position );

    virtual QString name();

    virtual QString notation();
protected:
    virtual void checkRange( int xFrom, int yFrom, int xDiff, int yDiff, Defs::state& resultState );

    bool IsPositionCoordinatesValid(int i, int j);
};

} //end namespace

#endif // QUEEN_H
