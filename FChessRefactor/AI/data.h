#ifndef DATA_H
#define DATA_H

#ifdef _WIN32
        //#define AInt8 __int8
        #define AInt8 int8_t
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
        Position(){}
        Position(int i, int j) : x(static_cast<AInt8>(i)), y(static_cast<AInt8>(j)) {}
        AInt8 x;
        AInt8 y;
    };

    struct Movement
    {
        Position from;
        Position to;
    };

    struct State
    {
    private:
        AInt8 cells[HORIZONTAL_SIZE * VERTICAL_SIZE];
    public:

        AInt8* operator[](int i)
        {
            return &cells[i * HORIZONTAL_SIZE];
        }

        AInt8* data() { return cells; }
    };

    struct StateNode
    {
        Defs::EColors playerColor;
        int value;
        Movement move;
        QList<std::shared_ptr<StateNode>> childrenNodes;
    };

    typedef std::shared_ptr<AiData::StateNode> NodePtr;

    //int ValueOfState(Figure *state, int maxX, int maxY, Defs::EColors color);
    int ValueOfState(State& state, Defs::EColors color);
    bool IsPlayerInCheckState(State& state, Defs::EColors color);
    Position ConvertFrom(Defs::Position*);
    State Apply(Movement& move, State& onState);
    bool operator==(const Movement& a, const Movement& b);

    Position ConvertToPosition(int i, int j);
    QList<AiData::Position> ConvertToPositions(Defs::state& state);

    QString toString(const StateNode& node);
}
#endif // DATA_H
