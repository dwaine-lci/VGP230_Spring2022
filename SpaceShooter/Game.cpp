#include "Game.h"
#include "Ship.h"

Game::Game()
{

}
Game::~Game()
{

}

void Game::Init()
{
	XASSERT(AddEntity(new Ship(this)), "failed to add ship");

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