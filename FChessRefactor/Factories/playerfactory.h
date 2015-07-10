#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include "../Interfaces/player.h"

class PlayerFactory
{
public:
    static Player* createPlayer( QString color, QString player );

    static Player* createPlayer( Defs::EColors color, QString player );

private:
    PlayerFactory();
};

#endif // PLAYERFACTORY_H
