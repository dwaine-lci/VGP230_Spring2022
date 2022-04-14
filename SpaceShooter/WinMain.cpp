#include <XEngine.h>
#include "Game.h"

Game game;
void GameInit()
{
	game.Init();
}

bool GameLoop(float deltaTime)
{
	return game.Update(deltaTime);
}

void GameCleanup()
{
	game.Cleanup();
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{	
	X::Start();
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}