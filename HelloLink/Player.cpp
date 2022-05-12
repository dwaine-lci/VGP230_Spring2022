#include "Player.h"
#include "TileMap.h"


Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	_position = X::Math::Vector2(100, 100);
	_textureId = X::LoadTexture("mario_walk_01.png");
}

void Player::Update(float deltaTime)
{
	float halfWidth = X::GetSpriteWidth(_textureId) * 0.5f;
	float halfHeight = X::GetSpriteHeight(_textureId) * 0.5f;
	X::Math::Rect playerRect;
	playerRect.left = _position.x - halfWidth;
	playerRect.right = _position.x + halfWidth;
	playerRect.top = _position.y - halfHeight;
	playerRect.bottom = _position.y + halfHeight;

	const float speed = 1000.0f;
	X::Math::Vector2 direction(0.0f, 0.0f);
	if (X::IsKeyDown(X::Keys::LEFT))
	{
		direction.x = -speed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::RIGHT))
	{
		direction.x = speed * deltaTime;
	}
	if (X::IsKeyDown(X::Keys::UP))
	{
		direction.y = -speed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::DOWN))
	{
		direction.y = speed * deltaTime;
	}
	if (X::Math::MagnitudeSqr(direction) > 0.0f)
	{
		direction = X::Math::Normalize(direction);

		if (TileMap::Get()->CanMoveToDirection(playerRect, direction))
		{
			_position += direction;
		}
	}
}

void Player::Render()
{
	X::DrawSprite(_textureId, _position);
}

void Player::Cleanup()
{
}