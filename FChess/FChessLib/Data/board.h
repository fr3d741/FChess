#ifndef BOARD_H
#define BOARD_H

#include "CommonData.h"

class Board
{
	public:
		Board();

		const Cell& operator()(int i, int j) const;
private:
		void movePuppet(int i, int j, std::shared_ptr<Puppet> piece);

		void blackPieces();
		void whitePieces();
		void initColors();
		void initBoard();

	private:
		Cell _board[8][8];
};

#endif // BOARD_H
