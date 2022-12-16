#pragma once

#include <array>
#include <memory>

#include "Board.h"
#include "Players/Player.h"

class ConnectFour
{
public:
	ConnectFour(std::unique_ptr<Player> playerOne, std::unique_ptr<Player> playerTwo);
	void start();

private:
	Board m_board;
	std::array<std::unique_ptr<Player>, 2> m_players;
	bool m_redPlaying;

	void switchTurnes();
	void doMove();
	void end() const;
};