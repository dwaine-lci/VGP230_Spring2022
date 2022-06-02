#include <XEngine.h>
#include "Game.h"

bool RunGame(float deltaTime)
{
	Game::Get()->Update(deltaTime);
	Game::Get()->Render();

	bool exit = X::IsKeyPressed(X::Keys::ESCAPE);
	return exit;
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	Game::Get()->Init();

	X::Run(RunGame);

	Game::Get()->Stop();
	X::Stop();

	return 0;
}