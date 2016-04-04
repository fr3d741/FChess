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

    _WhiteBlackState._board.reset();

    for ( int i = 0; i < 2; ++i )
    {
        for ( int j = 0; j < 8; ++j )
        {
            Defs::setBit( i, j, _WhiteBlackState._board );
            Defs::setBit( (i + 6), j, _WhiteBlackState._board );
        }
    }
}

Defs::ColorState &Board::State()
{
    return _WhiteBlackState;
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

void Board::ApplyCastling(int rookX, int rookY, Defs::Move& move, Defs::Cell& c1, int diff, Defs::Cell& c2)
{
    Defs::Move* addMove = new Defs::Move;
    addMove->from.y = rookX;
    addMove->from.x = rookY;
    addMove->to.y = move.to.y;
    addMove->to.x = move.from.x + diff;
    addMove->fromCell = _boardState[addMove->from.y][addMove->from.x];
    addMove->toCell = _boardState[addMove->to.y][addMove->to.x];
    addMove->figure = addMove->fromCell.figure;
    move.additionalMove = std::shared_ptr< Defs::Move >( addMove );
    c2.figure = c1.figure;
    c1.figure = 0;

    Defs::Cell& c3 = _boardState[addMove->from.y][addMove->from.x];
    Defs::Cell& c4 = _boardState[addMove->to.y][addMove->to.x];
    c4.figure = c3.figure;
    c3.figure = 0;

    Defs::setBit( move.from.y, move.from.x, _WhiteBlackState._board, false );
    Defs::setBit( addMove->from.y, addMove->from.x, _WhiteBlackState._board, false );

    Defs::setBit( move.to.y, move.to.x, _WhiteBlackState._board, true );
    Defs::setBit( addMove->to.y, addMove->to.x, _WhiteBlackState._board, true );

    Defs::setFigurePosition( move.figure, move.to.y, move.to.x, _WhiteBlackState );
    Defs::setFigurePosition( addMove->figure, addMove->to.y, addMove->to.x, _WhiteBlackState );

    _movedCells[ Defs::getPosition( move.from.y, move.from.x )]++;
    _movedCells[ Defs::getPosition( addMove->from.y, addMove->from.x )]++;
}

int Board::handleSpecificCases( Defs::Move& move )
{
    Defs::Cell& c1 = _boardState[move.from.x][move.from.y];
    Defs::Cell& c2 = _boardState[move.to.x][move.to.y];
    int diff = move.to.x - move.from.x;

    if ( c1.figure & Defs::King && abs( diff ) == 2 )
    {
        //Check Castling
        QList< QPair<int,int> > pointList;
        
        diff = diff / abs( diff );

        int rookX, rookY;
        for ( int i = move.from.x + diff; i != move.to.x + diff; i += diff )
        {
            QPair<int,int> pos(move.to.y, i );
            if ( Defs::testBit( pos.first, pos.second, _WhiteBlackState._board ) )
            {
                return Defs::INVALID_CONDITION;
            }
            pointList.push_back( pos );
        }

        if ( Evaluator::checkPositions( Defs::EColors(c1.figure & 0x0003), pointList ) )
        {
            //One of the cells is attacked
            return Defs::INVALID_CONDITION;
        }

        if ( _movedCells[ Defs::getPosition( move.from.y, move.from.x )] )
        {
            //King has moved before
            return Defs::INVALID_CONDITION;
        }

        if ( diff < 0 )
        {
            rookY = 0;
        }
        else
        {
            rookY = 7;
        }

        if ( ( c1.figure & 0x0003 ) == Defs::White )
        {
            rookX = 0;
        }
        else
        {
            rookX = 7;
        }

        if ( _movedCells[Defs::getPosition( rookX, rookY )] )
        {
            //Rook has moved before
            return Defs::INVALID_CONDITION;
        }

        //All ok, apply castling
        ApplyCastling(rookX, rookY, move, c1, diff, c2);
        return Defs::ACCEPTED;
    }
    else if ( c1.figure & Defs::Pawn )
    {
        //Check Promotion
        if ( ( ( c1.figure & Defs::White ) && move.to.y == 7 ) || ( ( c1.figure & Defs::Black ) && move.to.y == 0 ) )
        {
            int f = 0;
            if ( ( c1.figure & Defs::White ) && move.to.y == 7 )
            {
                FigureSelector fs;
                f = fs.getFigure( Defs::White );
                if ( f < 2 )
                {
                    return Defs::INVALID_CONDITION;
                }
            }
            else if ( ( c1.figure & Defs::Black ) && move.to.y == 0 )
            {
                FigureSelector fs;
                f = fs.getFigure( Defs::Black );
                if ( f < 2 )
                {
                    return Defs::INVALID_CONDITION;
                }
            }
            c1.figure = 0;
            c2.figure = f;
            Defs::setBit( move.from.y, move.from.x, _WhiteBlackState._board, false );

            Defs::setBit( move.to.y, move.to.x, _WhiteBlackState._board, true );

            Defs::setFigurePosition( move.figure, move.to.y, move.to.x, _WhiteBlackState );

            _movedCells[ Defs::getPosition( move.from.y, move.from.x )]++;
            return Defs::ACCEPTED;

        }

        //Check En passant
        {
        }
    }
return Defs::NOT_HANDLED;
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
        case Defs::Castling:
        case Defs::None:
        default:
            m.from = move.from;
            m.to = move.to;
            m.fromCell = c1;
            m.toCell = c2;
            m.figure = c1.figure;

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
    replica->State()._board = _WhiteBlackState._board;
    replica->State()._figures = _WhiteBlackState._figures;

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
    Defs::setBit( m.from.y, m.from.x, _WhiteBlackState._board, true );
    Defs::setBit( m.to.y, m.to.x, _WhiteBlackState._board, false );
    Defs::setFigurePosition( m.figure, m.from.y, m.from.x, _WhiteBlackState );
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

QList<Defs::Position> Board::filterCells(FncPtr filterFunction)
{
    QList<Defs::Position> result;

    for( int y = 0; y < sizeVerical(); ++y )
        for( int x = 0; x < sizeHorizontal(); ++x )
            if ((*filterFunction)(_boardState[x][y]))
            {
                result.push_back( {x,y} );
            }

    return result;
}

QList<Defs::Move> Board::filterHistory(std::function<bool(const Defs::Move&)>& filterFunc)
{
    QList<Defs::Move> result;

    for( QList<Defs::Move>::iterator it = _stack.begin(); it != _stack.end(); ++it )
        if (filterFunc(*it))
        {
            result.push_back( *it );
        }

    return result;
}

Defs::Move Board::lastMove()
{
    return _stack.back();
}

QList< Defs::Move >& Board::stack()
{
    return _stack;
}
