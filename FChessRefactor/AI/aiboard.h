#ifndef AIBOARD_H
#define AIBOARD_H

#include "data.h"

#include "../Interfaces/IBoard.h"

namespace Ai {

class AiBoard : public IBoard
{
    AiData::State&  _state;
public:
    AiBoard(AiData::State& stateRepresentation);

    virtual int sizeVerical();

    virtual int sizeHorizontal();

    virtual int GetFigureInPosition(int x, int y);

    virtual bool TestPosition(int x, int y);

    virtual Defs::Cell& cell(const Defs::Position &);

    virtual QList<Defs::Move> GetHistory();

    virtual Defs::Move lastMove();

    virtual std::shared_ptr<IBoard> replicate(Defs::Move move);

    virtual Defs::Position getFigurePosition(int);

};

}
#endif // AIBOARD_H
