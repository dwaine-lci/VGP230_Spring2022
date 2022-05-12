#include "Game.h"
#include "Ship.h"
#include "Enemy.h"
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
	XASSERT(AddEntity(new Ship(this, bulletPool)), "failed to add ship");
	XASSERT(AddEntity(new GameStates()), "failed to add GameStates");

	X::Math::Vector2 maxSpawnPos(X::GetScreenWidth(), X::GetScreenHeight());
	const int enemyCount = 5;
	for (int i = 0; i < enemyCount; ++i)
	{
		Enemy* newEnemy = new Enemy(this, bulletPool);
		X::Math::Vector2 randPos = X::RandomVector2(X::Math::Vector2::Zero(), maxSpawnPos);
		newEnemy->SetPosition(randPos);
		AddEntity(newEnemy);
	}

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
	const char hellowWorld[255] = "HELLO WORLD";
	float size = 0.0f;
	float width = X::GetTextWidth(hellowWorld, size);
	X::DrawScreenText(hellowWorld, (X::GetScreenWidth() - width) * 0.5f, 0.0f, size, X::Colors::Red);
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