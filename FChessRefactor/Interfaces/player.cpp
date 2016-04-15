#include <QMetaType>
#include <memory>
#include "player.h"

Player::Player(Defs::EColors color, QObject *parent)
    :QObject(parent)
    ,_playerColor( color )
{
    //qRegisterMetaType<std::shared_ptr<Player>>();
    qRegisterMetaType<std::shared_ptr<Player>>("std::shared_ptr<Player>const&");
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

