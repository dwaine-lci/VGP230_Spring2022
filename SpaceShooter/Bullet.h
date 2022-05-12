#pragma once
#include "Entity.h"
#include "XEngine.h"
#include "Enums.h"
class Game;

class Bullet : public Entity
{
public:
	Bullet();
	virtual ~Bullet();

	void Activate(Game* game, Entity* owner, BulletType bulletType, const X::Math::Vector2& position, float rotation, float lifeTime);

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Cleanup() override;
private:
	Game* _game;
	Entity* _owner;
	X::TextureId _textureId;
	X::Math::Vector2 _position;
	float _rotation;
	float _lifeTime;

	X::SoundId _photonShot;
};