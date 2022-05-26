#include "Enemy.h"
#include "Bullet.h"
#include "BulletPool.h"
#include "TileMap.h"

Enemy::Enemy()
{

}
Enemy::~Enemy()
{

}

void Enemy::Init()
{
	_textureId = X::LoadTexture("pikachu.png");
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
			X::Math::Vector2 randDir = X::RandomUnitCircle();
			_targetPosition = _startPosition + (randDir * _moveRadius);
			_randomMoveTime = X::RandomFloat(1.0f, 2.0f);
		}
		else
		{
			const float speed = 50.0f;
			X::Math::Vector2 moveDir = X::Math::Normalize(_targetPosition - _position);
			_randomMoveTime -= deltaTime;
			X::Math::Vector2 displacement = moveDir * speed * deltaTime;
			if (X::Math::MagnitudeSqr(displacement) > 0.0f)
			{
				float halfWidth = X::GetSpriteWidth(_textureId) * 0.5f;
				float halfHeight = X::GetSpriteHeight(_textureId) * 0.5f;
				const float edgeBuffer = 5.0f;
				X::Math::Rect enemyRect;
				enemyRect.left = _position.x - halfWidth + edgeBuffer;
				enemyRect.right = _position.x + halfWidth - edgeBuffer;
				enemyRect.top = _position.y - halfHeight + edgeBuffer;
				enemyRect.bottom = _position.y + halfHeight;
				if (TileMap::Get()->CanMoveToDirection(enemyRect, displacement))
				{
					_position += displacement;
				}
			}
		}
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