#include "Game.h"
#include "Ship.h"
#include "BulletPool.h"
#include "GameStates.h"

Game::Game()
{

}
Game::~Game()
{

}

void Game::Init()
{
	int bulletPoolSize = 20;
	BulletPool* bulletPool = new BulletPool(bulletPoolSize);
	XASSERT(AddEntity(bulletPool), "failed to add bullet pool");
	XASSERT(AddEntity(new Ship(bulletPool)), "failed to add ship");
	XASSERT(AddEntity(new GameStates()), "failed to add GameStates");

	for (auto e : _entities)
	{
		e->Init();
	}
}

bool Game::Update(float deltaTime)
{
	for (auto e : _entities)
	{
		e->Update(deltaTime);
	}

	Render();

	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}
void Game::Render()
{
	for (auto e : _entities)
	{
		e->Render();
	}
}

void Game::Cleanup()
{
	for (auto e : _entities)
	{
		e->Cleanup();
		delete(e);
	}
	_entities.clear();
}
bool Game::AddEntity(Entity* entity)
{
	if (entity == nullptr)
	{
		return false;
	}

	_entities.push_back(entity);

	return true;
}