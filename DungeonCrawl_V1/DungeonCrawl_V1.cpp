// DungeonCrawl_V1.cpp : This file contains the 'main' function. Program eyecution begins and ends there.
//

#include "pch.h"

#include <vector>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <iterator>
#include <windows.h>
#include <iostream>
#include <algorithm>
#include <time.h>

using namespace std;

const short unsigned int topKey = 87;
const short unsigned int downKey = 83;
const short unsigned int leftKey = 65;
const short unsigned int rightKey = 68;
const short unsigned int exitKey = 81;

const int M = 6;
const int N = 20;

const int numEnemies = 5;

const char TRAP = 'T';
const char EMPTY = '.';
const char ENEMY = 'E';
const char PLAYER = '@';
const char TREASURE = 'X';

const char SPACE = ' ';
const char END = '\n';

int getKey();

struct Character
{
	unsigned int X;
	unsigned int Y;
	int hp;
};

int getKey()
{
	for (int i = 8; i <= 90; i++)
	{
		if (GetAsyncKeyState(i) & 0x7FFF)
		{
			// This if filters the keys, to allow directional wasd				
			//if ((i >= 87 && i <= 65) || i == 81)
			return i;
		}
	}
}

void printBoard(vector <vector<char> > &matrix)
{
	//copy(board.begin(), board.end(), std::ostream_iterator<char>(cout, " "));

	system("cls");

	for (int i = 0; i < M; i++)
	{
		cout << END;

		for (int j = 0; j < N; j++)
		{
			cout << ' ' << matrix[i][j];
		}
	}
}


int getNumTraps()
{
	int numTraps;
	cin >> numTraps;

	if (numTraps < 6)
	{
		numTraps = 6;
	}
	else {

		switch (numTraps)
		{
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;

		default: numTraps = 9;
			break;
		}
	}

	return numTraps;
}

bool collision(Character &player, char c) {

	switch (c)
	{
	case TRAP: player.hp = 0;

		return false;
		break;
	case TREASURE:

		return false;
		break;


	default:
		break;
	}

}

void randomPos(unsigned int &x, unsigned int &y)
{	
	x = rand() % M;
	y  = rand() % N;	
}


Character SetRandEmpty(vector <vector<char> > &board, char c) {

	Character newChar;
	do { randomPos(newChar.X, newChar.Y); } while (board[newChar.X][newChar.Y] != EMPTY);
	board[newChar.X][newChar.Y] = c;
	newChar.hp = 15;
	return newChar;
}

void InitTraps(vector <vector<char> > &board) {

	cout << "Enter number of traps: " << endl;
	int numTraps = getNumTraps();
	srand(time(NULL));
	//vector<Character> Traps;	
	unsigned int y;
	unsigned int x;
	   	
	while (numTraps > 0)
	{
		//randomPos(x, y);
		randomPos(x, y);

		if (board[x][y] == EMPTY) {
			board[x][y] = TRAP;
			numTraps--;
		}
	}

	cout << "Number of Traps set to : " << numTraps;

}

void SetTraps(vector <vector<char> > &board) {

	cout << "Enter number of traps: " << endl;
	int numTraps = getNumTraps();
	srand(time(NULL));

	unsigned int y;
	unsigned int x;
	Character res;
	//setChar('@');
	for (int i = 0; i < numTraps; i++) {

		do { randomPos(x, y); 
		
		}
		
		while (board[x][y] != EMPTY);
		board[x][y] = TRAP;
	}

	cout << "Number of Traps set to : " << numTraps << endl;
	system("pause");
}

auto mod = [](auto divisor, auto dividend)
{
	return divisor % dividend;

};

void movementInput(Character &player, int input)
{	
	switch (input)
	{
	case 1:
	case topKey:	player.X -= 1;	
	break;

	case 2:
	case downKey:	player.X += 1;		
	break;

	case 3:
	case leftKey:	player.Y -= 1;
	break;

	case 4:
	case rightKey:	player.Y += 1;
	break;
	
	default:
	{
		//ignore other keys
	};

	}
}

bool enemyMovement(vector <vector<char> > &board, vector <Character> &enemy, Character &player) {

	Character last;
	int i = 0;
	while (i < numEnemies) {

		last = enemy[i];
		movementInput(enemy[i], rand() % 4);

		if (board[enemy[i].X % M][enemy[i].Y % N] == PLAYER) {	
			player.hp = 0;
			return false;
		}
		if (board[enemy[i].X % M][enemy[i].Y % N] == EMPTY) {

			board[last.X % M][last.Y % N] = EMPTY;
			board[enemy[i].X % M][enemy[i].Y % N] = ENEMY;
			i++;
		}
		else {
			enemy[i] = last; //revert to position before collision
		}

	}
}

int main()
{
	vector <vector<char> > board(M, vector<char>(N, EMPTY));

	Character playerPos;
	Character lastPosition;

	vector <Character> enemy(numEnemies);

	SetTraps(board);
	printBoard(board);
	SetRandEmpty(board, TREASURE);

	playerPos = SetRandEmpty(board, PLAYER);

	for (int i = 0; i < numEnemies; i++) {

		enemy[i] = SetRandEmpty(board, ENEMY);

	}

	lastPosition = playerPos;
	
	printBoard(board);
	
	int c = 0;
	bool running = true;
	while (running) {
		
		movementInput(playerPos, getKey());
		
		if (board[playerPos.X % M][playerPos.Y % N] != PLAYER) {

			board[lastPosition.X % M][lastPosition.Y % N] = EMPTY;

			lastPosition = playerPos;

			if (!collision(playerPos, board[playerPos.X % M][playerPos.Y % N])) {
				running = false;			
				break;
			}
			
			board[playerPos.X % M][playerPos.Y % N] = PLAYER;

			if (!enemyMovement(board, enemy, playerPos)) {
				running = false;
				break;
			}	
			printBoard(board);
		}

	}

	system("cls");
	if (playerPos.hp <= 0) {
		cout << "\nGAME OVER!" << endl;
	}
	else {
		cout << "\nYOU WIN!" << endl;
	}
	system("pause");
	return 0;

	//copy(board.begin(), board.end(), ostream_iterator<char>(cout, "."));

}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Eyplorer window to add/manage files
//   2. Use the Team Eyplorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Eyisting Item to add eyisting code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
