#ifndef COMPUTER_H
#define COMPUTER_H

#include "../Interfaces/player.h"

class Computer : public Player
{
    std::pair< int, int > _cellOverCursor;
public:
    Computer(Defs::EColors color, QObject *parent = 0);

    virtual std::pair< int, int >& cellOverCursor();
};

#endif // COMPUTER_H
