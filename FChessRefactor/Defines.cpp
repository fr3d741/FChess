#include <stdexcept>
#include <iostream>
#include <stdlib.h>

#include <QApplication>

#include "Defines.h"
#include "exceptions.h"

namespace Defs
{

EColors alternateColor(EColors color)
{
  return color == White ? Black : White;
}

EColors getColor(Ftype figure) {
  auto f = static_cast<int8_t>(figure);
  if (f < 0) return Defs::Black;
  if (f > 0) return Defs::White;

  return Defs::Invalid;
}

EFigures getFigure(Ftype figure) {
  return static_cast<EFigures>(figure & 0x7F);
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

void setBit( int i, int j, state& st, bool value )
{
    try{
        st.set( i * HORIZONTAL_SIZE + j, value );
    }
    catch ( std::out_of_range& ex )
    {
        std::cout << __FILE__ << ":" << __LINE__ << " Position:" << i * HORIZONTAL_SIZE + j << " Out of Range error: " << ex.what() << " " << i << ";" << j <<std::endl;
        QApplication::instance()->quit();
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
        std::cout << __FILE__ << ":" << __LINE__ << " Position:" << i * HORIZONTAL_SIZE + j << " Out of Range error: " << ex.what() << " " << i << ";" << j <<std::endl;
        QApplication::instance()->quit();
    }
}

QPair<int,int> getFigurePosition( int figure, int, ColorState& state )
{
    return state._figures[figure];
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

Move &Move::operator=(const MovePrimitive &rightSide)
{
    this->from = rightSide.from;
    this->to = rightSide.to;
    this->special = rightSide.special;
    return *this;
}

EColors nextColor(EColors color)
{
    if (color == White) return Black;
    if (color == Black) return White;

    throw InvalidArgumentException(QString("%1:%2:Invalid color %3").arg(__FILE__).arg(__LINE__).arg(color).toStdString().c_str());
}

QString toString(const Cell &cell)
{
    return QString("%1").arg(cell.figure);
}

QString toString(const Position &pos)
{
    return QString("[%1,%2]").arg(pos.x).arg(pos.y);
}

bool isPositionValid(int x, int y)
{
    return 0 <= x && x < HORIZONTAL_SIZE && 0 <= y && y < VERTICAL_SIZE;
}

bool isPositionValid(Position p)
{
    return isPositionValid(p.x, p.y);
}

EColors colorOfFigure(int figure)
{
    return (Defs::EColors)(figure & 0x3);
}

} // end namespace
