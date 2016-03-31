#include "computer.h"

Computer::Computer(Defs::EColors color, QObject *parent)
    :Player(color, parent)
{
}

std::pair< int, int >& Computer::cellOverCursor()
{
    return _cellOverCursor;
}
