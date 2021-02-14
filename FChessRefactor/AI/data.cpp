#include <QTextStream>

#include <Figures/FigureGlobals.h>

#include "data.h"

#include "../Interfaces/figure.h"
#include "../Factories/figurefactory.h"
#include "aiboard.h"

namespace AiData {

Position ConvertToPosition(int i, int j)
{
    Position p;
    p.y = (AInt8)j;
    p.x = (AInt8)i;

    return p;
}

QList<Position> ConvertToPositions(Defs::state &state)
{
    QList<Position> list;
    for(int i = 0, c = 0; i < 8; ++i)
        for(int j = 0; j < 8; ++j, ++c)
            if (state.test(c))
            {
                Position p = ConvertToPosition(i, j);
                list.push_back(p);
            }

    return list;
}

int ValueOfState(State &state, Defs::EColors color)
{
    int sum = 0;
    auto cells = state.data();
    for (int i = 0; i < HORIZONTAL_SIZE * VERTICAL_SIZE; ++i)
    {
      switch (Defs::getColor(cells[i])) {
        case Defs::White:
          sum += cells[i];
          continue;
        case Defs::Black:
          sum -= cells[i] & 0x7F;
          continue;
        default:
          break;
      }
    }

    if (IsPlayerInCheckState(state, color))
        sum -= 11;

    return sum;
}

State Apply(Movement &move, State &onState)
{
    State replica = onState;
    replica[move.to.x][move.to.y] = replica[move.from.x][move.from.y];
    replica[move.from.x][move.from.y] = 0;

    return replica;
}

Position ConvertFrom(Defs::Position *)
{
    return Position();
}

bool operator==(const Movement &a, const Movement &b)
{
    return  a.from.x == b.from.x &&
            a.from.y == b.from.y &&
            a.to.x == b.to.x &&
            a.to.y == b.to.y;
}

QString toString(const StateNode &node)
{
    QString txt;
    QTextStream stream(&txt);
    stream << "player:" << (node.playerColor==Defs::White?"White":"Black") << "\n";
    stream << "value:" << node.value << "\n";
    stream << "Move " << QString("[%1,%2]=>[%3,%4]").arg(node.move.from.x).arg(node.move.from.y).arg(node.move.to.x).arg(node.move.to.y) << "\n";
    return txt;
}

bool IsPlayerInCheckState(State &state, Defs::EColors color)
{
    Position ofKing;
    Ftype king = Defs::King | color;
    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            if (state[i][j] != king)
                continue;
            ofKing.x = i;
            ofKing.y = j;
            goto kingFound;
        }
    }
kingFound:;
    auto board = std::make_shared<Ai::AiBoard>(state);
    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            AInt8 val = state[i][j];
            if (!val || Defs::getColor(val) == color)
                continue;

            Defs::MovePrimitive m;
            m.from.x = i;
            m.from.y = j;
            m.to.x = ofKing.x;
            m.to.y = ofKing.y;
            auto figure = (board, state[i][j]);
            if (FigureGlobals::isValidMove(board.get(), figure, m))
                return true;
        }
    }

    return false;
}

}
