#include "evaluator.h"
#include "Facade/gameplayfacade.h"
#include "Interfaces/figure.h"
#include "Factories/figurefactory.h"
#include "board.h"

Defs::EColors playerColorGlobal;

Evaluator::Evaluator()
{
}

bool filterOutPlayerCells(Defs::Cell& c)
{
    return c.figure && !(c.figure & playerColorGlobal);
}

bool Evaluator::isCheckFor(Defs::EColors playerColor, Defs::MovePrimitive move)
{
    std::shared_ptr<Board> board = GameplayFacade::Instance()->GetBoard();
    std::shared_ptr<Board> replica = board->replicate(move);

    std::pair<int, int> king_pos = replica->getFigurePosition(playerColor | Defs::King);
    playerColorGlobal = playerColor;
    QList<std::pair<int, int> > figurePositions = replica->filterCells(&filterOutPlayerCells);
    while(!figurePositions.isEmpty())
    {
        std::pair<int, int> pos = figurePositions.takeFirst();
        Defs::Cell c = replica->at(pos);
        Defs::MovePrimitive m{pos, king_pos};
        if ( puppets::FigureFactory::createFigure(board, playerColor, c.figure)->isValidMove(m) )
            return true;
    }
return false;
}

bool Evaluator::check( Defs::EColors color )
{
    std::shared_ptr<Board> board = GameplayFacade::Instance()->GetBoard();
    Defs::Cell** boardState = board->BoardState();
    QPair<int, int> pos = Defs::getFigurePosition( color | Defs::King, color, board->WhiteBlackState() );
    Defs::state result;
    Defs::state& reference = board->WhiteBlackState()._board;

    //for ( QMap< int, puppets::Figure* >::iterator it = puppets::ChessFigures.begin(); it != puppets::ChessFigures.end(); ++it )
    for( int i = 0; i < (int)reference.size(); ++i )
    {
        result.reset();
        QPair<int,int> fpos = Defs::getPosition( i );
        int figure = boardState[fpos.first][fpos.second].figure;
        if ( !figure )
        {
            continue;
        }
        puppets::FigureFactory::createFigure(board, color, figure)->reachableCells( result, fpos );
        if ( Defs::testBit( pos.first, pos.second, result ) )
        {
            return true;
        }
    }
return false;
}

bool Evaluator::checkPositions( Defs::EColors color, QList< QPair<int,int> >& pointList )
{
    std::shared_ptr<Board> board = GameplayFacade::Instance()->GetBoard();
    Defs::Cell** boardState = board->BoardState();
    Defs::state result;
    Defs::state& reference = board->WhiteBlackState()._board;

    for( int i = 0; i < (int)reference.size(); ++i )
    {
        result.reset();
        QPair<int,int> fpos = Defs::getPosition( i );
        int figure = boardState[fpos.first][fpos.second].figure;
        if ( !figure || (figure & color) )
        {
            continue;
        }

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
