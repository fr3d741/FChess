#include "aiboard.h"

AiBoard::AiBoard()
{
}


int Ai::AiBoard::sizeVerical()
{
    return 8;
}

int Ai::AiBoard::sizeHorizontal()
{
    return 8;
}

int Ai::AiBoard::GetFigureInPosition(int x, int y)
{
    return state[x][y];
}

bool Ai::AiBoard::TestPosition(int x, int y)
{
    return GetFigureInPosition(x, y) != 0;
}

Defs::ColorState &Ai::AiBoard::State()
{
    return _colorState;
}

Defs::Cell &Ai::AiBoard::cell(const Defs::Position &indexPair)
{

}

QList<Defs::Move> Ai::AiBoard::filterHistory(std::function<bool (const Defs::Move &)> &filterFunc)
{
    return QList<Defs::Move>();
}

QList<Defs::Position> Ai::AiBoard::filterCells(FncPtr filterFunction)
{
    return QList<Defs::Position>();
}

Defs::Move Ai::AiBoard::lastMove()
{
    return Defs::Move;
}
