#ifndef DATA_H
#define DATA_H

#ifdef _WIN32
        #define AInt8 __int8
#else
        #define AInt8 int8_t;
#endif

#include <QList>

#include "../Defines.h"

namespace AiData {
    union Figure{
        AInt8 color : 2;
        AInt8 type : 6;
        AInt8 data;
    };

    struct Movement
    {
        AInt8 fromX :4;
        AInt8 fromY :4;
        AInt8 toX :4;
        AInt8 toY :4;
    };

    struct StateNode
    {
        int value;
        Movement move;
        QList<StateNode> childrenNodes;
    };

    int ValueOfState(Figure *state, int maxX, int maxY, Defs::EColors color);

}
#endif // DATA_H
