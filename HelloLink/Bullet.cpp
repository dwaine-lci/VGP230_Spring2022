#include "Bullet.h"
#include "Game.h";
#include "TileMap.h";
#include "Enemy.h"

Bullet::Bullet()
{

}
Bullet::~Bullet()
{

}

void Bullet::Activate(BulletType bulletType, const X::Math::Vector2& position, float rotation, float lifeTime)
{
	switch (bulletType)
	{
	case BulletType::BULLET_01: _textureId = X::LoadTexture("bullet1.png"); break;
	case BulletType::BULLET_02: _textureId = X::LoadTexture("bullet2.png"); break;
	default:
		break;
	}
	XASSERT(_textureId != 0, "bullet didnt get made");
	_position = position;
	_rotation = rotation;
	_lifeTime = lifeTime;
	X::PlaySoundOneShot(_photonShot);
}

void Bullet::Init()
{
	_textureId = 0;
	_position = X::Math::Vector2::Zero();
	_rotation = 0.0f;
	_lifeTime = 0.0f;

	_photonShot = X::LoadSound("photongun1.wav");
}
void Bullet::Update(float deltaTime)
{
	if (_lifeTime > 0.0f)
	{
		const float speed = 200.0f;
		X::Math::Vector2 direction = X::Math::Vector2::Forward(_rotation);
		_position += direction * speed * deltaTime;

		if (TileMap::Get()->HitsBlockableObject(_position))
		{
			_lifeTime = 0.0f;
		}
		std::vector<Enemy>& enemies = Game::Get()->GetEnemies();
		for (int i = 0; i < enemies.size(); ++i)
		{
			Enemy& enemy = enemies[i];
			if (enemy.IsAlive() && enemy.CheckHit(_position))
			{
				_lifeTime = 0.0f;
				enemy.OnHit(1);
				break;
			}
		}
	}
}
void Bullet::Render()
{
	if (_lifeTime > 0.0f && _textureId != 0)
	{
		X::DrawSprite(_textureId, _position, _rotation);
	}
}
void Bullet::Cleanup()
{
}