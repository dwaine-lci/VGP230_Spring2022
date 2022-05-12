#include "Bullet.h"
#include "Game.h";

Bullet::Bullet()
	: Entity(EntityType::Bullet)
{

}
Bullet::~Bullet()
{

}

void Bullet::Activate(Game* game, Entity* owner, BulletType bulletType, const X::Math::Vector2& position, float rotation, float lifeTime)
{
	_game = game;
	_owner = owner;
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
		const std::vector<Entity*>& entities = _game->GetEntities();
		EntityType targetType = EntityType::Ship;
		if (_owner->GetType() == EntityType::Ship)
		{
			targetType = EntityType::Enemy;
		}
		for(auto entity : entities)
		{
			if (entity->GetType() == targetType && entity->IsAlive())
			{
				if (entity->CheckHit(_position))
				{
					entity->OnHit(1);
					_lifeTime = 0.0f;
					break;
				}
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