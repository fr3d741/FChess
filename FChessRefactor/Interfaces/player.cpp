#include "player.h"

Player::Player(Defs::EColors color, QObject *parent)
    :QObject(parent)
    ,_playerColor( color )
{
}

Player::~Player()
{
}

Defs::EColors Player::color()
{
    return _playerColor;
}

bool Player::isValidCell( Defs::Cell& sourceCell )
{
    return sourceCell.figure && ( sourceCell.figure & _playerColor );
}

bool Player::isValidCellForTarget( Defs::Cell* targetCell )
{
    if ( targetCell->figure && ( targetCell->figure & _playerColor ) )
    {
        return true;
    }

return false;
}
