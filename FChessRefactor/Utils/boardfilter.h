#ifndef BOARDFILTER_H
#define BOARDFILTER_H

#include <QList>

#include "../Defines.h"
#include "../Interfaces/IBoard.h"

typedef bool (*FncPtr)(Defs::Cell& c);

class BoardFilter
{
    std::shared_ptr<IBoard> _board;
public:
    BoardFilter(std::shared_ptr<IBoard> board);

    QList<Defs::Position> filterCells(FncPtr filterFunction);

    QList<Defs::Move> filterHistory(std::function<bool(const Defs::Move&)>& filterFunc);

};

#endif // BOARDFILTER_H
