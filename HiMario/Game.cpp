#include "Game.h"
#include "TileMap.h"
#include "Tile.h"

Game* Game::_instance = nullptr;

Game::Game()
{
}
Game::~Game()
{

}

Game* Game::Get()
{
	if (_instance == nullptr)
	{
		_instance = new Game();
	}

	return _instance;
}

void Game::Init()
{
	TileMap::Get()->Init();
	_player.Init();
}
void Game::Update(float deltaTime)
{
	TileMap::Get()->Update(deltaTime);
	_player.Update(deltaTime);
}
void Game::Render()
{
	TileMap::Get()->Render();
	_player.Render();
}

void Game::Stop()
{
	TileMap::Get()->Cleanup();
	_player.Cleanup();
}