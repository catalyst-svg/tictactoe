#ifndef TICTAC_H
#define TICTAC_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

class player
{
	const std::string m_name;
public:
	player(const std;:string name);

	void getName() const;
};

class board
{
public:
	static std::vector<std::vector<char>> board1;
	static void printBoard();
	static void placement(int userRow, int userCol, char userS);
};

class board
{
public:
	static bool play1;
	static bool turnManager();
	static bool winChecker(std::vector<std::vector<char>>& gameBoard,int rowChose,int colChose);
};

std::string name;
bool whichTurn;
bool isWinner;

#endif


