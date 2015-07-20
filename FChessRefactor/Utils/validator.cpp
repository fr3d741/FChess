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
    std::shared_ptr<Board> board = GameplayFacade::Instance()->GetBoard();
    Defs::Cell f = (*board)(move.from);
    Defs::Cell t = (*board)(move.to);

    bool fromValid = f.figure && ( f.figure & playerColor );
    bool toValid = !(t.figure & playerColor);

    if (!fromValid || !toValid)
        return false;

    std::shared_ptr<puppets::FigureInterface> instance = puppets::FigureFactory::createFigure(board, playerColor, f.figure);
    bool isFigureOk = instance->isValidMove(move);

    return isFigureOk;
}

bool Validator::isValidCell(int x, int y, Defs::EColors playerColor)
{
    std::shared_ptr<Board> board = GameplayFacade::Instance()->GetBoard();
    Defs::Cell f = (*board)[x][y];

return f.figure && ( f.figure & playerColor );
}
