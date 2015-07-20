#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QVector>

#include "Defines.h"
#include "messageinterface.h"
#include "Interfaces/player.h"

//extern Defs::Cell** Defs::boardState;
//extern Defs::ColorState Defs::WhiteBlackState;

typedef bool (*FncPtr)(Defs::Cell& c);

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
    
    int sizeVerical();

    int sizeHorizontal();

    void resetBoard();

    //bool setMove( Defs::Move& move );

    bool applyMove(Defs::MovePrimitive move);

    std::shared_ptr<Board> replicate(Defs::MovePrimitive move);

    std::pair<int, int>& selectedCell();

    std::pair<int, int> getFigurePosition(int value);

    Defs::Cell at(std::pair<int, int>& indexPair);

    QList< std::pair<int, int> > filterCells(FncPtr filterFunction);

    /*!
    * \returns list of moves so far
    */
    QList< Defs::Move >& stack();

    /*!
    * \brief reverts board state based on move, if called with NULL, reverts last move
    */
    void revertStep( Defs::Move* move = 0 );

    void init();

    Defs::ColorState&        WhiteBlackState();

    ///*** operators ***
    Defs::Cell operator()(std::pair<int, int>& indexPair);

    Defs::Cell* operator[](int index);

    //TODO: move to a more convenient location
    //static Defs::Cell** boardState;
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

protected:
    /*!
    * \brief Handles Castling, En passant, Promotion etc.
    */
    int handleSpecificCases( Defs::Move& move );

protected:
    Defs::Cell**            _boardState;

    Defs::ColorState        _WhiteBlackState;

    bool                    _isCheck;

    //!
    std::pair< int, int >   _selectedCell;

    QList< Defs::Move >     _stack;

    QVector< int >             _movedCells;
};

#endif // BOARD_H
