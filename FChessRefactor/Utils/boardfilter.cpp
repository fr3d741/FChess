#include "boardfilter.h"

BoardFilter::BoardFilter(std::shared_ptr<IBoard> board)
    :_board(board.get())
{
}
BoardFilter::BoardFilter(IBoard* board)
    :_board(board)
{
}

QList<Defs::Position> BoardFilter::filterCells(FncPtr filterFunction)
{
    QList<Defs::Position> result;

    for( int y = 0; y < _board->sizeVerical(); ++y )
        for( int x = 0; x < _board->sizeHorizontal(); ++x )
            if ((*filterFunction)(_board->cell({x, y})))
            {
                result.push_back( {x,y} );
            }

    return result;
}

QList<Defs::Move> BoardFilter::filterHistory(std::function<bool(const Defs::Move&)>& filterFunc)
{
    QList<Defs::Move> result;
    QList<Defs::Move> history = _board->GetHistory();

    while(!history.isEmpty())
    {
        Defs::Move item = history.takeFirst();
        if (filterFunc(item))
        {
            result.push_back( item );
        }
    }

    return result;
}

