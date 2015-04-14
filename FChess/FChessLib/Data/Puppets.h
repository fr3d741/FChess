#ifndef PUPPETS_H
#define PUPPETS_H

#include <QtGlobal>

enum class EPuppet : qint8
{
	King,
	Queen,
	Bishop,
	Knight,
	Rook,
	Pawn
};

struct Puppet{
		EPuppet type;

};

#endif // PUPPETS_H
