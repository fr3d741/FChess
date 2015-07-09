#include <QFileInfo>

#include "figure.h"
#include "Factories/figurefactory.h"

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
    PuppetContainer::PuppetContainer()
    {
        (*this)[ Defs::White | Defs::Pawn ]     = FigureFactory::Instance()->createFigure( Defs::White, Defs::Pawn );
        (*this)[ Defs::Black | Defs::Pawn ]     = FigureFactory::Instance()->createFigure( Defs::Black, Defs::Pawn );

        (*this)[ Defs::White | Defs::Rook ]     = FigureFactory::Instance()->createFigure( Defs::White, Defs::Rook );
        (*this)[ Defs::Black | Defs::Rook ]     = FigureFactory::Instance()->createFigure( Defs::Black, Defs::Rook );

        (*this)[ Defs::White | Defs::Knight ]   = FigureFactory::Instance()->createFigure( Defs::White, Defs::Knight );
        (*this)[ Defs::Black | Defs::Knight ]   = FigureFactory::Instance()->createFigure( Defs::Black, Defs::Knight );

        (*this)[ Defs::White | Defs::Bishop ]   = FigureFactory::Instance()->createFigure( Defs::White, Defs::Bishop );
        (*this)[ Defs::Black | Defs::Bishop ]   = FigureFactory::Instance()->createFigure( Defs::Black, Defs::Bishop );

        (*this)[ Defs::White | Defs::King ]     = FigureFactory::Instance()->createFigure( Defs::White, Defs::King );
        (*this)[ Defs::Black | Defs::King ]     = FigureFactory::Instance()->createFigure( Defs::Black, Defs::King );

        (*this)[ Defs::White | Defs::Queen ]    = FigureFactory::Instance()->createFigure( Defs::White, Defs::Queen );
        (*this)[ Defs::Black | Defs::Queen ]    = FigureFactory::Instance()->createFigure( Defs::Black, Defs::Queen );
    }
}//end namespace
