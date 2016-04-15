#ifndef FIGURE_H
#define FIGURE_H

class Board;

#include <QPixmap>
#include <QImage>
#include <QMap>
#include <memory>

#include "../Defines.h"
#include "../Interfaces/IBoard.h"
#include "../Interfaces/singleton.h"

namespace puppets
{

/*!
* \brief abstract class of chess figures
*/
class FigureInterface
{
public:
    /*!
    * \brief
    */
    explicit FigureInterface(std::shared_ptr<IBoard> board, Defs::EColors color, int figure );

    /*!
    * \brief
    */
    virtual ~FigureInterface();

    /*!
    * \brief color of figure
    */
    virtual Defs::EColors color();

    /*!
    * \brief type of figure
    */
    virtual Defs::EFigures type();

    /*!
    * \brief checks whether if from to is a valid move according to the rules, implemented in a subclass
    */
    virtual bool isValidMove(Defs::MovePrimitive) = 0;

    /*!
    * \brief gives back reachable cells in a 8x8 bitfield, also it's represents which cells are under attack
    */
    virtual void reachableCells(Defs::state&, QPair<int,int>&) = 0;

    virtual Defs::ESpecials isSpecial(const Defs::MovePrimitive&);

    virtual QString name();

    virtual QString notation();

public:
    static QSize IconSize();

protected:
    bool IsPositionOccupied(int j, int i);

    bool IsSameColorFigureOnPosition(int i, int j);

private:
    FigureInterface();

protected:
    Defs::EColors    _color;
    Defs::EFigures   _figure;
    std::shared_ptr<IBoard> _board;
};

}

#endif // FIGURE_H


