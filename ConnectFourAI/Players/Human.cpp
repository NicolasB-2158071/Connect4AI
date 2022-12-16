#include <iostream>
#include "Human.h"

int Human::doMove(const Board& board)
{
	int input;
	char player = (getColor() == Player::COLOR::RED ? 'X' : 'O');
	std::cout << player << " is playing:\n";
	std::cin >> input;
	return input;
}