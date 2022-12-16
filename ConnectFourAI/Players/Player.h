#pragma once

class Board;

class Player
{
public:
	enum class COLOR{RED, YELLOW, EMPTY};

	virtual int doMove(const Board& board) = 0;
	COLOR getColor() const { return m_color; };
	void setColor(const Player::COLOR color) { m_color = color; };

private:
	COLOR m_color;
};