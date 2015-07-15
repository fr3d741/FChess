/*
*
*   Global functions and defined variables, constants
*
*/
#ifndef DEFINES_H
#define DEFINES_H

#define VERTICAL_SIZE 8
#define HORIZONTAL_SIZE 8
#define NUMBER_OF_PLAYERS 2

#define CELL_TEXTURE_W 44
#define CELL_TEXTURE_H 44

#include <QString>
#include <QPair>
#include <QMap>
#include <utility>
#include <bitset>
#include <memory>

#define RELEASE_VERSION "0.3 Beta"

namespace Defs
{

typedef std::bitset<64> state;

struct ColorState
{
    state _board;
    QMap< int, QPair< int, int > > _figures;
};

void setBit( int i, int j, state& st, bool value = true );
bool testBit( int i, int j, state& st );
void setFigurePosition( int figure, int i, int j );
QPair<int,int> getFigurePosition( int figure, int color );
QPair<int, int> getPosition( int i );
int getPosition( int i, int j );
int getFigureID( int i );

QString convertFigureToString( int );

enum
{
    ACCEPTED,
    INVALID_CONDITION,
    NOT_HANDLED
};

enum EColors
{
    Invalid = -1,
    White = 1,
    Black = 2
};

enum EPlayers
{
    Human
};

enum EFigures
{
    King = 4,
    Queen = 8,
    Bishop = 16,
    Knight = 32,
    Rook = 64,
    Pawn = 128
};

struct Cell
{
    int     figure;
    EColors cellColor;
};

struct MovePrimitive
{
    std::pair<int,int> from;
    std::pair<int,int> to;
};

struct Move : public MovePrimitive
{
    Move();
    ~Move();
    int figure;
    Cell fromCell;
    Cell toCell;
    std::shared_ptr< Move > additionalMove;
};

extern ColorState WhiteBlackState;
//extern ColorState& WhiteState;
//extern ColorState& BlackState;

} //end namespace


#endif // DEFINES_H
