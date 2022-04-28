#include <XEngine.h>
#include "Game.h"

const int map[5 * 5] = {
	0, 0, 0, 3, 3,
	0, 1, 0, 3, 3,
	0, 0, 0, 0, 0,
	0, 0, 2, 0, 1,
	0, 0, 0, 0, 0
};
X::TextureId mapTextures[6];

Game game;
void GameInit()
{
	game.Init();
	mapTextures[0] = X::LoadTexture("white.jpg");
	mapTextures[1] = X::LoadTexture("blue.jpg");
	mapTextures[2] = X::LoadTexture("green.jpg");
	mapTextures[3] = X::LoadTexture("purple.jpg");
	mapTextures[4] = X::LoadTexture("red.jpg");
	mapTextures[5] = X::LoadTexture("yellow.jpg");
}

bool GameLoop(float deltaTime)
{
	//X::Math::Vector2 mapOffset(X::GetScreenWidth() * 0.25f, X::GetScreenHeight() * 0.25f);
	//for (int y = 0; y < 5; ++y)
	//{
	//	for (int x = 0; x < 5; ++x)
	//	{
	//		int index = x + y * 5;
	//		X::TextureId textureId = mapTextures[map[index]];
	//		int textureWidth = X::GetSpriteWidth(textureId);
	//		int textureHeight = X::GetSpriteHeight(textureId);
	//		X::Math::Vector2 position(x * textureWidth, y * textureHeight);
	//		X::DrawSprite(textureId, position + mapOffset);
	//	}
	//}
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