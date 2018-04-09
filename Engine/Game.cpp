/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snake({ 2,2 }),
	goal(rng, brd, snake)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{

	if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
		gameStarted = true;
	}
	if (wnd.kbd.KeyIsPressed(VK_END)) {
		delta_loc = { 0,0 };
		goal.Respawn(rng, brd, snake);
	}
	if (wnd.kbd.KeyIsPressed(VK_SPACE)) {
		snake.SnakeReset();
		gameIsOver = false;
	}
	if (!gameIsOver) {
		if (wnd.kbd.KeyIsPressed(VK_UP)) {
			
			if (!(delta_loc == Location {0,1}) && !snake.inputLocked) {
				delta_loc = { 0,-1 };
				snake.inputLocked = true;
			}
			
		}
		if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
			if (!(delta_loc == Location{ 0,-1 }) && !snake.inputLocked) {
				delta_loc = { 0,1 };
				snake.inputLocked = true;
			}
		}
		if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
			if (!(delta_loc == Location{ 1,0 }) && !snake.inputLocked) {
				delta_loc = { -1,0 };
				snake.inputLocked = true;
			}
		}
		if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
			if (!(delta_loc == Location{ -1,0 }) && !snake.inputLocked) {
				delta_loc = { 1,0 };
				snake.inputLocked = true;
			}
		}

		snake.inputLockCounter++;
		if (snake.inputLockCounter == 3) {
			snake.inputLocked = false;
			snake.inputLockCounter = 0;
		}
		snakeMoveCounter++;
		if (snakeMoveCounter >= snakeMovePeriod) {
			snakeMoveCounter = 0;

			Location next = snake.GetNextHeadLocation(delta_loc);
			if (!brd.IsInsideBoard(next) || snake.IsInTileExceptEnd(next)) {
				gameIsOver = true;
			}
			else {
				const bool eating = next == goal.GetLocation();
				if (eating || wnd.kbd.KeyIsPressed(VK_CONTROL)){
					snake.Grow();
				}
				if (goal.rainbow == true) {
					snakeMovePeriod = 2;
					snake.rainbow = true;
					snake.rainbowCounter++;
					if (snake.rainbowCounter == 10) {
						snakeMovePeriod = 5;
						goal.rainbow = false;
						snake.rainbow = false;
						goal.counter = 0;
						snake.rainbowCounter = 0;
					}
				}
				snake.MoveBy(delta_loc);

				if (eating) {
					goal.Respawn(rng, brd, snake);
				}
			}




		}
	}

}

void Game::ComposeFrame()
{
	if (gameStarted) {
		brd.DrawBackground();
		snake.Draw(brd);
		goal.Draw(brd);
		if (gameIsOver) {
			SpriteCodex::DrawGameOver(200, 200, gfx);
		}
	}
	else {
		SpriteCodex::DrawTitle(100, 100, gfx);
	}
}
