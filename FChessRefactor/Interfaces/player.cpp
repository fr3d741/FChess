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
