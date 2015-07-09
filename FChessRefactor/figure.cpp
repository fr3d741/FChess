#include "figure.h"

#include <QFileInfo>

#include "Figures/bishop.h"
#include "Figures/king.h"
#include "Figures/knight.h"
#include "Figures/pawn.h"
#include "Figures/queen.h"
#include "Figures/rook.h"

namespace puppets
{

    Figure::Figure( QString path, Defs::EColors color, Defs::EFigures figure )
        :_icon(0)
        ,_iconPix(0)
        ,_color( color )
        ,_figure( figure )
        ,_path( path )
    {
    }

    Figure::~Figure()
    {
        delete _icon;
        delete _iconPix;
    }

    const QPixmap& Figure::iconPixmap()
    {
        if ( !_iconPix )
        {
            _iconPix = new QPixmap( _path );
        }
        return *_iconPix;
    }

    const QImage& Figure::iconImage()
    {
        if ( !_icon )
        {
            _icon = new QImage( _path );
        }
        return *_icon;
    }

    Defs::EColors Figure::color()
    {
        return _color;
    }

    Defs::EFigures Figure::type()
    {
        return _figure;
    }

}

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

const std::auto_ptr< FigureFactory > FigureFactory::globalInstance()
{
    if ( !_globalInst.get() )
    {
        _globalInst = std::auto_ptr< FigureFactory >( new FigureFactory() );
    }
    return _globalInst;
}

} // end namespace

namespace puppets
{
    PuppetContainer::PuppetContainer()
    {
        (*this)[ Defs::White | Defs::Pawn ]     = FigureFactory::globalInstance()->createFigure( Defs::White, Defs::Pawn );
        (*this)[ Defs::Black | Defs::Pawn ]     = FigureFactory::globalInstance()->createFigure( Defs::Black, Defs::Pawn );

        (*this)[ Defs::White | Defs::Rook ]     = FigureFactory::globalInstance()->createFigure( Defs::White, Defs::Rook );
        (*this)[ Defs::Black | Defs::Rook ]     = FigureFactory::globalInstance()->createFigure( Defs::Black, Defs::Rook );

        (*this)[ Defs::White | Defs::Knight ]   = FigureFactory::globalInstance()->createFigure( Defs::White, Defs::Knight );
        (*this)[ Defs::Black | Defs::Knight ]   = FigureFactory::globalInstance()->createFigure( Defs::Black, Defs::Knight );

        (*this)[ Defs::White | Defs::Bishop ]   = FigureFactory::globalInstance()->createFigure( Defs::White, Defs::Bishop );
        (*this)[ Defs::Black | Defs::Bishop ]   = FigureFactory::globalInstance()->createFigure( Defs::Black, Defs::Bishop );

        (*this)[ Defs::White | Defs::King ]     = FigureFactory::globalInstance()->createFigure( Defs::White, Defs::King );
        (*this)[ Defs::Black | Defs::King ]     = FigureFactory::globalInstance()->createFigure( Defs::Black, Defs::King );

        (*this)[ Defs::White | Defs::Queen ]    = FigureFactory::globalInstance()->createFigure( Defs::White, Defs::Queen );
        (*this)[ Defs::Black | Defs::Queen ]    = FigureFactory::globalInstance()->createFigure( Defs::Black, Defs::Queen );
    }
}//end namespace
