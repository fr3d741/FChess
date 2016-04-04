#ifndef DATA_H
#define DATA_H

#ifdef _WIN32
        //#define AInt8 __int8
        #define AInt8 int
#else
        #define AInt8 int8_t;
#endif

#include <QList>

#include "../Defines.h"

namespace AiData
{
    struct Figure
    {
        AInt8 color;
        AInt8 type;
        AInt8 data;
    };

    struct Position
    {
        AInt8 x;
        AInt8 y;
        AInt8 data;
    };

    struct Movement
    {
        Position from;
        Position to;
    };

    struct State
    {
        AInt8 cells[8][8];

        AInt8* operator[](int i)
        {
            return cells[i];
        }
    };

    struct StateNode
    {
        //State rootState;
        int value;
        Movement move;
        QList<StateNode> childrenNodes;
    };

    int ValueOfState(Figure *state, int maxX, int maxY, Defs::EColors color);

    QList<AiData::Position> ConvertToPositions(Defs::state& state);

    void BuildStateTree(StateNode& rootNode, State& state);
}
#endif // DATA_H
