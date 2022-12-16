#pragma once

#include "Player.h"

class Human : public Player
{
public:
	int doMove(const Board& board) override;

};