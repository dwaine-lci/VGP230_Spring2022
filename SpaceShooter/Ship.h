#pragma once
#include "XEngine.h"
#include "Entity.h"
#include "Enums.h"

class Game;
class BulletPool;

class Ship : public Entity
{
public:
	Ship(Game* game, BulletPool* bulletPool);
	virtual ~Ship();

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Cleanup() override;
	virtual bool IsAlive() override { return _health > 0; }
	virtual bool CheckHit(const X::Math::Vector2& pos) override;
	virtual void OnHit(int damage) override;
	virtual const X::Math::Vector2& GetPosition() override { return _position; }

	void FireBullet();
	void SwitchBullet();

private:
	Game* _game;
	X::TextureId _textureId;
	X::Math::Vector2 _position;
	float _rotation;
	float _hitRadius;
	int _health;

	BulletType _bulletType;
	BulletPool* _bulletPool;
};