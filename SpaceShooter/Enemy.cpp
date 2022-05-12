#include "Enemy.h"
#include "Bullet.h"
#include "BulletPool.h"
#include "Game.h"

Enemy::Enemy(Game* game, BulletPool* bulletPool)
	: Entity(EntityType::Enemy)
	, _game(game)
	, _bulletPool(bulletPool)
{

}
Enemy::~Enemy()
{

}

void Enemy::Init()
{
	_textureId = X::LoadTexture("fighter.png");
	XASSERT(_textureId != 0, "Missing Texture");

	_health = 10;
	_hitRadius = 30.0f;
	_rotation = 0.0f;
	_targetPosition;
	_moveRadius = 100;
}
void Enemy::SetPosition(X::Math::Vector2& pos)
{
	_position = pos;
	_startPosition = pos;
	_targetPosition = pos;
}
void Enemy::Update(float deltaTime)
{
	if (_health > 0)
	{
		const float rotationSpeed = X::Math::kPi * 0.5f;

		if (_randomMoveTime <= 0.0f || X::Math::MagnitudeSqr(_position - _targetPosition) < 10.0f)
		{
			Entity* ship = nullptr;
			auto entities = _game->GetEntities();
			for (auto e : entities)
			{
				if (e->GetType() == EntityType::Ship)
				{
					ship = e;
					break;
				}
			}
			if (ship != NULL)
			{
				_targetPosition = ship->GetPosition();
				_randomMoveTime = 99999;
			}
			else
			{
				X::Math::Vector2 randDir = X::RandomUnitCircle();
				_targetPosition = _startPosition + (randDir * _moveRadius);
				_randomMoveTime = X::RandomFloat(1.0f, 2.0f);
			}
		}
		else
		{
			const float speed = 50.0f;
			X::Math::Vector2 moveDir = X::Math::Normalize(_targetPosition - _position);
			_position += moveDir * speed * deltaTime;
			_randomMoveTime -= deltaTime;
		}
		//if (X::IsKeyDown(X::Keys::LEFT))
		//{
		//	_rotation -= rotationSpeed * deltaTime;
		//}
		//else if (X::IsKeyDown(X::Keys::RIGHT))
		//{
		//	_rotation += rotationSpeed * deltaTime;
		//}

		//if (X::IsKeyPressed(X::Keys::SPACE))
		//{
		//	FireBullet();
		//}
		//else if (X::IsKeyPressed(X::Keys::LSHIFT))
		//{
		//	SwitchBullet();
		//}
	}
}
void Enemy::Render()
{
	if (_health > 0)
	{
		X::DrawSprite(_textureId, _position, _rotation);
		X::DrawScreenCircle(_position, _hitRadius, X::Colors::Red);
	}
}
void Enemy::Cleanup()
{

}

bool Enemy::CheckHit(const X::Math::Vector2& pos)
{
	float magnitudeSqr = X::Math::DistanceSqr(pos, _position);
	return magnitudeSqr <= _hitRadius * _hitRadius;
}

void Enemy::OnHit(int damage)
{
	if (_health > 0)
	{
		_health -= damage;
	}
}

void Enemy::FireBullet()
{
	XASSERT(_bulletPool != nullptr, "bullet pool does not exist");
	Bullet* firedBullet = _bulletPool->GetNextBullet();

	const float offset = 60.0f;
	X::Math::Vector2 firePos = _position + (X::Math::Vector2::Forward(_rotation) * offset);
	firedBullet->Activate(_game, this, _bulletType, firePos, _rotation, 2.0f);
}

void Enemy::SwitchBullet()
{
	if (_bulletType == BulletType::BULLET_01)
	{
		_bulletType = BulletType::BULLET_02;
	}
	else
	{
		_bulletType = BulletType::BULLET_01;
	}
}