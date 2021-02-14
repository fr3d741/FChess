#ifndef BOARD_H
#define BOARD_H

class Player;

#include <functional>
#include <QObject>
#include <QVector>


#include "Defines.h"
#include "messageinterface.h"
#include "Interfaces/IBoard.h"
#include "Interfaces/iserializable.h"

/*!
* \brief Main class, handling players, figures, turn order, containg board data
*/
class Board : public QObject, public IBoard, public MessageInterface, public ISerializable
{
    Q_OBJECT

public:

    explicit Board(QObject *parent = 0);

    ~Board();

    Defs::Cell** BoardState();
    
    int sizeVerical() override;

    int sizeHorizontal() override;

    void resetBoard();

    bool applyMove(Defs::MovePrimitive &move);

    std::shared_ptr<IBoard> replicate(Defs::Move move) override;

    virtual Ftype GetFigureInPosition(int x, int y) override;

    virtual bool TestPosition(int x, int y) override;

    Defs::Position getFigurePosition(int value) override;

    Defs::Cell& cell(const Defs::Position &indexPair) override;

    QList<Defs::Move> GetHistory() override;

    Defs::Move lastMove() override;

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

    QString SaveState() override;

    void LoadState(const QString state) override;

signals:
    void signalMessage( QString ) override;

    void signalError( QString ) override;

    void signalPlayerChanged(std::shared_ptr<Player>);

    /*!
    * \brief signals general changes in the state of board
    */
    void signalBoardChanged();

public slots:

protected:

private:
    void CreateMove(Defs::Move& m, Defs::MovePrimitive& move);

protected:
    Defs::Cell**            _boardState;

    bool                    _isCheck;

    QList< Defs::Move >     _stack;

    QVector< int >          _movedCells;
};

#endif // BOARD_H
