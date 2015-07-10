#include "playerfactory.h"

#include "../Players/human.h"
#include "../Players/tcpiplayer.h"

Player* PlayerFactory::createPlayer( Defs::EColors color, QString player )
{
    if ( player == "Human" )
    {
        return new Human( color );
    }
    else if ( player == "Remote Human")
    {
        return new TCPIPlayer( color );
    }

return 0;
}


Player* PlayerFactory::createPlayer( QString color, QString player )
{
    Defs::EColors col = Defs::Invalid;
    if ( color == "White" )
    {
        col = Defs::White;
    }
    else if ( color == "Black" )
    {
        col = Defs::Black;
    }

    if ( player == "Human" )
    {
        return new Human( col );
    }

return 0;
}
