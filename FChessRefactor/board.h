#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QVector>

#include "Defines.h"
#include "messageinterface.h"
#include "Interfaces/player.h"

extern Defs::Cell** Defs::boardState;
extern Defs::ColorState Defs::WhiteBlackState;

/*!
* \brief Main class, handling players, figures, turn order, containg board data
*/
class Board : public QObject, public MessageInterface
{
    Q_OBJECT
public:
    /*!
    * \brief Construktor
    */
    explicit Board(QObject *parent = 0);

    ~Board();

    Defs::Cell** BoardState();
    
    void setNumberOfPlayers( int i );

    int sizeVerical();

    int sizeHorizontal();

    void resetBoard();

    void addPlayer( Player* player );

    void setPlayer( int i, Player* player );

    bool isValidCell( Defs::Cell& cell );

    bool setMove( Defs::Move& move );

    //Player* currentPlayer();

    std::pair<int, int>& selectedCell();

    QString formatMove( Defs::Move& move );

    /*!
    * \returns true if the games has started
    */
    bool started();

    /*!
    * \returns list of moves so far
    */
    QList< Defs::Move >& stack();

    /*!
    * \brief reverts board state based on move, if called with NULL, reverts last move
    */
    void revertStep( Defs::Move* move = 0 );

    /*!
    * \brief deletes player, in case of some error
    */
    void deletePlayer( int index );

    void init();
signals:
    //void signalSendMessage( QString );
    virtual void signalMessage( QString );

    virtual void signalError( QString );

    void signalPlayerChanged();

    /*!
    * \brief signals general changes in the state of board
    */
    void signalBoardChanged();

public slots:
    /*!
    * \brief validates cell position
    * \returns true if needed to update visuals
    */
    bool cellPressed( int x, int y );

    //bool start();

protected:
    /*!
    * \brief Handles Castling, En passant, Promotion etc.
    */
    int handleSpecificCases( Defs::Move& move );

    //void nextPlayer();

protected:
    bool                    _started;

    bool                    _isCheck;

    //! current player, handling availability through gui
    //Player*                 _currentPlayer;

    //! array of players
    QVector<Player*>        _players;

    //!
    std::pair< int, int >   _selectedCell;

    QList< Defs::Move >     _stack;

    QVector< int >             _movedCells;
};

#endif // BOARD_H
