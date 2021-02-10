#define TEXTURE_W 44
#define TEXTURE_H 44

#include <QFileInfo>

#include "figure.h"
#include "../Factories/figurefactory.h"
#include "../board.h"

namespace puppets
{

    FigureInterface::FigureInterface(std::shared_ptr<IBoard> board, Defs::EColors color, int figure )
        :_color( color )
        ,_figure( (Defs::EFigures)figure )
        ,_board(board)
    {
    }

    FigureInterface::~FigureInterface()
    {
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

    bool FigureInterface::IsPositionOccupied(int i, int j)
    {
        return _board->TestPosition(i, j);
    }

    bool FigureInterface::IsSameColorFigureOnPosition(int i, int j)
    {
        return _color & _board->GetFigureInPosition(i, j);
    }
}
