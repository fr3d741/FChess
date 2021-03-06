#ifndef IBOARD_H
#define IBOARD_H

#include <QList>

#include <Defines.h>

class IBoard
{
public:
    virtual int sizeVerical() = 0;

    virtual int sizeHorizontal() = 0;

    virtual Ftype GetFigureInPosition(int, int) = 0;

    virtual bool TestPosition(int, int) = 0;

    virtual Defs::Cell& cell(const Defs::Position &indexPair) = 0;

    virtual QList<Defs::Move> GetHistory() = 0;

    virtual Defs::Move lastMove() = 0;

    virtual std::shared_ptr<IBoard> replicate(Defs::Move move) = 0;

    virtual Defs::Position getFigurePosition(int value) = 0;
};

#endif // IBOARD_H
