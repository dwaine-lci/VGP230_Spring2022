#pragma once
#include <XEngine.h>
#include "BulletPool.h"

class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void Update(float deltaTime);
	void Render();
	void Cleanup();

private:
	void FireWeapon(const X::Math::Vector2& direction);
	X::TextureId _textureId;
	X::Math::Vector2 _position;
	BulletPool _bulletPool;
};