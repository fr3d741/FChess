#ifndef HUMAN_H
#define HUMAN_H

#include "../Interfaces/player.h"

class Human : public Player
{
public:
    Human( Defs::EColors color = Defs::Invalid, QObject *parent = 0 );

    virtual bool isValidCell( Defs::Cell& cell );

    virtual bool isValidCellForTarget( Defs::Cell* cell );

    virtual bool eventFilter( QObject * watched, QEvent * event );

    virtual std::pair< int, int >& cellOverCursor();
protected:
    std::pair< int, int >   _cellOverCursor;

    std::pair< int, int >   _cellSelected;

};

#endif // HUMAN_H
