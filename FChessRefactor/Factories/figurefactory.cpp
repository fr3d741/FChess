#include "figurefactory.h"

#include "../Figures/bishop.h"
#include "../Figures/king.h"
#include "../Figures/knight.h"
#include "../Figures/pawn.h"
#include "../Figures/queen.h"
#include "../Figures/rook.h"

#include "../Interfaces/figure.h"

namespace puppets
{

FigureFactory::FigureFactory()
{
    _texturePaths[ Defs::White | Defs::Pawn ]   = QString( ":/icon/figure/pawn_w.png" );
    _texturePaths[ Defs::White | Defs::Knight ] = QString( ":/icon/figure/knight_w.png" );
    _texturePaths[ Defs::White | Defs::Rook ]   = QString( ":/icon/figure/rook_w.png" );
    _texturePaths[ Defs::White | Defs::Bishop ] = QString( ":/icon/figure/bishop_w.png" );
    _texturePaths[ Defs::White | Defs::King ]   = QString( ":/icon/figure/king_w.png" );
    _texturePaths[ Defs::White | Defs::Queen ]  = QString( ":/icon/figure/queen_w.png" );

    _texturePaths[ Defs::Black | Defs::Pawn ]   = QString( ":/icon/figure/pawn_b.png" );
    _texturePaths[ Defs::Black | Defs::Knight ] = QString( ":/icon/figure/knight_b.png" );
    _texturePaths[ Defs::Black | Defs::Rook ]   = QString( ":/icon/figure/rook_b.png" );
    _texturePaths[ Defs::Black | Defs::Bishop ] = QString( ":/icon/figure/bishop_b.png" );
    _texturePaths[ Defs::Black | Defs::King ]   = QString( ":/icon/figure/king_b.png" );
    _texturePaths[ Defs::Black | Defs::Queen ]  = QString( ":/icon/figure/queen_b.png" );
}

FigureInterface* FigureFactory::createFigure( Defs::EColors color, Defs::EFigures figure )
{
    switch (figure)
    {
        case Defs::Pawn:
            return new Pawn( _texturePaths[color | figure], color, figure );
        case Defs::Knight:
            return new Knight( _texturePaths[color | figure], color, figure );
        case Defs::Rook:
            return new Rook( _texturePaths[color | figure], color, figure );
        case Defs::Bishop:
            return new Bishop( _texturePaths[color | figure], color, figure );
        case Defs::King:
            return new King( _texturePaths[color | figure], color, figure );
        case Defs::Queen:
            return new Queen( _texturePaths[color | figure], color, figure );
        default:
            return 0;
    }
}

} // end namespace
