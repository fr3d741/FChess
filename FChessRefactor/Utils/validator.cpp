#include <QDebug>

#include <Figures/FigureGlobals.h>
#include "validator.h"
#include "../Facade/gameplayfacade.h"
#include "../Interfaces/figure.h"
#include "../Factories/figurefactory.h"
#include "../board.h"

Validator::Validator()
{
}

bool Validator::isValidMove(Defs::MovePrimitive move, Defs::EColors playerColor)
{
    std::shared_ptr<IBoard> board = GameplayFacade::Instance()->GetBoard();
    Defs::Cell f = board->cell(move.from);
    Defs::Cell t = board->cell(move.to);

    bool fromValid = f.figure && (Defs::getColor(f.figure) == playerColor );
    bool toValid = t.figure == 0 || (Defs::getColor(t.figure) != playerColor);

    if (!fromValid || !toValid)
    {
        qDebug() << "Invalid move: " << QString("%1:%2=>%3:%4").arg(Defs::toString(move.from)).arg(f.figure).arg(Defs::toString(move.to)).arg(t.figure);
        return false;
    }

    return FigureGlobals::isValidMove(board.get(), playerColor, f.figure, move);
}

bool Validator::isValidCell(int x, int y, Defs::EColors playerColor)
{
    std::shared_ptr<IBoard> board = GameplayFacade::Instance()->GetBoard();
    Defs::Cell f = board->cell({x, y});

return f.figure && (Defs::getColor(f.figure) == playerColor );
}
