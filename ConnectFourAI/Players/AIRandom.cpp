#include "AIRandom.h"

int AIRandom::doMove(const Board& board)
{
	return board.getRandomMove();
}