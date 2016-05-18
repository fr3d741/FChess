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

    Defs::Cell& cell(const Defs::Position &indexPair);

    QList<Defs::Move> GetHistory();

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

private:
    void CreateMove(Defs::Move& m, Defs::MovePrimitive& move);

protected:
    Defs::Cell**            _boardState;

    bool                    _isCheck;

    QList< Defs::Move >     _stack;

    QVector< int >          _movedCells;
};

#endif // BOARD_H
