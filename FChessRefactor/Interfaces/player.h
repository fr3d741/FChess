#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "../messageinterface.h"
#include "../Defines.h"

/*!
* \brief Abstract class of players( PC, Human, etc. )
*/
class Player : public QObject, public MessageInterface
{
    Q_OBJECT
public:
    explicit Player( Defs::EColors color = Defs::Invalid, QObject *parent = 0);

    virtual ~Player();

    virtual Defs::EColors color();

    virtual bool isValidCell( Defs::Cell& cell ) = 0;

    virtual bool isValidCellForTarget( Defs::Cell* cell ) = 0;

    virtual std::pair< int, int >& cellOverCursor() = 0;

signals:
    /*!
    * \brief sends general message
    */
    void signalMessage( QString );

    /*!
    * \brief sends error message
    */
    void signalError( QString );

    /*!
    * \brief target cell has been selected
    */
    void signalCellPressed( int, int );

    /*!
    * \brief source cell has been selected
    */
    void signalCellChanged( int, int );

    /*!
    * \brief signals eventFilter has been successfully processed
    */
    void signalEventFiltered();
public slots:

protected:
    Defs::EColors _playerColor;
};

#endif // PLAYER_H
