#include "Player.h"
#include "TileMap.h"
#include "Bullet.h"

Player::Player()
	: _bulletPool(20)
{
}

Player::~Player()
{
}

void Player::Init()
{
	_position = X::Math::Vector2(100, 100);
	_textureId = X::LoadTexture("mario_walk_01.png");
	_bulletPool.Init();
}

void Player::Update(float deltaTime)
{
	float halfWidth = X::GetSpriteWidth(_textureId) * 0.5f;
	float halfHeight = X::GetSpriteHeight(_textureId) * 0.5f;
	const float edgeBuffer = 5.0f;
	X::Math::Rect playerRect;
	playerRect.left = _position.x - halfWidth + edgeBuffer;
	playerRect.right = _position.x + halfWidth - edgeBuffer;
	playerRect.top = _position.y - halfHeight + edgeBuffer;
	playerRect.bottom = _position.y + halfHeight;

	const float speed = 100.0f;
	X::Math::Vector2 displacement(0.0f, 0.0f);
	if (X::IsKeyDown(X::Keys::LEFT))
	{
		displacement.x = -speed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::RIGHT))
	{
		displacement.x = speed * deltaTime;
	}
	if (X::IsKeyDown(X::Keys::UP))
	{
		displacement.y = -speed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::DOWN))
	{
		displacement.y = speed * deltaTime;
	}
	if (X::Math::MagnitudeSqr(displacement) > 0.0f)
	{
		if (TileMap::Get()->CanMoveToDirection(playerRect, displacement))
		{
			_position += displacement;
		}
	}
	if (X::IsKeyPressed(X::Keys::W))
	{
		FireWeapon(X::Math::Vector2(0.0f, -1.0f));
	}
	else if (X::IsKeyPressed(X::Keys::A))
	{
		FireWeapon(X::Math::Vector2(-1.0f, 0.0f));
	}
	if (X::IsKeyPressed(X::Keys::S))
	{
		FireWeapon(X::Math::Vector2(0.0f, 1.0f));
	}
	else if (X::IsKeyPressed(X::Keys::D))
	{
		FireWeapon(X::Math::Vector2(1.0f, 0.0f));
	}

	_bulletPool.Update(deltaTime);
}

void Player::FireWeapon(const X::Math::Vector2& direction)
{
	Bullet* firedBullet = _bulletPool.GetNextBullet();
	const float offset = 40.0f;
	X::Math::Vector2 firePos = _position + (direction * offset);
	float rotation = X::Math::kPi + atan2(-direction.x, direction.y);
	firedBullet->Activate(BulletType::BULLET_01, firePos, rotation, 2.0f);
}


void Player::Render()
{
	float halfWidth = X::GetSpriteWidth(_textureId) * 0.5f;
	float halfHeight = X::GetSpriteHeight(_textureId) * 0.5f;
	const float edgeBuffer = 5.0f;
	X::Math::Rect playerRect;
	playerRect.left = _position.x - halfWidth + edgeBuffer;
	playerRect.right = _position.x + halfWidth - edgeBuffer;
	playerRect.top = _position.y - halfHeight + edgeBuffer;
	playerRect.bottom = _position.y + halfHeight;

	X::DrawSprite(_textureId, _position);
	X::DrawScreenRect(playerRect, X::Colors::Green);

	_bulletPool.Render();
}

void Player::Cleanup()
{
	_bulletPool.Cleanup();
}