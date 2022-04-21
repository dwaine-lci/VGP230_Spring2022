#pragma once
#include "XEngine.h"
#include "Entity.h"
#include "Enums.h"

class Game;
class BulletPool;

class Ship : public Entity
{
public:
	Ship(BulletPool* bulletPool);
	virtual ~Ship();

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Cleanup() override;

	void FireBullet();
	void SwitchBullet();

private:
	Game* _game;
	X::TextureId _textureId;
	X::Math::Vector2 _position;
	float _rotation;

	BulletType _bulletType;
	BulletPool* _bulletPool;
};