#include <algorithm>
#include <QDebug>

#include "board.h"

#include "Interfaces/figure.h"
#include "evaluator.h"
#include "Visual/figureselector.h"
#include "Factories/figurefactory.h"

Board::Board(QObject *parent)
    :QObject(parent)
    ,_boardState(nullptr)
    ,_isCheck(false)
    ,_stack()
    ,_movedCells(64)
{
    _boardState = new Defs::Cell*[sizeVerical()];
    for ( int i = 0; i < sizeVerical(); ++i )
        _boardState[i] = new Defs::Cell[sizeHorizontal()];

    _movedCells.fill( 0 );
    resetBoard();
}

Board::~Board()
{
    for ( int i = 0; i < sizeVerical(); ++i )
       delete[] _boardState[i];
    delete[] _boardState;
}

Defs::Cell **Board::BoardState()
{
    return _boardState;
}

void Board::init()
{
    //Right now assume a 8 x 8 table

    // 0,0 is lower left corner
    _boardState[0][0].figure = Defs::White | Defs::Rook;
    _boardState[0][1].figure = Defs::White | Defs::Knight;
    _boardState[0][2].figure = Defs::White | Defs::Bishop;
    _boardState[0][3].figure = Defs::White | Defs::Queen;
    _boardState[0][4].figure = Defs::White | Defs::King;
    _boardState[0][5].figure = Defs::White | Defs::Bishop;
    _boardState[0][6].figure = Defs::White | Defs::Knight;
    _boardState[0][7].figure = Defs::White | Defs::Rook;

    _boardState[1][0].figure = Defs::White | Defs::Pawn;
    _boardState[1][1].figure = Defs::White | Defs::Pawn;
    _boardState[1][2].figure = Defs::White | Defs::Pawn;
    _boardState[1][3].figure = Defs::White | Defs::Pawn;
    _boardState[1][4].figure = Defs::White | Defs::Pawn;
    _boardState[1][5].figure = Defs::White | Defs::Pawn;
    _boardState[1][6].figure = Defs::White | Defs::Pawn;
    _boardState[1][7].figure = Defs::White | Defs::Pawn;

    _boardState[7][0].figure = Defs::Black | Defs::Rook;
    _boardState[7][1].figure = Defs::Black | Defs::Knight;
    _boardState[7][2].figure = Defs::Black | Defs::Bishop;
    _boardState[7][3].figure = Defs::Black | Defs::Queen;
    _boardState[7][4].figure = Defs::Black | Defs::King;
    _boardState[7][5].figure = Defs::Black | Defs::Bishop;
    _boardState[7][6].figure = Defs::Black | Defs::Knight;
    _boardState[7][7].figure = Defs::Black | Defs::Rook;

    _boardState[6][0].figure = Defs::Black | Defs::Pawn;
    _boardState[6][1].figure = Defs::Black | Defs::Pawn;
    _boardState[6][2].figure = Defs::Black | Defs::Pawn;
    _boardState[6][3].figure = Defs::Black | Defs::Pawn;
    _boardState[6][4].figure = Defs::Black | Defs::Pawn;
    _boardState[6][5].figure = Defs::Black | Defs::Pawn;
    _boardState[6][6].figure = Defs::Black | Defs::Pawn;
    _boardState[6][7].figure = Defs::Black | Defs::Pawn;

    for ( int i = 2; i < 6; ++i )
        for ( int j = 0; j < 8; ++j )
            _boardState[i][j].figure = 0;
}

Defs::Cell Board::operator()(Defs::Position &indexPair)
{
    size_t x = indexPair.x;
    size_t y = indexPair.y;
    if ((size_t)sizeHorizontal() <= x || (size_t)sizeVerical() <= y )
        return Defs::Cell();

    return _boardState[indexPair.x][indexPair.y];
}

Defs::Cell *Board::operator[](int index)
{
    size_t x = index;
    if (sizeVerical() <= x)
        return nullptr;

    return _boardState[x];
}

void Board::dumpState()
{
    for ( int x = 0; x < sizeHorizontal(); ++x )
    {
        for ( int y = 0; y < sizeVerical(); ++y )
        {
            qDebug() << "[" << x << "," << y << "]:" << _boardState[x][y].figure;
        }
    }
}

void Board::CreateMove(Defs::Move &m, Defs::MovePrimitive &move)
{
    Defs::Cell& c1 = cell(move.from);
    Defs::Cell& c2 = cell(move.to);

    m.from = move.from;
    m.to = move.to;
    m.fromCell = c1;
    m.toCell = c2;
    m.figure = c1.figure;
}

bool Board::applyMove(Defs::MovePrimitive& move)
{
    if (!move.isValid())
        return false;

    Defs::Cell& c1 = cell(move.from);
    Defs::Cell& c2 = cell(move.to);

    Defs::Move m;
    switch(move.special)
    {
        case Defs::Promotion:
            m = reinterpret_cast<Defs::Move&>(move);
            c2.figure = m.figure;
            c1.figure = 0;
            break;
        case Defs::EnPassant:
            {
                Defs::Position p{move.from.x, move.to.y};
                cell(p).figure = 0;
                m.special = Defs::EnPassant;

                CreateMove(m, move);

                c2.figure = c1.figure;
                c1.figure = 0;
            }
            break;
        case Defs::Castling:
        case Defs::None:
        default:
            CreateMove(m, move);

            c2.figure = c1.figure;
            c1.figure = 0;
            break;
    }

    _stack.push_back( m );

    return true;
}

std::shared_ptr<IBoard> Board::replicate(Defs::Move move)
{
    Board* replica = new Board;
    Defs::Cell** board = replica->BoardState();

    for ( int i = 0; i < sizeVerical(); ++i )
    {
        for ( int j = 0; j < sizeHorizontal(); ++j )
            board[i][j] = _boardState[i][j];
    }

    replica->applyMove(move);

    return std::shared_ptr<IBoard>(replica);
}

int Board::GetFigureInPosition(int x, int y)
{
    return _boardState[x][y].figure;
}

bool Board::TestPosition(int x, int y)
{
    return _boardState[x][y].figure != 0;
}

void Board::revertStep( Defs::Move* move )
{
    Defs::Move m;
    if ( !move )
    {
        m = _stack.takeLast();
    }
    else
    {
        m = *move;
    }

    _boardState[m.from.y][m.from.x]   = m.fromCell;
    _boardState[m.to.y][m.to.x]       = m.toCell;
    _movedCells[ Defs::getPosition( m.from.y, m.from.x ) ]--;
    if ( m.additionalMove )
    {
        revertStep( m.additionalMove.get() );
    }

    if ( !move )
    {
        //nextPlayer();
    }

    emit signalBoardChanged();
}

int Board::sizeVerical()
{
    return VERTICAL_SIZE;
}

int Board::sizeHorizontal()
{
    return HORIZONTAL_SIZE;
}

void Board::resetBoard()
{
    bool color = true;
    for ( int x = 0; x < sizeHorizontal(); ++x )
    {
        for ( int y = 0; y < sizeVerical(); ++y )
        {
            _boardState[x][y].cellColor = (color?Defs::Black:Defs::White);
            color = !color;
            _boardState[x][y].figure = 0;
        }
        color = !color;
    }
    _stack.clear();
    _movedCells.fill(0);

    emit signalBoardChanged();
}

Defs::Position Board::getFigurePosition(int value)
{
    for( int y = 0; y < sizeVerical(); ++y )
        for( int x = 0; x < sizeHorizontal(); ++x )
            if (_boardState[x][y].figure==value)
            {
                return {x, y};
            }

    return {-1, -1};
}

Defs::Cell &Board::cell(const Defs::Position &indexPair)
{
    return _boardState[indexPair.x][indexPair.y];
}

QList<Defs::Move> Board::GetHistory()
{
    return _stack;
}

Defs::Move Board::lastMove()
{
    return _stack.back();
}

QList< Defs::Move >& Board::stack()
{
    return _stack;
}
