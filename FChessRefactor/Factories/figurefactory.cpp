#include "figurefactory.h"

#include "../Figures/bishop.h"
#include "../Figures/king.h"
#include "../Figures/knight.h"
#include "../Figures/pawn.h"
#include "../Figures/queen.h"
#include "../Figures/rook.h"

#include "../figure.h"

namespace puppets
{

std::auto_ptr< FigureFactory > FigureFactory::_globalInst;

FigureFactory::FigureFactory()
{
    _texturePaths[ Defs::White | Defs::Pawn ]   = QString( "resources/pawn_w.png" );
    _texturePaths[ Defs::White | Defs::Knight ] = QString( "resources/knight_w.png" );
    _texturePaths[ Defs::White | Defs::Rook ]   = QString( "resources/rook_w.png" );
    _texturePaths[ Defs::White | Defs::Bishop ] = QString( "resources/bishop_w.png" );
    _texturePaths[ Defs::White | Defs::King ]   = QString( "resources/king_w.png" );
    _texturePaths[ Defs::White | Defs::Queen ]  = QString( "resources/queen_w.png" );

    _texturePaths[ Defs::Black | Defs::Pawn ]   = QString( "resources/pawn_b.png" );
    _texturePaths[ Defs::Black | Defs::Knight ] = QString( "resources/knight_b.png" );
    _texturePaths[ Defs::Black | Defs::Rook ]   = QString( "resources/rook_b.png" );
    _texturePaths[ Defs::Black | Defs::Bishop ] = QString( "resources/bishop_b.png" );
    _texturePaths[ Defs::Black | Defs::King ]   = QString( "resources/king_b.png" );
    _texturePaths[ Defs::Black | Defs::Queen ]  = QString( "resources/queen_b.png" );
}

Figure* FigureFactory::createFigure( Defs::EColors color, Defs::EFigures figure )
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

const std::auto_ptr< FigureFactory > FigureFactory::Instance()
{
    if ( !_globalInst.get() )
    {
        _globalInst = std::auto_ptr< FigureFactory >( new FigureFactory() );
    }
    return _globalInst;
}

} // end namespace
