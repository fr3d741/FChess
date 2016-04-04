#include "data.h"

int AiData::ValueOfState(AiData::Figure* state, int maxX, int maxY, Defs::EColors color)
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
