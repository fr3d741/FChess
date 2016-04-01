#ifndef FIGURE_H
#define FIGURE_H

class Board;

#include <QPixmap>
#include <QImage>
#include <QMap>
#include <memory>

#include "../Defines.h"
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
    explicit FigureInterface(std::shared_ptr<Board> board, Defs::EColors color, int figure );

    /*!
    * \brief
    */
    virtual ~FigureInterface();

    /*!
    * \brief texture cache
    */
    virtual const QPixmap& iconPixmap();

    /*!
    * \brief texture cache
    */
    virtual const QImage& iconImage();

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
    QImage*         _icon;
    QPixmap*        _iconPix;
    Defs::EColors    _color;
    Defs::EFigures   _figure;
    QString          _path;
    std::shared_ptr<Board> _board;
};

}

namespace puppets
{

/*!
* \brief contains instances of figures
*/
//class PuppetContainer : public QMap< int, puppets::FigureInterface* >, public Singleton<PuppetContainer>
//{
//    friend class Singleton<PuppetContainer>;
//public:
//    typedef QMap< int, puppets::FigureInterface* >::iterator iterator;
//    PuppetContainer();
//};

}

#endif // FIGURE_H


