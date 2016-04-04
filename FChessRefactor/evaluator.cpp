#include <QDebug>

#include "evaluator.h"
#include "Facade/gameplayfacade.h"
#include "Interfaces/figure.h"
#include "Factories/figurefactory.h"
#include "Utils/boardfilter.h"

Defs::EColors playerColorGlobal;

bool filterOutPlayerCells(Defs::Cell& c)
{
    bool b = c.figure && !(c.figure & playerColorGlobal);
    return b;
}

Evaluator::Evaluator()
{
}

bool Evaluator::isCheckFor(Defs::EColors playerColor, Defs::Move move)
{
    std::shared_ptr<IBoard> board = GameplayFacade::Instance()->GetBoard();
    std::shared_ptr<IBoard> replica = board->replicate(move);
    BoardFilter filter = BoardFilter(replica);

    //replica->applyMove(move);
    Defs::Position king_pos = replica->getFigurePosition(playerColor | Defs::King);
    playerColorGlobal = playerColor;

    QList<Defs::Position> figurePositions = filter.filterCells(&filterOutPlayerCells);
    while(!figurePositions.isEmpty())
    {
        Defs::Position pos = figurePositions.takeFirst();
        Defs::Cell c = replica->cell(pos);
        Defs::MovePrimitive m{pos, king_pos};
        if ( puppets::FigureFactory::createFigure(replica, (Defs::EColors)(c.figure & 0x03), c.figure)->isValidMove(m) )
        {
            return true;
        }
    }
return false;
}

bool Evaluator::check( Defs::EColors color )
{
    std::shared_ptr<IBoard> board = GameplayFacade::Instance()->GetBoard();
    Defs::Position pos = board->getFigurePosition(color | Defs::King);
    Defs::state result;

    for( int i = 0; i < (int)board->sizeHorizontal(); ++i )
        for( int j = 0; j < (int)board->sizeVerical(); ++j )
        {
            result.reset();
            QPair<int,int> fpos = QPair<int,int>( i, j );
            int figure = board->GetFigureInPosition(i, j);
            if ( !figure )
                continue;

            puppets::FigureFactory::createFigure(board, color, figure)->reachableCells( result, fpos );
            if ( Defs::testBit( pos.x, pos.y, result ) )
                return true;

        }
return false;
}

bool Evaluator::checkPositions( Defs::EColors color, QList< QPair<int,int> >& pointList )
{
    std::shared_ptr<IBoard> board = GameplayFacade::Instance()->GetBoard();
    Defs::state result;

    for( int i = 0; i < (int)board->sizeHorizontal(); ++i )
        for( int j = 0; j < (int)board->sizeVerical(); ++j )
        {
            result.reset();
            QPair<int,int> fpos = QPair<int,int>(i, j);
            int figure = board->GetFigureInPosition(fpos.first, fpos.second);
            if ( !figure || (figure & color) )
                continue;

            puppets::FigureFactory::createFigure(board, color, figure)->reachableCells( result, fpos );
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

Defs::ESpecials Evaluator::defineSpecial(Defs::MovePrimitive &move)
{
    std::shared_ptr<IBoard> board = GameplayFacade::Instance()->GetBoard();
    Defs::Cell& piece = board->cell(move.from);
    Defs::EColors color = (Defs::EColors)(piece.figure & 0x03);
    auto instance = puppets::FigureFactory::createFigure(board, color, piece.figure );

    return instance->isSpecial(move);
}
