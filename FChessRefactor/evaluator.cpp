#include "evaluator.h"
#include "Interfaces/figure.h"
#include "board.h"

Evaluator::Evaluator()
{
}

bool Evaluator::check( Defs::EColors color )
{
    QPair<int, int> pos = Defs::getFigurePosition( color | Defs::King, color );
    Defs::state result;
    Defs::state& reference = Defs::WhiteBlackState._board;

    //for ( QMap< int, puppets::Figure* >::iterator it = puppets::ChessFigures.begin(); it != puppets::ChessFigures.end(); ++it )
    for( int i = 0; i < (int)reference.size(); ++i )
    {
        result.reset();
        QPair<int,int> fpos = Defs::getPosition( i );
        int figure = Board::boardState[fpos.first][fpos.second].figure;
        if ( !figure )
        {
            continue;
        }
        puppets::PuppetContainer::Instance()->value(figure)->reachableCells( result, fpos );
        if ( Defs::testBit( pos.first, pos.second, result ) )
        {
            return true;
        }
    }
return false;
}

bool Evaluator::checkPositions( Defs::EColors color, QList< QPair<int,int> >& pointList )
{
    Defs::state result;
    Defs::state& reference = Defs::WhiteBlackState._board;

    for( int i = 0; i < (int)reference.size(); ++i )
    {
        result.reset();
        QPair<int,int> fpos = Defs::getPosition( i );
        int figure = Board::boardState[fpos.first][fpos.second].figure;
        if ( !figure || (figure & color) )
        {
            continue;
        }

        puppets::PuppetContainer::Instance()->value(figure)->reachableCells( result, fpos );
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
