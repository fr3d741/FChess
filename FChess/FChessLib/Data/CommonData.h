#ifndef COMMONDATA_H
#define COMMONDATA_H

#include <memory>
#include <QtGlobal>

enum class EColor
{
	White = 0x1,
	Black = 0x0
};

enum class EPuppet : quint8
{
	King,
	Queen,
	Bishop,
	Knight,
	Rook,
	Pawn
};

struct Cell
{
		EColor color;
		std::shared_ptr<Puppet> puppet;
};

struct Puppet
{
		EPuppet type;

		union {
				quint8 position_x:3;
				quint8 position_y:3;
				quint8 color:1;
				quint8 reserved:1;
				quint8 description;
		};
};

struct Step
{

};


#endif // COMMONDATA_H
