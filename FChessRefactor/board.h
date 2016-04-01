#ifndef BOARD_H
#define BOARD_H

#include <functional>
#include <QObject>
#include <QVector>


#include "Defines.h"
#include "messageinterface.h"
#include "Interfaces/player.h"

typedef bool (*FncPtr)(Defs::Cell& c);

/*!
* \brief Main class, handling players, figures, turn order, containg board data
*/
class Board : public QObject, public MessageInterface
{
    Q_OBJECT
public:

    explicit Board(QObject *parent = 0);

    ~Board();

    Defs::Cell** BoardState();
    
    int sizeVerical();

    int sizeHorizontal();

    void resetBoard();

    bool applyMove(Defs::MovePrimitive &move);

    std::shared_ptr<Board> replicate(Defs::Move move);

    int GetFigureInPosition(int x, int y);

    Defs::Position getFigurePosition(int value);

    Defs::Cell at(Defs::Position &indexPair);

    Defs::Cell& cell(const Defs::Position &indexPair);

    QList<Defs::Position> filterCells(FncPtr filterFunction);

    QList<Defs::Move> filterHistory(std::function<bool(const Defs::Move&)>& filterFunc);

    Defs::Move lastMove();

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

    Defs::Cell operator()(Defs::Position& indexPair);

    Defs::Cell* operator[](int index);

    void dumpState();
signals:
    virtual void signalMessage( QString );

    virtual void signalError( QString );

    void signalPlayerChanged(std::shared_ptr<Player>);

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

    QList< Defs::Move >     _stack;

    QVector< int >             _movedCells;
};

#endif // BOARD_H
