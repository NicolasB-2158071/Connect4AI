#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Board.h"

Board::Board()
{
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLUMNS; j++)
			m_board[i][j] = Player::COLOR::EMPTY;

    srand((unsigned)time(NULL));
}

void Board::undoDrop(int column)
{
    if (0 > column || COLUMNS <= column)
        throw std::out_of_range("Column out of range");
    int row = ROWS - 1;
    while (m_board[row][column] == Player::COLOR::EMPTY && row > 0)
        row--;
    if (m_board[row][column] == Player::COLOR::EMPTY)
        throw std::out_of_range("Column is empty");
    m_board[row][column] = Player::COLOR::EMPTY;
}

// c++ row major
void Board::dropColor(int column, const Player::COLOR& color)
{
    if (0 > column || COLUMNS <= column)
        throw std::out_of_range("Column out of range");
    int row = 0;
    while (m_board[row][column] != Player::COLOR::EMPTY && row < ROWS)
        row++;
    if (m_board[row][column] != Player::COLOR::EMPTY)
        throw std::out_of_range("Column is full");
    m_board[row][column] = color;
}

bool Board::terminalState() const
{
    if (fourAdjecent(Player::COLOR::RED) || fourAdjecent(Player::COLOR::YELLOW) || isTie())
        return true;
    return false;
}


bool Board::isTie() const
{
    for (int i = 0; i < COLUMNS; i++)
        if (m_board[ROWS - 1][i] == Player::COLOR::EMPTY)
            return false;
    return true;
}

bool Board::fourAdjecent(const Player::COLOR& color) const
{
    if (!checkRows(color))
        if (!checkColumns(color))
            if (!checkDownDiagonals(color))
                if (!checkUpDiagonals(color))
                    return false;
    return true;
}

bool Board::checkColumns(const Player::COLOR& color) const
{
    for (int i = 0; i < ROWS - 3; i++)
        for (int j = 0; j < COLUMNS; j++) {
            if (m_board[i][j] == color &&
                m_board[i + 1][j] == color &&
                m_board[i + 2][j] == color &&
                m_board[i + 3][j] == color)
                return true;
        }
    return false;
}

bool Board::checkRows(const Player::COLOR& color) const
{
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLUMNS - 3; j++) {
            if (m_board[i][j] == color &&
                m_board[i][j + 1] == color &&
                m_board[i][j + 2] == color &&
                m_board[i][j + 3] == color)
                return true;
        }
    return false;
}

bool Board::checkUpDiagonals(const Player::COLOR& color) const
{
    for (int i = 3; i < ROWS; i++)
        for (int j = 0; j < COLUMNS - 3; j++) {
            if (m_board[i][j] == color &&
                m_board[i - 1][j + 1] == color &&
                m_board[i - 2][j + 2] == color &&
                m_board[i - 3][j + 3] == color)
                return true;
        }
    return false;
}

bool Board::checkDownDiagonals(const Player::COLOR& color) const
{
    for (int i = 0; i < ROWS - 3; i++)
        for (int j = 0; j < COLUMNS - 3; j++) {
            if (m_board[i][j] == color &&
                m_board[i + 1][j + 1] == color &&
                m_board[i + 2][j + 2] == color &&
                m_board[i + 3][j + 3] == color)
                return true;
        }
    return false;
}

void Board::printBoard() const
{
    system("cls");
    for (int i = ROWS - 1; i >= 0; i--)
    {
        std::cout << i << " |";
        for (int j = 0; j < COLUMNS; j++)
        {
            switch (m_board[i][j])
            {
                case Player::COLOR::RED:
                    std::cout << " X ";
                    break;
                case Player::COLOR::YELLOW:
                    std::cout << " O ";
                    break;
                default:
                    std::cout << "   ";
            }
            std::cout << '|';
        }
        std::cout << '\n';
    }
    std::cout << "   ";
    for (int i = 0; i < COLUMNS; i++)
        std::cout << ' ' << i << "  ";
    std::cout << '\n';
}

std::vector<int> Board::getPossibleMoves() const
{
    std::vector<int> ret{};
    for (int i = 0; i < COLUMNS; i++)
        if (m_board[ROWS - 1][i] == Player::COLOR::EMPTY)
            ret.push_back(i);
    return ret;
}

int Board::getRandomMove() const
{
    int moves[COLUMNS]{};
    int size{};
    for (int i = 0; i < COLUMNS; i++)
    {
        if (m_board[ROWS - 1][i] == Player::COLOR::EMPTY)
        {
            moves[size] = i;
            size++;
        }
    }
    return moves[rand() % size];
}