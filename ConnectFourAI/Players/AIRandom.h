#pragma once

#include "Player.h"
#include "../Board.h"

class AIRandom : public Player
{
public:
	int doMove(const Board& board) override;

};