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

	const std::vector<Tile>& walkableTiles = TileMap::Get()->GetTilesOfType(TileType::Walkable);
	const int enemyCount = 5;
	for (int i = 0; i < enemyCount; ++i)
	{
		int randIndex = X::Random() % walkableTiles.size();
		Enemy newEnemy;
		X::Math::Vector2 randPos = walkableTiles[randIndex].GetPosition();
		newEnemy.SetPosition(randPos);
		newEnemy.Init();
		_enemies.push_back(newEnemy);
	}
}
void Game::Update(float deltaTime)
{
	TileMap::Get()->Update(deltaTime);
	_player.Update(deltaTime);
	for (int i = 0; i < _enemies.size(); ++i)
	{
		_enemies[i].Update(deltaTime);
	}
}
void Game::Render()
{
	TileMap::Get()->Render();
	_player.Render();
	for (int i = 0; i < _enemies.size(); ++i)
	{
		_enemies[i].Render();
	}
}

void Game::Stop()
{
	TileMap::Get()->Cleanup();
	_player.Cleanup();
	for (int i = 0; i < _enemies.size(); ++i)
	{
		_enemies[i].Cleanup();
	}
}