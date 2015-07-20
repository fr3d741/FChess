#include <algorithm>

#include "board.h"

#include "Interfaces/figure.h"
#include "evaluator.h"
#include "Visual/figureselector.h"
#include "Factories/figurefactory.h"

Board::Board(QObject *parent)
    :QObject(parent)
    ,_boardState(nullptr)
    ,_isCheck(false)
    ,_selectedCell( -1, -1)
    ,_stack()
    ,_movedCells(64)
{
    _boardState = new Defs::Cell*[sizeVerical()];
    for ( int i = 0; i < sizeVerical(); ++i )
        _boardState[i] = new Defs::Cell[sizeHorizontal()];

    _movedCells.fill( 0 );
    resetBoard();
    //init();
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

//    Defs::WhiteState._board.reset();
//    Defs::BlackState._board.reset();
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

Defs::ColorState &Board::WhiteBlackState()
{
    return _WhiteBlackState;
}

Defs::Cell Board::operator()(std::pair<int, int> &indexPair)
{
    size_t j = indexPair.first;
    size_t i = indexPair.second;

    if (sizeHorizontal() <= j && sizeVerical() <= i )
        return Defs::Cell();

    Defs::Cell& c = _boardState[j][i];
    return c;
}

Defs::Cell *Board::operator[](int index)
{
    size_t i = index;
    if (sizeVerical() <= i)
        return nullptr;

return _boardState[i];
}

int Board::handleSpecificCases( Defs::Move& move )
{
    Defs::Cell& c1 = _boardState[move.from.first][move.from.second];
    Defs::Cell& c2 = _boardState[move.to.first][move.to.second];
	int diff = move.to.second - move.from.second;

    if ( c1.figure & Defs::King && abs( diff ) == 2 )
    {
        //Check Castling
        QList< QPair<int,int> > pointList;
        //int diff = move.to.first - move.from.first;
        
        diff = diff / abs( diff );

        int rookX, rookY;
        for ( int i = move.from.second + diff; i != move.to.second + diff; i += diff )
        {
            QPair<int,int> pos(move.to.first, i );
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

        if ( _movedCells[ Defs::getPosition( move.from.first, move.from.second )] )
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
        {
            Defs::Move* addMove = new Defs::Move;
            addMove->from.first = rookX;
            addMove->from.second = rookY;
            addMove->to.first = move.to.first;
            addMove->to.second = move.from.second + diff;
            addMove->fromCell = _boardState[addMove->from.first][addMove->from.second];
            addMove->toCell = _boardState[addMove->to.first][addMove->to.second];
            //addMove->additionalMove = 0;
            addMove->figure = addMove->fromCell.figure;
            move.additionalMove = std::shared_ptr< Defs::Move >( addMove );
            c2.figure = c1.figure;
            c1.figure = 0;

            Defs::Cell& c3 = _boardState[addMove->from.first][addMove->from.second];
            Defs::Cell& c4 = _boardState[addMove->to.first][addMove->to.second];
            c4.figure = c3.figure;
            c3.figure = 0;

            Defs::setBit( move.from.first, move.from.second, _WhiteBlackState._board, false );
            Defs::setBit( addMove->from.first, addMove->from.second, _WhiteBlackState._board, false );

            Defs::setBit( move.to.first, move.to.second, _WhiteBlackState._board, true );
            Defs::setBit( addMove->to.first, addMove->to.second, _WhiteBlackState._board, true );

            Defs::setFigurePosition( move.figure, move.to.first, move.to.second, _WhiteBlackState );
            Defs::setFigurePosition( addMove->figure, addMove->to.first, addMove->to.second, _WhiteBlackState );

            _movedCells[ Defs::getPosition( move.from.first, move.from.second )]++;
            _movedCells[ Defs::getPosition( addMove->from.first, addMove->from.second )]++;
        }
        return Defs::ACCEPTED;
    }
    else if ( c1.figure & Defs::Pawn )
    {
        //Check Promotion
        if ( ( ( c1.figure & Defs::White ) && move.to.first == 7 ) || ( ( c1.figure & Defs::Black ) && move.to.first == 0 ) )
        {
            int f = 0;
            if ( ( c1.figure & Defs::White ) && move.to.first == 7 )
            {
                FigureSelector fs;
                f = fs.getFigure( Defs::White );
                if ( f < 2 )
                {
                    return Defs::INVALID_CONDITION;
                }
            }
            else if ( ( c1.figure & Defs::Black ) && move.to.first == 0 )
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
            Defs::setBit( move.from.first, move.from.second, _WhiteBlackState._board, false );

            Defs::setBit( move.to.first, move.to.second, _WhiteBlackState._board, true );

            Defs::setFigurePosition( move.figure, move.to.first, move.to.second, _WhiteBlackState );

            _movedCells[ Defs::getPosition( move.from.first, move.from.second )]++;
            return Defs::ACCEPTED;

        }

        //Check En passant
        {
        }
    }
return Defs::NOT_HANDLED;
}

//bool Board::setMove( Defs::Move& move )
//{
//    Defs::Cell& c1 = _boardState[move.from.first][move.from.second];
//    Defs::Cell& c2 = _boardState[move.to.first][move.to.second];
//    move.fromCell = c1;
//    move.toCell = c2;

//    if ( ( c1.figure & 0x0003 ) == ( c2.figure & 0x0003 ) )
//    {
//        return false;
//    }

//    if ( !puppets::FigureFactory::createFigure(value(c1.figure)->isValidMove(move) )
//    {
//        emit signalMessage( QString( "Invalid move from [%1,%2] to [%3,%4] with %5" ).arg( move.from.first ).arg( move.from.second ).arg(move.to.first).arg( move.to.second).arg( Defs::convertFigureToString(c1.figure) ) );
//        return false;
//    }

//    int result = handleSpecificCases( move );
//    if ( result == Defs::INVALID_CONDITION )
//    {
//        emit signalMessage( QString( "Invalid move from [%1,%2] to [%3,%4] with %5" ).arg( move.from.first ).arg( move.from.second ).arg(move.to.first).arg( move.to.second).arg( Defs::convertFigureToString(c1.figure) ) );
//        return false;
//    }

//    if ( result == Defs::NOT_HANDLED )
//    {
//        if ( move.figure & Defs::White )
//        {
//            Defs::setBit( move.from.first, move.from.second, _WhiteBlackState._board, false );
//            Defs::setBit( move.to.first, move.to.second, _WhiteBlackState._board );
//            Defs::setFigurePosition( move.figure, move.to.first, move.to.second, _WhiteBlackState );
//        }
//        else if ( move.figure & Defs::Black )
//        {
//            Defs::setBit( move.from.first, move.from.second, _WhiteBlackState._board, false );
//            Defs::setBit( move.to.first, move.to.second, _WhiteBlackState._board );
//            Defs::setFigurePosition( move.figure, move.to.first, move.to.second, _WhiteBlackState );
//        }

//        emit signalMessage( QString( "%5 moved from [%1,%2] to [%3,%4]" ).arg( move.from.first ).arg( move.from.second ).arg(move.to.first).arg( move.to.second).arg( Defs::convertFigureToString(c1.figure) ) );

//        c2.figure = c1.figure;
//        c1.figure = 0;

//        _movedCells[ Defs::getPosition( move.from.first, move.from.second )]++;
//    }

//    _stack.push_back( move );
////    Player* prevPlayer = _currentPlayer;
////    nextPlayer();
////    bool isStillCheck = false;
////    isStillCheck = Evaluator::check( prevPlayer->color() );
////    if ( _isCheck && isStillCheck )
////    {
////        revertStep();
////        emit signalMessage( QString( "You are in Check!" ) );
////        return false;
////    }
////    else if ( isStillCheck )
////    {
////        revertStep();
////        emit signalMessage( QString( "Cant move into a Check position!" ) );
////        return false;
////    }
////    else
////    {
////        _isCheck = Evaluator::check( _currentPlayer->color() );
////        if ( _isCheck )
////        {
////            emit signalMessage( QString( "Check!" ) );
////        }
////    }

////    emit signalBoardChanged();

//    return true;
//}

bool Board::applyMove(Defs::MovePrimitive move)
{
    Defs::Cell& c1 = _boardState[move.from.first][move.from.second];
    Defs::Cell& c2 = _boardState[move.to.first][move.to.second];

//    if ( result == Defs::NOT_HANDLED )
//    {
//        if ( move.figure & Defs::White )
//        {
//            Defs::setBit( move.from.first, move.from.second, Defs::WhiteBlackState._board, false );
//            Defs::setBit( move.to.first, move.to.second, Defs::WhiteBlackState._board );
//            Defs::setFigurePosition( move.figure, move.to.first, move.to.second );
//        }
//        else if ( move.figure & Defs::Black )
//        {
//            Defs::setBit( move.from.first, move.from.second, Defs::WhiteBlackState._board, false );
//            Defs::setBit( move.to.first, move.to.second, Defs::WhiteBlackState._board );
//            Defs::setFigurePosition( move.figure, move.to.first, move.to.second );
//        }

//        emit signalMessage( QString( "%5 moved from [%1,%2] to [%3,%4]" ).arg( move.from.first ).arg( move.from.second ).arg(move.to.first).arg( move.to.second).arg( Defs::convertFigureToString(c1.figure) ) );

//        c2.figure = c1.figure;
//        c1.figure = 0;

//        _movedCells[ Defs::getPosition( move.from.first, move.from.second )]++;
//    }

    Defs::Move m;
    m.from = move.from;
    m.to = move.to;
    m.fromCell = c1;
    m.toCell = c2;
    m.figure = c1.figure;
    _stack.push_back( m );

    c2.figure = c1.figure;
    c1.figure = 0;
    return true;
}

std::shared_ptr<Board> Board::replicate(Defs::MovePrimitive move)
{
    std::shared_ptr<Board> replica(new Board);
    Defs::Cell** board = replica->BoardState();

    for ( int i = 0; i < sizeVerical(); ++i )
    {
        for ( int j = 0; j < sizeHorizontal(); ++j )
            board[i][j] = _boardState[i][j];
    }

    replica->applyMove(move);

    return replica;
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

    _boardState[m.from.first][m.from.second]   = m.fromCell;
    _boardState[m.to.first][m.to.second]       = m.toCell;
    Defs::setBit( m.from.first, m.from.second, _WhiteBlackState._board, true );
    Defs::setBit( m.to.first, m.to.second, _WhiteBlackState._board, false );
    Defs::setFigurePosition( m.figure, m.from.first, m.from.second, _WhiteBlackState );
    _movedCells[ Defs::getPosition( m.from.first, m.from.second ) ]--;
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
    for ( int i = 0; i < sizeHorizontal(); ++i )
    {
        for ( int j = 0; j < sizeVerical(); ++j )
        {
            _boardState[i][j].cellColor = (color?Defs::Black:Defs::White);
            color = !color;
            _boardState[i][j].figure = 0;
        }
        color = !color;
    }
    _stack.clear();
    _selectedCell.first = -1;
    _selectedCell.second = -1;
    _movedCells.fill(0);

    emit signalBoardChanged();
}

std::pair<int, int>& Board::selectedCell()
{
    return _selectedCell;
}

std::pair<int, int> Board::getFigurePosition(int value)
{
    for( int j = 0; j < sizeVerical(); ++j )
        for( int i = 0; i < sizeHorizontal(); ++i )
            if (_boardState[j][i].figure==value)
            {
                return std::make_pair(i, j);
            }

    return std::make_pair(-1, -1);
}

Defs::Cell Board::at(std::pair<int, int> &indexPair)
{
    return (*this)(indexPair);
}

QList<std::pair<int, int> > Board::filterCells(FncPtr filterFunction)
{
    QList<std::pair<int, int> > result;

    for( int j = 0; j < sizeVerical(); ++j )
        for( int i = 0; i < sizeHorizontal(); ++i )
            if ((*filterFunction)(_boardState[j][i]))
            {
                result.push_back( std::make_pair(i, j) );
            }

    return result;

}

QList< Defs::Move >& Board::stack()
{
    return _stack;
}
