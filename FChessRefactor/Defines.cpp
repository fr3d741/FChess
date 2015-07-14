#include "Defines.h"
//#include <exception>
#include <stdexcept>
#include <iostream>
#include <stdlib.h>

namespace Defs
{

Cell** boardState = 0;
ColorState WhiteBlackState;
ColorState& WhiteState = WhiteBlackState;
ColorState& BlackState = WhiteBlackState;

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

int getFigureID( int i )
{
    div_t dt = div( i, HORIZONTAL_SIZE );
    try
    {
        return boardState[dt.quot][dt.rem].figure;
     //   qDebug("Access: %d, %d", dt.quot, dt.rem);
    }
    catch (...)
    {
        qDebug("Exception: %d, %d", dt.quot, dt.rem);
    }
return -1;
}

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

QPair<int,int> getFigurePosition( int figure, int color )
{
    if ( color == White )
    {
        return WhiteState._figures[figure];
    }
    else if ( color == Black )
    {
        return BlackState._figures[figure];
    }

return QPair<int,int>( -1, -1 );
}

void setFigurePosition( int figure, int i, int j )
{
    WhiteBlackState._figures[figure] = QPair<int,int>(i,j);
//    if ( color == White )
//    {
//        WhiteState._figures[figure] = QPair<int,int>(i,j);
//    }
//    else if ( color == Black )
//    {
//        BlackState._figures[figure] = QPair<int,int>(i,j);
//    }
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

} // end namespace
