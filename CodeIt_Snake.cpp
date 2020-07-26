// CodeIt_Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// ConsoleApplication4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<thread>
#include <string>
#include<vector>
#include<chrono>
using namespace std;

#include <chrono> 
using namespace std::chrono;


struct sSnakeSegment
{
	int x;
	int y;
};
#include "olcConsoleGameEngine.h"

class Snake : public olcConsoleGameEngine
{
public:
	Snake()
	{}
	virtual bool OnUserCreate()
	{
		snake = { {40,24},{41,24},{42,24} };
		FoodX = 20;
		FoodY = 24;
		bResetGame = true;
		keyLeft = false;
		keyRight = false; 
		keyLeftOld = false;
		keyRightOld = false;
		return true;

	}
	virtual bool OnUserUpdate(float fElapsedTime)
	{
		
		if (bResetGame)
		{
			bHasCollided = false;
			Direction = 3; // 0-3 in anticlokwise 1, is west 
			bResetGame = false;
			snake = { {40,24},{41,24},{42,24} };
			nAttempt++;
			nSnakeLength = 0;
		}

		//checking self joining
		int nCount = 0;
		for (auto s : snake)
		{
			if (nCount > 0 && snake.front().x == s.x && snake.front().y == s.y)
			{
				bHasCollided = true;
				break;
			}
			nCount++;
		}



		// Game
		if (bHasCollided || snake.front().x <= 3 || snake.front().x >= ScreenWidth() - 3 ||
			snake.front().y <= 3 || snake.front().y >= ScreenHeight() - 3)
		{
			// Do nothing until user releases space
			if (m_keys[VK_SPACE].bReleased)
				bResetGame = true;
			
		}
		else
		{ 
			if (m_keyNewState[VK_UP])
				Direction = 0;
			else if (m_keyNewState[VK_RIGHT])
				Direction = 1;
			else if (m_keyNewState[VK_DOWN])
				Direction = 2;
			else if (m_keyNewState[VK_LEFT])
				Direction = 3;
			 

			Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');
			DrawLine(3, 3, ScreenWidth() - 3, 3);
			DrawLine(ScreenWidth() - 3, 3, ScreenWidth() - 3, ScreenHeight() - 3);
			DrawLine(ScreenWidth() - 3, ScreenHeight() - 3, 3, ScreenHeight() - 3);
			DrawLine(3, ScreenHeight() - 3, 3, 3);

			// Fill whatever needed 


			// Collision Detection
			bHasCollided = false; //check the head 

			//Draw the things 
			DrawString(1, 1, L"Attempt: " + to_wstring(nAttempt) + L" Score: " + to_wstring(nSnakeLength) + L" High Score: " + to_wstring(nMaxSnakeLength));
			
			
			switch (Direction)
			{
			case 0: // UP
				snake.push_front({ snake.front().x, snake.front().y - 1 });
				break;
			case 1: // RIGHT
				snake.push_front({ snake.front().x + 1, snake.front().y });
				//snake.pop_back();
				break;
			case 2: // DOWN
				snake.push_front({ snake.front().x, snake.front().y + 1 });
				//snake.pop_back();
				break;
			case 3: // LEFT
				snake.push_front({ snake.front().x - 1, snake.front().y });
				//snake.pop_back();
				break;
			}
			

			if (snake.front().x == FoodX && snake.front().y == FoodY)
			{
				FoodX = 5 + rand() % (ScreenWidth() - 12);
				FoodY = 5 + rand() % (ScreenHeight() - 12);
				nSnakeLength++;
				if (nSnakeLength > nMaxSnakeLength)
					nMaxSnakeLength = nSnakeLength;

			}

			
			else
			{
				snake.pop_back();
			}
			



			 
			
			for (auto s : snake)
			{
				Draw(s.x, s.y);
			}
			sSnakeSegment head = snake.front();

			Draw(head.x, head.y, 0x40);
			Draw(FoodX, FoodY, 0x23);
			Sleep(100);
		}
		return true;

	}

private:
	
	//list<int, int> listSection;
	list<sSnakeSegment> snake;
	int Direction;
	int FoodX;
	int FoodY;
	bool bHasCollided = false;
	bool bResetGame = false;
	int nAttempt = 0;
	int nSnakeLength = 0;;
	int nMaxSnakeLength = 0;
	bool keyLeft, keyRight, keyLeftOld, keyRightOld;
	
};



int main()
{


	Snake game;
	game.ConstructConsole(80, 48, 16, 16);
	// width, height , charcter sizes

	game.Start();




	return 0;
}