#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <memory>
#include "../Defines.h"

class Validator
{
    Validator();
public:

    static bool isValidMove(Defs::MovePrimitive, Defs::EColors playerColor);

    static bool isValidCell(int x, int y, Defs::EColors playerColor);
};

#endif // VALIDATOR_H
