#pragma once

#include "Player.h"
#include "../Board.h"

struct alfaBetaResult {
	int value;
	int move;
};

class ABPAI : public Player
{
public:
	int doMove(const Board& board) override;
	const int AMOUNT = 150;
	const int DEPTH = 2;

private:
	int evaluate(const Board& board, bool maximizing) const;
	alfaBetaResult alfaBeta(Board& board, int depth, int alfa, int beta, bool maximizing) const;
};