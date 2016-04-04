#ifndef AIBOARD_H
#define AIBOARD_H

#include "data.h"

#include "../Interfaces/IBoard.h"

namespace Ai {

class AiBoard : public IBoard
{
    AInt8 cells[8][8];
public:
    AiBoard();

    virtual int sizeVerical();

    virtual int sizeHorizontal();

    virtual int GetFigureInPosition(int x, int y);

    virtual bool TestPosition(int x, int y);

    virtual Defs::Cell& cell(const Defs::Position &indexPair);

    virtual QList<Defs::Move> GetHistory();

    virtual Defs::Move lastMove();

    virtual std::shared_ptr<IBoard> replicate(Defs::Move move);

    virtual Defs::Position getFigurePosition(int value);

};

}
#endif // AIBOARD_H
