#define TEXTURE_W 44
#define TEXTURE_H 44

#include <QFileInfo>

#include "figure.h"
#include "../Factories/figurefactory.h"
#include "../board.h"

namespace puppets
{

    FigureInterface::FigureInterface(std::shared_ptr<Board> board, Defs::EColors color, int figure )
        :_icon(0)
        ,_iconPix(0)
        ,_color( color )
        ,_figure( (Defs::EFigures)figure )
        ,_path()
        ,_board(board)
    {
        _path = FigureFactory::IconPath(color | figure);
    }

    FigureInterface::~FigureInterface()
    {
        delete _icon;
        delete _iconPix;
    }

    const QPixmap& FigureInterface::iconPixmap()
    {
        if ( !_iconPix )
        {
            _iconPix = new QPixmap( _path );
        }
        return *_iconPix;
    }

    const QImage& FigureInterface::iconImage()
    {
        if ( !_icon )
        {
            _icon = new QImage( _path );
        }
        return *_icon;
    }

    Defs::EColors FigureInterface::color()
    {
        return _color;
    }

    Defs::EFigures FigureInterface::type()
    {
        return _figure;
    }

    Defs::ESpecials FigureInterface::isSpecial(const Defs::MovePrimitive&)
    {
        return Defs::None;
    }

    QString FigureInterface::name()
    {
        return QString("Invalid");
    }

    QString FigureInterface::notation()
    {
        return QString("Invalid");
    }

    QSize FigureInterface::IconSize()
    {
        return QSize(TEXTURE_W, TEXTURE_H);
    }

    bool FigureInterface::IsPositionOccupied(int j, int i)
    {
        return Defs::testBit( i, j, _board->WhiteBlackState()._board );
    }

    bool FigureInterface::IsSameColorFigureOnPosition(int i, int j)
    {
        return _color & _board->GetFigureInPosition(i, j);
    }
}
