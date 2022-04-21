#pragma once
#include <vector>
#include "Entity.h"

class Bullet;

class BulletPool : public Entity
{
public:
	BulletPool(int size);
	virtual ~BulletPool();
	
	Bullet* GetNextBullet();

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Cleanup() override;

private:
	int _nextBulletIndex;
	std::vector<Bullet*> _bullets;
};