#pragma once
#include <vector>

class Bullet;

class BulletPool
{
public:
	BulletPool(int size);
	virtual ~BulletPool();

	Bullet* GetNextBullet();

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Cleanup();

private:
	int _nextBulletIndex;
	std::vector<Bullet*> _bullets;
};