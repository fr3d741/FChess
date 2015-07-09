#ifndef FIGURE_H
#define FIGURE_H

#include <QPixmap>
#include <QImage>
#include <QMap>
#include <memory>

#include "Defines.h"

namespace puppets
{

/*!
* \brief abstract class of chess figures
*/
class Figure
{
public:
    /*!
    * \brief
    */
    explicit Figure( QString path, Defs::EColors color, Defs::EFigures figure );

    /*!
    * \brief
    */
    virtual ~Figure();

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
    virtual bool isValidMove( Defs::Move step ) = 0;

    /*!
    * \brief gives back reachable cells in a 8x8 bitfield, also it's represents which cells are under attack
    */
    virtual void reachableCells( Defs::state& result, QPair<int,int>& position ) = 0;

protected:

private:
    Figure();

protected:
    QImage*         _icon;
    QPixmap*        _iconPix;
    Defs::EColors    _color;
    Defs::EFigures   _figure;
    QString          _path;
};

}

namespace puppets
{

/*!
* \brief contains instances of figures
*/
class PuppetContainer : public QMap< int, puppets::Figure* >
{
public:
    typedef QMap< int, puppets::Figure* >::iterator iterator;
    PuppetContainer();
};

static PuppetContainer ChessFigures;

}

#endif // FIGURE_H


