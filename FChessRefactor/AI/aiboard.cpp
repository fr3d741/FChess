#include "aiboard.h"

namespace Ai
{

AiBoard::AiBoard(AiData::State &stateRepresentation)
    :_state(stateRepresentation)
{
}


int AiBoard::sizeVerical()
{
    return 8;
}

int AiBoard::sizeHorizontal()
{
    return 8;
}

int AiBoard::GetFigureInPosition(int x, int y)
{
    return _state.cells[x][y];
}

bool AiBoard::TestPosition(int x, int y)
{
    return GetFigureInPosition(x, y) != 0;
}

Defs::Cell &AiBoard::cell(const Defs::Position &indexPair)
{
    return Defs::Cell();
}

QList<Defs::Move> AiBoard::GetHistory()
{
    return QList<Defs::Move>();
}

Defs::Move AiBoard::lastMove()
{
    return Defs::Move();
}

std::shared_ptr<IBoard> AiBoard::replicate(Defs::Move move)
{
    return std::shared_ptr<IBoard>(nullptr);
}

Defs::Position AiBoard::getFigurePosition(int value)
{
    return Defs::Position();
}

}
