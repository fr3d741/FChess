#include <QTextStream>

#include "data.h"

#include "../Interfaces/figure.h"
#include "../Factories/figurefactory.h"

namespace AiData {

//State StateNode::rootState;

int ValueOfState(Figure* state, int maxX, int maxY, Defs::EColors color)
{
    int sum = 0;
    for (int x = 0; x < maxX * maxY; ++x)
    {
        int value = 0;
        switch(state[x].type)
        {
            case Defs::King:
                value = 12;
                break;
            case Defs::Queen:
                value = 9;
                break;
            case Defs::Rook:
                value = 6;
                break;
            case Defs::Knight:
                value = 3;
                break;
            case Defs::Bishop:
                value = 2;
                break;
            case Defs::Pawn:
                value = 1;
            default:
                value = 0;
        }
        sum += value * (state[x].color & color?1:-1);
    }

return sum;
}


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
    for (int x = 0; x < 8; ++x)
        for (int y = 0; y < 8; ++y)
        {
            int value = 0;
            int figure = state[x][y];
            switch(figure & 0xFFFC)
            {
                case Defs::King:
                    value = 12;
                    break;
                case Defs::Queen:
                    value = 9;
                    break;
                case Defs::Rook:
                    value = 6;
                    break;
                case Defs::Knight:
                    value = 3;
                    break;
                case Defs::Bishop:
                    value = 2;
                    break;
                case Defs::Pawn:
                    value = 1;
                default:
                    value = 0;
            }
            sum += value * (figure & color?1:-1);
        }

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

}
