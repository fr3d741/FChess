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
#define BOARD_SIZE VERTICAL_SIZE * HORIZONTAL_SIZE

#define CELL_TEXTURE_W 44
#define CELL_TEXTURE_H 44

#include <QMetaType>
#include <QString>
#include <QPair>
#include <QMap>
#include <utility>
#include <bitset>
#include <memory>

#define RELEASE_VERSION "0.3"

typedef uint8_t Ftype;

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
void setFigurePosition( int figure, int i, int j, ColorState& state );
QPair<int,int> getFigurePosition(int figure, int, ColorState &state);
QPair<int, int> getPosition( int i );
int getPosition( int i, int j );

QString convertFigureToString( int );

struct Position{
    int x; //second
    int y; //first
};

extern bool             operator==(const Position& A, const Position& B);
extern Defs::Position   operator-(const Position& A, const Position& B);

enum
{
    ACCEPTED,
    INVALID_CONDITION,
    NOT_HANDLED
};

enum ESpecials
{
    Castling,
    Promotion,
    EnPassant,
    None
};

enum EColors
{
    White = 0x00,
    Black = 0x80,
    Invalid = 0xFF
};

enum EPlayers
{
    Human,
    Computer
};

enum EFigures
{
  Pawn = 1,
  Bishop = 2,
  Knight = 4,
  Rook = 8,
  Queen = 16,
  King = 32,
};

struct Cell
{
    Ftype     figure;
    EColors cellColor;
};

extern bool operator==(const Cell& A, const Cell& B);

class MovePrimitive
{
public:
    MovePrimitive():from({-1,-1}),to({-1,-1}), special(None){}
    MovePrimitive(const Position& f, const Position& t):from(f),to(t), special(None){}

    bool isValid(){return from.x != -1 && from.y != -1 && to.x != -1 && to.y != -1;}

    Position from;
    Position to;
    ESpecials special;
};

Q_DECLARE_METATYPE(MovePrimitive)

class Move : public MovePrimitive
{
public:
    Move& operator=(const MovePrimitive& rightSide);
    int figure;
    Cell fromCell;
    Cell toCell;
    std::shared_ptr< Move > additionalMove;
};

extern bool operator==(const Move& A, const Move& B);

EColors alternateColor(EColors color);
EColors getColor(Ftype figure);
EFigures getFigure(Ftype figure);
bool isPositionValid(Defs::Position p);
bool isPositionValid(int x, int y);
EColors nextColor(EColors color);
EColors colorOfFigure(int figure);
QString toString(const Cell& cell);
QString toString(const Position& pos);
}


#endif // DEFINES_H
