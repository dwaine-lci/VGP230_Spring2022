#pragma once
#include "XEngine.h"
#include "Entity.h"
#include "Bullet.h"
class Game;

class Ship : public Entity
{
public:
	Ship(Game* game);
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
	int _nextBulletIndex;
	std::vector<Bullet*> _bullets;
};