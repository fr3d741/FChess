#include <QDebug>

#include <Figures/FigureGlobals.h>

#include <Factories/figurefactory.h>

#include "aiEvaluator.h"
#include "../Interfaces/IBoard.h"
#include "../Interfaces/figure.h"



namespace Ai {

Defs::EColors playerColorGlobal;

bool filterOutPlayerCells(Defs::Cell& c)
{
    bool b = c.figure && !(c.figure & playerColorGlobal);
    return b;
}

bool isPlayerInCheck(Defs::EColors playerColor, std::shared_ptr<IBoard> board)
{
    Defs::Position king_pos = board->getFigurePosition(playerColor | Defs::King);
    playerColorGlobal = playerColor;

    for (int i = 0; i < board->sizeHorizontal(); ++i)
    {
        for (int j = 0; j < board->sizeVerical(); ++j)
        {
            int figure = board->GetFigureInPosition(i, j);
            if (!figure || !(figure & playerColor))
                continue;

            Defs::MovePrimitive m{{i,j}, king_pos};
            if (FigureGlobals::isValidMove(board.get(), figure, m))
            {
                return true;
            }

        }
    }
return false;
}

bool checkPositions(Defs::EColors color, std::shared_ptr<IBoard> board, QList< QPair<int,int> >& pointList)
{
    Defs::state result;

    for( int i = 0; i < board->sizeHorizontal(); ++i )
        for( int j = 0; j < board->sizeVerical(); ++j )
        {
            result.reset();
            QPair<int,int> fpos = QPair<int,int>(i, j);
            int figure = board->GetFigureInPosition(fpos.first, fpos.second);
            if ( !figure || (figure & color) )
                continue;

            //puppets::FigureFactory::createFigure(board, color, figure)->reachableCells( result, fpos );
            FigureGlobals::reachableCells(board.get(), result, fpos, color);
            for ( QList< QPair<int,int> >::iterator it = pointList.begin(); it != pointList.end(); ++it )
            {
                QPair<int, int>& pos = (*it);
                if ( Defs::testBit( pos.first, pos.second, result ) )
                {
                    return true;
                }
            }
        }

    return false;
}

Defs::ESpecials defineSpecial(Defs::MovePrimitive &move, std::shared_ptr<IBoard> board)
{
    Defs::Cell& piece = board->cell(move.from);
    Defs::EColors color = (Defs::EColors)(piece.figure & 0x03);
    auto instance = puppets::FigureFactory::createFigure(board, color, piece.figure );

    return instance->isSpecial(move);
}

}
