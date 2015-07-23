#include "Defines.h"
//#include <exception>
#include <stdexcept>
#include <iostream>
#include <stdlib.h>

namespace Defs
{

//Cell** boardState = 0;
//ColorState WhiteBlackState;
//ColorState& WhiteState = WhiteBlackState;
//ColorState& BlackState = WhiteBlackState;

Move::Move()
    :figure(0)
    ,fromCell()
    ,toCell()
    ,additionalMove()
{
}

Move::~Move()
{
    //delete additionalMove;
}

QPair<int, int> getPosition( int i )
{
    div_t dt = div( i, HORIZONTAL_SIZE );
return QPair<int,int>( dt.quot, dt.rem );
}

int getPosition( int i, int j )
{
    return i * HORIZONTAL_SIZE + j;
}

//int getFigureID( int i )
//{
//    div_t dt = div( i, HORIZONTAL_SIZE );
//    try
//    {
//        return boardState[dt.quot][dt.rem].figure;
//     //   qDebug("Access: %d, %d", dt.quot, dt.rem);
//    }
//    catch (...)
//    {
//        qDebug("Exception: %d, %d", dt.quot, dt.rem);
//    }
//return -1;
//}

void setBit( int i, int j, state& st, bool value )
{
    try{
        st.set( i * HORIZONTAL_SIZE + j, value );
    }
    catch ( std::out_of_range& ex )
    {
        std::cout << "Position:" << i * HORIZONTAL_SIZE + j << " Out of Range error: " << ex.what() << " " << i << ";" << j <<std::endl;
        exit( -1 );
    }
}

bool testBit( int i, int j, state& st )
{
    try
    {
        return st.test( i * HORIZONTAL_SIZE + j );
    }
    catch ( std::out_of_range& ex )
    {
        std::cout << "Position:" << i * HORIZONTAL_SIZE + j << " Out of Range error: " << ex.what() << " " << i << ";" << j <<std::endl;
        exit( -1 );
    }
}

QPair<int,int> getFigurePosition( int figure, int color, ColorState& state )
{
//    if ( color == White )
//    {
//        return WhiteState._figures[figure];
//    }
//    else if ( color == Black )
//    {
        return state._figures[figure];
//    }

return QPair<int,int>( -1, -1 );
}

void setFigurePosition(int figure, int i, int j , ColorState &state)
{
    state._figures[figure] = QPair<int,int>(i,j);
}


QString convertFigureToString( int fig )
{
    QString ret;
    if ( fig & White )
    {
        ret.append( "White" );
    }
    else if ( fig & Black )
    {
        ret.append( "Black" );
    }

    int fig2 = fig & 0xFFFC;

    switch(fig2)
    {
        case King:
            ret.append(" King");
            break;
        case Queen:
            ret.append(" Queen");
            break;
        case Bishop:
            ret.append(" Bishop");
            break;
        case Knight:
            ret.append(" Knight");
            break;
        case Rook:
            ret.append(" Rook");
            break;
        case Pawn:
            ret.append(" Pawn");
            break;
        default:
            qDebug("Invalid figure: %d",fig);
            ret = QString( "Invalid Figure");
            break;
    }

    return ret;
}

bool operator==(const Position &A, const Position &B)
{
    return A.x == B.x && A.y == B.y;
}

Defs::Position operator-(const Position &A, const Position &B)
{
    return {A.x - B.x, A.y - B.y};
}

bool operator==(const Move &A, const Move &B)
{
    return  A.from == B.from &&
            A.to == B.to &&
            A.figure == B.figure &&
            A.fromCell == B.fromCell &&
            A.toCell == B.toCell &&
            A.special == B.special;
}

bool operator==(const Cell &A, const Cell &B)
{
    return A.cellColor == B.cellColor && A.figure == B.figure;
}

} // end namespace
