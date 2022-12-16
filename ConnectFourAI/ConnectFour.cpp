#include <iostream>
#include "ConnectFour.h"

ConnectFour::ConnectFour(std::unique_ptr<Player> playerOne, std::unique_ptr<Player> playerTwo) : m_redPlaying{ true }, m_board{},
m_players{ std::move(playerOne), std::move(playerTwo) }
{
	m_players[0]->setColor(Player::COLOR::RED);
	m_players[1]->setColor(Player::COLOR::YELLOW);
}

void ConnectFour::start()
{
	while (!m_board.fourAdjecent(m_redPlaying ? Player::COLOR::YELLOW : Player::COLOR::RED) && !m_board.isTie())
	{
		doMove();
		m_board.printBoard();
		switchTurnes();
	}
	end();
}

void ConnectFour::end() const
{
	if (m_board.isTie())
		std::cout << "Tie!";
	else if (m_redPlaying)
		std::cout << "O won!";
	else
		std::cout << "X won!";
}

void ConnectFour::doMove()
{
	if (m_redPlaying)
		m_board.dropColor(m_players[0]->doMove(m_board), Player::COLOR::RED);
	else
		m_board.dropColor(m_players[1]->doMove(m_board), Player::COLOR::YELLOW);
}

void ConnectFour::switchTurnes()
{
	m_redPlaying = !m_redPlaying;
}

