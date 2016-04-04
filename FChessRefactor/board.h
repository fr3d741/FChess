#ifndef BOARD_H
#define BOARD_H

class Player;

#include <functional>
#include <QObject>
#include <QVector>


#include "Defines.h"
#include "messageinterface.h"
#include "Interfaces/IBoard.h"

/*!
* \brief Main class, handling players, figures, turn order, containg board data
*/
class Board : public QObject, public IBoard, public MessageInterface
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

    std::shared_ptr<IBoard> replicate(Defs::Move move);

    virtual int GetFigureInPosition(int x, int y);

    virtual bool TestPosition(int x, int y);

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

    Defs::ColorState& State();

    Defs::Cell operator()(Defs::Position& indexPair);

    Defs::Cell* operator[](int index);

    void dumpState();
    void ApplyCastling(int rookX, int rookY, Defs::Move& move, Defs::Cell& c1, int diff, Defs::Cell& c2);
signals:
    void signalMessage( QString );

    void signalError( QString );

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
