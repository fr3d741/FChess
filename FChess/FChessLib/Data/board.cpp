#include "board.h"
#include "Factory/puppetfactory.h"

Board::Board()
{
}

const Cell& Board::operator()(int x, int y) const
{
	Q_ASSERT(x<0);Q_ASSERT(7<x);
	Q_ASSERT(y<0);Q_ASSERT(7<y);

	return _board[y][x];
}

void Board::movePuppet(int x, int y, std::shared_ptr<Puppet> piece)
{
	piece->position_x = (quint8)x;
	piece->position_y = (quint8)y;
	_board[y][x].puppet = piece;
}

void Board::initColors()
{
	bool white = true;
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			_board[i][j].color = white?EColor::White:EColor::Black;
			white=!white;
		}
		white=!white;
	}
}

void Board::blackPieces()
{
	movePuppet(0, 0, PuppetFactory(EPuppet::Rook, EColor::Black));
	movePuppet(0, 1, PuppetFactory(EPuppet::Knight, EColor::Black));
	movePuppet(0, 2, PuppetFactory(EPuppet::Bishop, EColor::Black));
	movePuppet(0, 3, PuppetFactory(EPuppet::Queen, EColor::Black));
	movePuppet(0, 4, PuppetFactory(EPuppet::King, EColor::Black));
	movePuppet(0, 5, PuppetFactory(EPuppet::Bishop, EColor::Black));
	movePuppet(0, 6, PuppetFactory(EPuppet::Knight, EColor::Black));
	movePuppet(0, 7, PuppetFactory(EPuppet::Rook, EColor::Black));

	movePuppet(1, 0, PuppetFactory(EPuppet::Pawn, EColor::Black));
	movePuppet(1, 1, PuppetFactory(EPuppet::Pawn, EColor::Black));
	movePuppet(1, 2, PuppetFactory(EPuppet::Pawn, EColor::Black));
	movePuppet(1, 3, PuppetFactory(EPuppet::Pawn, EColor::Black));
	movePuppet(1, 4, PuppetFactory(EPuppet::Pawn, EColor::Black));
	movePuppet(1, 5, PuppetFactory(EPuppet::Pawn, EColor::Black));
	movePuppet(1, 6, PuppetFactory(EPuppet::Pawn, EColor::Black));
	movePuppet(1, 7, PuppetFactory(EPuppet::Pawn, EColor::Black));
}

void Board::whitePieces()
{
	movePuppet(7, 0, PuppetFactory(EPuppet::Rook, EColor::White));
	movePuppet(7, 1, PuppetFactory(EPuppet::Knight, EColor::White));
	movePuppet(7, 2, PuppetFactory(EPuppet::Bishop, EColor::White));
	movePuppet(7, 3, PuppetFactory(EPuppet::Queen, EColor::White));
	movePuppet(7, 4, PuppetFactory(EPuppet::King, EColor::White));
	movePuppet(7, 5, PuppetFactory(EPuppet::Bishop, EColor::White));
	movePuppet(7, 6, PuppetFactory(EPuppet::Knight, EColor::White));
	movePuppet(7, 7, PuppetFactory(EPuppet::Rook, EColor::White));

	movePuppet(6, 0, PuppetFactory(EPuppet::Pawn, EColor::White));
	movePuppet(6, 1, PuppetFactory(EPuppet::Pawn, EColor::White));
	movePuppet(6, 2, PuppetFactory(EPuppet::Pawn, EColor::White));
	movePuppet(6, 3, PuppetFactory(EPuppet::Pawn, EColor::White));
	movePuppet(6, 4, PuppetFactory(EPuppet::Pawn, EColor::White));
	movePuppet(6, 5, PuppetFactory(EPuppet::Pawn, EColor::White));
	movePuppet(6, 6, PuppetFactory(EPuppet::Pawn, EColor::White));
	movePuppet(6, 7, PuppetFactory(EPuppet::Pawn, EColor::White));
}

void Board::initBoard()
{
	//Coloring of the board
	initColors();

	//Initial setup
	blackPieces();
	whitePieces();
}
