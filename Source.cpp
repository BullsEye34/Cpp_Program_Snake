#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

void draw(char main[][75], int score);
void reset(char main[][75]);
void move(char main[][75], int &parts, int pastCounter, int past[][2], int &apples, int &score, int &quit);
void check(int &direction);
void directionn(int direction, int &pastCounter, int past[][2]);
void apple(int &apples, char main[][75]);
void quitGame(int score);

using namespace std;

int main()
{
	//past is an array to help direct when the snakes body will go, 
	//did it like this so the behind pieces will follow the snakes head
	int past[1000][2]; //second bracket: 0 is up, 1 is side
	int parts = 3; //number of snake pieces
	char main[23][75];// 23 down, 73 wide is appropriate screen size
	int pastCounter = 6;//used in the use of past 
	int direction = 0;
	int apples = 0;
	int score = 0;
	int quit = 0;
	int playAgain = 1;
	srand(time(0));

	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);  -- color if wanted

	for (int x = 0; x < 1000; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			past[x][y] = 0;
		}
	}
	past[pastCounter][0] = 1; //keep the game from crashing because if you hit the wall it kicks you from the wall
	past[pastCounter][1] = 1;
	while (quit == 0)
	{
		//main rotation through all the game's functions.
		draw(main, score);
		check(direction);
		directionn(direction, pastCounter, past);
		reset(main);
		move(main, parts, pastCounter, past, apples, score, quit);
		Sleep(25); //pause to keep the game a normal speed...
		if (apples == 0)
		{
			//place more apples only if they are all gone
			apple(apples, main);
		}

	}
	quitGame(score);
	Sleep(10000);
	//getch();

}
void draw(char main[][75], int score)
{//draws the screen
	system("cls");
	printf("Score : %d\n", score);
	for (int x = 0; x < 23; x++)
	{
		for (int y = 0; y < 75; y++)
		{
			printf("%c", main[x][y]);
		}
		printf("\n");
	}

}

void reset(char main[][75])
{//resets the array to keep it from being filled with parts of snake that shouldn't be there after the snake has moved on
	for (int x = 0; x < 23; x++)
	{
		for (int y = 0; y < 75; y++)
		{
			if (main[x][y] == '@')
			{
				//doesn't reset the apples
				main[x][y] == '@';
			}
			else
			{
				if (x == 0 || x == 22 || y == 0 || y == 74)
				{//doesnt reset the border
					main[x][y] = 177;
				}
				else
				{
					main[x][y] = ' ';
				}
			}
		}
	}
}

void move(char main[][75], int &parts, int pastCounter, int past[][2], int &apples, int &score, int &quit)
{//moves the snake head, and has the body follow it
	if (past[pastCounter][0] == 22 || past[pastCounter][0] == 0)
	{
		//if te snake is on the border of the game you loose
		quit = 1;
	}
	if (past[pastCounter][1] == 74 || past[pastCounter][1] == 0)
	{
		quit = 1;
	}

	for (int x = 0; x < parts; x++)
	{
		if (main[past[pastCounter - x][0]][past[pastCounter - x][1]] == '@')
		{
			//if the snake (technically any part of the snake) eats and apple...
			apples--;
			parts++;
			score += 10;
		}
		if (main[past[pastCounter - x][0]][past[pastCounter - x][1]] == 'o')
		{
			//if the snake eats itself
			quit = 1;
		}
		else
		{
			//else the snakes new location is determined
			main[past[pastCounter - x][0]][past[pastCounter - x][1]] = 'o';
		}
	}
}
void check(int &direction)
{//checks if there has been user input
	int key = 0;
	if (_kbhit())
	{
		key = -_getch();
		switch (key)
		{
		case -72:
			direction = 2;
			break;
			//up
		case -77:
			direction = 0;
			break; //right
		case -80:
			direction = 3;
			break; //down
		case -75:
			direction = 1;
			break; //left
		}
	}

}
void directionn(int direction, int &pastCounter, int past[][2])
{//based on user input, detects which directing the snake head should be going
	int right;//adding to the array itself did not work, so i worked around it.
	int down;
	right = past[pastCounter][1];
	down = past[pastCounter][0];
	switch (direction)
	{
		//directs the snake based on direction
	case 0:
		right++;
		break;
	case 1:
		right--;
		break;
	case 2:
		down--;
		break;
	case 3:
		down++;
	}

	pastCounter++;
	past[pastCounter][0] = down;
	past[pastCounter][1] = right;
}
void apple(int &apples, char main[][75])
{//places apples on the screen
	int up = 0;
	int left = 0;
	apples = 3;

	for (int x = 0; x < apples; x++)
	{ //places appples, only if theres no border of part of the snake already in the space
		up = (rand() % 22);
		left = (rand() % 74);

		if (main[up][left] == 'o')
		{
			apple(apples, main);
		}
		if (main[up][left] == '*')
		{
			apple(apples, main);
		}
		else
		{
			main[up][left] = '@';
		}
	}
}




void quitGame(int score)
{//quits and displays score
	int quit = 0;
	system("cls");
	printf("GAME OVER!!!!\n\n");
	printf("You got a score of %d\n", score); 
}
//sadasd