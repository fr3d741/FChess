#include <QDebug>

#include "evaluator.h"
#include "Facade/gameplayfacade.h"
#include "Interfaces/figure.h"
#include "Factories/figurefactory.h"
#include "board.h"

Defs::EColors playerColorGlobal;

bool filterOutPlayerCells(Defs::Cell& c)
{
    bool b = c.figure && !(c.figure & playerColorGlobal);
    //qDebug() << c.figure << ": " << (b?"true":"false");
    return b;
}

Evaluator::Evaluator()
{
}

bool Evaluator::isCheckFor(Defs::EColors playerColor, Defs::Move move)
{
    std::shared_ptr<Board> board = GameplayFacade::Instance()->GetBoard();
    std::shared_ptr<Board> replica = board->replicate(move);

    replica->applyMove(move);
    Defs::Position king_pos = replica->getFigurePosition(playerColor | Defs::King);
    playerColorGlobal = playerColor;
    //qDebug() << "******************************";
    QList<Defs::Position> figurePositions = replica->filterCells(&filterOutPlayerCells);
    while(!figurePositions.isEmpty())
    {
        Defs::Position pos = figurePositions.takeFirst();
        Defs::Cell c = replica->at(pos);
        Defs::MovePrimitive m{pos, king_pos};
        if ( puppets::FigureFactory::createFigure(replica, (Defs::EColors)(c.figure & 0x03), c.figure)->isValidMove(m) )
        {
            //qDebug() << c.figure << " attacks King";
            return true;
        }
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

Defs::ESpecials Evaluator::defineSpecial(Defs::MovePrimitive &move)
{
    std::shared_ptr<Board> board = GameplayFacade::Instance()->GetBoard();
    Defs::Cell& piece = board->cell(move.from);
    Defs::EColors color = (Defs::EColors)(piece.figure & 0x03);
    auto instance = puppets::FigureFactory::createFigure(board, color, piece.figure );

    return instance->isSpecial(move);
}
