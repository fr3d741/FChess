#ifndef HUMAN_H
#define HUMAN_H

#include <QPoint>
#include <QVariant>

#include "../Interfaces/player.h"

class Human : public Player
{
    Q_OBJECT
public:
    Human( Defs::EColors color = Defs::Invalid, QObject *parent = 0 );

    virtual bool isValidCell( Defs::Cell& cell );

    virtual bool isValidCellForTarget( Defs::Cell* cell );

    virtual bool eventFilter(QObject *, QEvent * event );

    virtual std::pair< int, int >& cellOverCursor();

signals:
    void signalMouseOver(int, int);

    void signalCellSelected(int, int);

    void signalMouseOverCell(QVariant);

    void signalMove(QVariant);
protected:
    QPoint getCellIndices(QPoint position);
    inline bool isValid(const Defs::Position& coord);
    inline void invalidate(Defs::Position &position);

protected:
    Defs::Position   _cellSelected;
    std::pair< int, int >   _cellOverCursor;

};

#endif // HUMAN_H
