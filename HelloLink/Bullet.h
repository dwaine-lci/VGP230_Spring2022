#pragma once
#include "XEngine.h"
#include "Enums.h"
class Game;

class Bullet
{
public:
	Bullet();
	virtual ~Bullet();

	void Activate(BulletType bulletType, const X::Math::Vector2& position, float rotation, float lifeTime);

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Cleanup();
private:
	X::TextureId _textureId;
	X::Math::Vector2 _position;
	float _rotation;
	float _lifeTime;

	X::SoundId _photonShot;
};