#pragma once

#include <vector>
#include "Players/Player.h"

class Board
{
public:
	const static int ROWS = 6;
	const static int COLUMNS = 7;

	Board();
	bool fourAdjecent(const Player::COLOR& color) const;
	bool isTie() const;
	bool terminalState() const;
	void dropColor(int column, const Player::COLOR& color);
	void undoDrop(int column);
	std::vector<int> getPossibleMoves() const;
	int getRandomMove() const;

	void printBoard() const;

private:
	bool checkRows(const Player::COLOR& color) const;
	bool checkColumns(const Player::COLOR& color) const;
	bool checkDownDiagonals(const Player::COLOR& color) const;
	bool checkUpDiagonals(const Player::COLOR& color) const;

	//std::array<std::array<Player::COLOR, COLUMNS>, ROWS>  m_board;
	Player::COLOR m_board[ROWS][COLUMNS];
};