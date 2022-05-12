#include "BulletPool.h"
#include "Bullet.h"

BulletPool::BulletPool(int size)
	: Entity(EntityType::BulletPool)
	, _nextBulletIndex(0)
{
	_bullets.resize(size);
}

BulletPool::~BulletPool()
{
	Cleanup();
}

Bullet* BulletPool::GetNextBullet()
{
	Bullet* returnBullet = _bullets[_nextBulletIndex];
	_nextBulletIndex = (_nextBulletIndex + 1) % (int)_bullets.size();

	return returnBullet;
}

void BulletPool::Init()
{
	for (int i = 0; i < _bullets.size(); ++i)
	{
		_bullets[i] = new Bullet();
		_bullets[i]->Init();
	}
}
void BulletPool::Update(float deltaTime)
{
	for (int i = 0; i < _bullets.size(); ++i)
	{
		_bullets[i]->Update(deltaTime);
	}
}
void BulletPool::Render()
{
	for (int i = 0; i < _bullets.size(); ++i)
	{
		_bullets[i]->Render();
	}
}
void BulletPool::Cleanup()
{
	for (auto b : _bullets)
	{
		b->Cleanup();
		delete b;
	}
	_bullets.clear();
}