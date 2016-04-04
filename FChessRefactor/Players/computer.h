#ifndef COMPUTER_H
#define COMPUTER_H

#include <QVariant>

#include "../Interfaces/player.h"

class Computer : public Player
{
    Q_OBJECT
    std::pair< int, int > _cellOverCursor;
public:
    Computer(Defs::EColors color, QObject *parent = 0);

    virtual std::pair< int, int >& cellOverCursor();

signals:
    void signalMove(QVariant);

protected slots:
    void slotPlayerChanged(std::shared_ptr<Player> player);


};

#endif // COMPUTER_H
