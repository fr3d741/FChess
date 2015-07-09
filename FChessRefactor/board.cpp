#include <algorithm>

#include "board.h"

#include "figure.h"
#include "evaluator.h"
#include "Visual/figureselector.h"

Board::Board(QObject *parent)
    :QObject(parent)
    ,_started(false)
    ,_isCheck(false)
    ,_currentPlayer(0)
    ,_players()
    ,_selectedCell( -1, -1)
    ,_stack()
    ,_movedCells(64)
{
    Defs::boardState = new Defs::Cell*[VERTICAL_SIZE];
    for ( int i = 0; i < VERTICAL_SIZE; ++i )
        Defs::boardState[i] = new Defs::Cell[HORIZONTAL_SIZE];

    _movedCells.fill( 0 );
    resetBoard();
    //init();
}

Board::~Board()
{
    for ( int i = 0; i < VERTICAL_SIZE; ++i )
       delete[] Defs::boardState[i];
    delete[] Defs::boardState;
}

void Board::deletePlayer( int index )
{
    if ( 0 <= index && index < _players.size() )
    {
        delete _players[index];
        _players[index] = 0;
    }
}

void Board::init()
{
    //Right now assume a 8 x 8 table

    // 0,0 is lower left corner
    Defs::boardState[0][0].figure = Defs::White | Defs::Rook;
    Defs::boardState[0][1].figure = Defs::White | Defs::Knight;
    Defs::boardState[0][2].figure = Defs::White | Defs::Bishop;
    Defs::boardState[0][3].figure = Defs::White | Defs::Queen;
    Defs::boardState[0][4].figure = Defs::White | Defs::King;
    Defs::boardState[0][5].figure = Defs::White | Defs::Bishop;
    Defs::boardState[0][6].figure = Defs::White | Defs::Knight;
    Defs::boardState[0][7].figure = Defs::White | Defs::Rook;

    Defs::boardState[1][0].figure = Defs::White | Defs::Pawn;
    Defs::boardState[1][1].figure = Defs::White | Defs::Pawn;
    Defs::boardState[1][2].figure = Defs::White | Defs::Pawn;
    Defs::boardState[1][3].figure = Defs::White | Defs::Pawn;
    Defs::boardState[1][4].figure = Defs::White | Defs::Pawn;
    Defs::boardState[1][5].figure = Defs::White | Defs::Pawn;
    Defs::boardState[1][6].figure = Defs::White | Defs::Pawn;
    Defs::boardState[1][7].figure = Defs::White | Defs::Pawn;

    Defs::boardState[7][0].figure = Defs::Black | Defs::Rook;
    Defs::boardState[7][1].figure = Defs::Black | Defs::Knight;
    Defs::boardState[7][2].figure = Defs::Black | Defs::Bishop;
    Defs::boardState[7][3].figure = Defs::Black | Defs::Queen;
    Defs::boardState[7][4].figure = Defs::Black | Defs::King;
    Defs::boardState[7][5].figure = Defs::Black | Defs::Bishop;
    Defs::boardState[7][6].figure = Defs::Black | Defs::Knight;
    Defs::boardState[7][7].figure = Defs::Black | Defs::Rook;

    Defs::boardState[6][0].figure = Defs::Black | Defs::Pawn;
    Defs::boardState[6][1].figure = Defs::Black | Defs::Pawn;
    Defs::boardState[6][2].figure = Defs::Black | Defs::Pawn;
    Defs::boardState[6][3].figure = Defs::Black | Defs::Pawn;
    Defs::boardState[6][4].figure = Defs::Black | Defs::Pawn;
    Defs::boardState[6][5].figure = Defs::Black | Defs::Pawn;
    Defs::boardState[6][6].figure = Defs::Black | Defs::Pawn;
    Defs::boardState[6][7].figure = Defs::Black | Defs::Pawn;

    for ( int i = 2; i < 6; ++i )
        for ( int j = 0; j < 8; ++j )
            Defs::boardState[i][j].figure = 0;

//    Defs::WhiteState._board.reset();
//    Defs::BlackState._board.reset();
    Defs::WhiteBlackState._board.reset();

    for ( int i = 0; i < 2; ++i )
    {
        for ( int j = 0; j < 8; ++j )
        {
            Defs::setBit( i, j, Defs::WhiteBlackState._board );
            Defs::setBit( (i + 6), j, Defs::WhiteBlackState._board );
        }
    }
}

int Board::handleSpecificCases( Defs::Move& move )
{
    Defs::Cell& c1 = Defs::boardState[move.from.first][move.from.second];
    Defs::Cell& c2 = Defs::boardState[move.to.first][move.to.second];
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
            if ( Defs::testBit( pos.first, pos.second, Defs::WhiteBlackState._board ) )
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
            addMove->fromCell = Defs::boardState[addMove->from.first][addMove->from.second];
            addMove->toCell = Defs::boardState[addMove->to.first][addMove->to.second];
            //addMove->additionalMove = 0;
            addMove->figure = addMove->fromCell.figure;
            move.additionalMove = std::tr1::shared_ptr< Defs::Move >( addMove );
            c2.figure = c1.figure;
            c1.figure = 0;

            Defs::Cell& c3 = Defs::boardState[addMove->from.first][addMove->from.second];
            Defs::Cell& c4 = Defs::boardState[addMove->to.first][addMove->to.second];
            c4.figure = c3.figure;
            c3.figure = 0;

            Defs::setBit( move.from.first, move.from.second, Defs::WhiteBlackState._board, false );
            Defs::setBit( addMove->from.first, addMove->from.second, Defs::WhiteBlackState._board, false );

            Defs::setBit( move.to.first, move.to.second, Defs::WhiteBlackState._board, true );
            Defs::setBit( addMove->to.first, addMove->to.second, Defs::WhiteBlackState._board, true );

            Defs::setFigurePosition( move.figure, move.to.first, move.to.second );
            Defs::setFigurePosition( addMove->figure, addMove->to.first, addMove->to.second );

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
            Defs::setBit( move.from.first, move.from.second, Defs::WhiteBlackState._board, false );

            Defs::setBit( move.to.first, move.to.second, Defs::WhiteBlackState._board, true );

            Defs::setFigurePosition( move.figure, move.to.first, move.to.second );

            _movedCells[ Defs::getPosition( move.from.first, move.from.second )]++;
            return Defs::ACCEPTED;

        }

        //Check En passant
        {
        }
    }
return Defs::NOT_HANDLED;
}

bool Board::setMove( Defs::Move& move )
{
    Defs::Cell& c1 = Defs::boardState[move.from.first][move.from.second];
    Defs::Cell& c2 = Defs::boardState[move.to.first][move.to.second];
    move.fromCell = c1;
    move.toCell = c2;

    if ( ( c1.figure & 0x0003 ) == ( c2.figure & 0x0003 ) )
    {
        return false;
    }

    if ( !puppets::ChessFigures[c1.figure]->isValidMove(move) )
    {
        emit signalMessage( QString( "Invalid move from [%1,%2] to [%3,%4] with %5" ).arg( move.from.first ).arg( move.from.second ).arg(move.to.first).arg( move.to.second).arg( Defs::convertFigureToString(c1.figure) ) );
        return false;
    }

    int result = handleSpecificCases( move );
    if ( result == Defs::INVALID_CONDITION )
    {
        emit signalMessage( QString( "Invalid move from [%1,%2] to [%3,%4] with %5" ).arg( move.from.first ).arg( move.from.second ).arg(move.to.first).arg( move.to.second).arg( Defs::convertFigureToString(c1.figure) ) );
        return false;
    }

    if ( result == Defs::NOT_HANDLED )
    {
        if ( move.figure & Defs::White )
        {
            Defs::setBit( move.from.first, move.from.second, Defs::WhiteBlackState._board, false );
            Defs::setBit( move.to.first, move.to.second, Defs::WhiteBlackState._board );
            Defs::setFigurePosition( move.figure, move.to.first, move.to.second );
        }
        else if ( move.figure & Defs::Black )
        {
            Defs::setBit( move.from.first, move.from.second, Defs::WhiteBlackState._board, false );
            Defs::setBit( move.to.first, move.to.second, Defs::WhiteBlackState._board );
            Defs::setFigurePosition( move.figure, move.to.first, move.to.second );
        }

        emit signalMessage( QString( "%5 moved from [%1,%2] to [%3,%4]" ).arg( move.from.first ).arg( move.from.second ).arg(move.to.first).arg( move.to.second).arg( Defs::convertFigureToString(c1.figure) ) );

        c2.figure = c1.figure;
        c1.figure = 0;

        _movedCells[ Defs::getPosition( move.from.first, move.from.second )]++;
    }

    _stack.push_back( move );
    Player* prevPlayer = _currentPlayer;
    nextPlayer();
    bool isStillCheck = false;
    isStillCheck = Evaluator::check( prevPlayer->color() );
    if ( _isCheck && isStillCheck )
    {
        revertStep();
        emit signalMessage( QString( "You are in Check!" ) );
        return false;
    }
    else if ( isStillCheck )
    {
        revertStep();
        emit signalMessage( QString( "Cant move into a Check position!" ) );
        return false;
    }
    else
    {
        _isCheck = Evaluator::check( _currentPlayer->color() );
        if ( _isCheck )
        {
            emit signalMessage( QString( "Check!" ) );
        }
    }

    emit signalBoardChanged();

return true;
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

    Defs::boardState[m.from.first][m.from.second]   = m.fromCell;
    Defs::boardState[m.to.first][m.to.second]       = m.toCell;
    Defs::setBit( m.from.first, m.from.second, Defs::WhiteBlackState._board, true );
    Defs::setBit( m.to.first, m.to.second, Defs::WhiteBlackState._board, false );
    Defs::setFigurePosition( m.figure, m.from.first, m.from.second );
    _movedCells[ Defs::getPosition( m.from.first, m.from.second ) ]--;
    if ( m.additionalMove )
    {
        revertStep( m.additionalMove.get() );
    }

    if ( !move )
    {
        nextPlayer();
    }

    emit signalBoardChanged();
}

bool Board::isValidCell( Defs::Cell& cell )
{
    if ( !_currentPlayer )
    {
        return false;
    }

return _currentPlayer->isValidCell( cell );
}

bool Board::cellPressed( int x, int y )
{
    if ( _selectedCell.first == x && _selectedCell.second == y )
    {
        //unselect
        _selectedCell.first = -1;
        _selectedCell.second = -1;
        //emit signalMessage( QString("unselected" ) );
        emit signalBoardChanged();
        return true;
    }
    else
    {
        Defs::Cell cell = Defs::boardState[x][y];
        if ( _selectedCell.first == -1 && _selectedCell.second == -1 )
        {
            //select
            if ( isValidCell( cell ) )
            {
                _selectedCell.first = x;
                _selectedCell.second = y;
                emit signalBoardChanged();
                return true;
            }
            else
            {
                emit signalMessage( QString("Invalid cell: %1,%2").arg(x).arg(y) );
            }
        }
        else if ( 0 <= _selectedCell.first && 0 <= _selectedCell.second )
        {
            Defs::Move m;
            //m.additionalMove = 0;
            m.from = _selectedCell;
            m.to = std::pair<int, int>(x , y);
            m.figure = Defs::boardState[_selectedCell.first][_selectedCell.second].figure;
            if ( setMove( m ) )
            {
                _selectedCell.first = -1;
                _selectedCell.second = -1;
                emit signalBoardChanged();
                return true;
            }
            return false;
        }
        else
        {
            emit signalMessage( QString("Invalid selection!Reset position.") );
            _selectedCell.first = -1;
            _selectedCell.second = -1;
            return true;
        }
    }

return false;
}

void Board::addPlayer( Player* player )
{
    _players.push_back( player );
}

void Board::setNumberOfPlayers( int i )
{
    _players.resize(i);
}

void Board::setPlayer( int i, Player* player )
{
    _players[i] = player;
}

int Board::sizeVerical()
{
    return VERTICAL_SIZE;
}

int Board::sizeHorizontal()
{
    return HORIZONTAL_SIZE;
}

bool Board::start()
{
    if ( _players.isEmpty() )
    {
        //no players => exit
        return false;
    }

	_currentPlayer = _players.front();
	if ( !_currentPlayer )
	{
		return false;
	}

    if ( _started )
    {
        resetBoard();
    }
    _started = true;
    init();
    
    emit signalPlayerChanged();
return true;
}

bool Board::started()
{
    return _started;
}

void Board::resetBoard()
{
    bool color = true;
    for ( int i = 0; i < HORIZONTAL_SIZE; ++i )
    {
        for ( int j = 0; j < VERTICAL_SIZE; ++j )
        {
            Defs::boardState[i][j].cellColor = (color?Defs::Black:Defs::White);
            color = !color;
            Defs::boardState[i][j].figure = 0;
        }
        color = !color;
    }
    _stack.clear();
    _selectedCell.first = -1;
    _selectedCell.second = -1;
    _movedCells.fill(0);

    emit signalBoardChanged();
}

Player* Board::currentPlayer()
{
    return _currentPlayer;
}

void Board::nextPlayer()
{
    QVector<Player*>::iterator now = std::find( _players.begin(), _players.end(), (Player*)_currentPlayer );
    if ( now != _players.end() )
    {
        ++now;
        if ( now != _players.end() )
        {
            _currentPlayer = *now;
        }
        else
        {
            _currentPlayer = _players.front();
        }
        emit signalPlayerChanged();
    }
}

std::pair<int, int>& Board::selectedCell()
{
    return _selectedCell;
}

QList< Defs::Move >& Board::stack()
{
    return _stack;
}
