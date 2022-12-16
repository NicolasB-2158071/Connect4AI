#include <algorithm>
#include <vector>
#include "ABPAI.h"
#include "../Board.h"


int ABPAI::doMove(const Board& board)
{
	Board copy{ board };
	std::vector<int> possibleMoves{ std::move(board.getPossibleMoves()) };
	int bestMove{possibleMoves[0]};
	int bestValue{};
	bool maximizing{ getColor() == Player::COLOR::RED};
	for (auto move : possibleMoves)
	{
		copy.dropColor(move, getColor());
		alfaBetaResult res{ alfaBeta(copy, DEPTH, -9999, 9999, !maximizing)};
		if ((maximizing && res.value > bestValue) || (!maximizing && res.value < bestValue))
		{
			bestMove = move;
			bestValue = res.value;
		}
		copy.undoDrop(move);
	}
	return bestMove;
}

alfaBetaResult ABPAI::alfaBeta(Board& board, int depth, int alfa, int beta, bool maximizing) const
{
	if (depth == 0 || board.terminalState())
		return alfaBetaResult{evaluate(board, maximizing), 0};
	if (maximizing)
	{
		int maxValue = -9999;
		int maxMove = 0;
		for (auto move : board.getPossibleMoves())
		{
			board.dropColor(move, Player::COLOR::RED);
			alfaBetaResult res{ alfaBeta(board, depth - 1, alfa, beta, false) };
			board.undoDrop(move);
			if (res.value > maxValue)
			{
				maxValue = res.value;
				maxMove = res.move;
			}
			if (std::max(alfa, res.value) >= beta)
				break;
		}
		return alfaBetaResult{ maxValue, maxMove };
	}
	int minValue = 9999;
	int minMove = 0;
	for (auto move : board.getPossibleMoves())
	{
		board.dropColor(move, Player::COLOR::YELLOW);
		alfaBetaResult res{ alfaBeta(board, depth - 1, alfa, beta, true) };
		board.undoDrop(move);
		if (res.value < minValue)
		{
			minValue = res.value;
			minMove = res.move;
		}
		if (std::min(beta, res.value) <= alfa)
			break;
	}
	return alfaBetaResult{ minValue, minMove };
}

int ABPAI::evaluate(const Board& board, bool maximizing) const
{
	int payOff{};
	bool redPlaying{ maximizing };
	Board copy{ board };
	for (int i = 0; i < AMOUNT; i++)
	{
		while (!copy.terminalState())
		{
			copy.dropColor(copy.getRandomMove(), redPlaying ? Player::COLOR::RED : Player::COLOR::YELLOW);
			redPlaying = !redPlaying;
		}
		if (!copy.isTie())
		{
			if (copy.fourAdjecent(Player::COLOR::RED))
				payOff += 1;
			else
				payOff -= 1;
		}
		copy = board;
	}
	return payOff;
}


