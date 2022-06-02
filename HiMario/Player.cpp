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
	_position = X::Math::Vector2(X::GetScreenWidth()* 0.5f, X::GetScreenHeight() * 0.5f);
	_textureId = X::LoadTexture("mario_walk_01.png");
	_desiredMoveDistance = X::Math::Vector2::One();
	_stateMachine.Init();
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

	_stateMachine.UpdateState(this, deltaTime);
	_desiredMoveDistance = _velocity * deltaTime;
	if (X::Math::MagnitudeSqr(_desiredMoveDistance) > 0.0f)
	{
		if (TileMap::Get()->CanMoveToDirection(playerRect, _desiredMoveDistance))
		{
			_position += _desiredMoveDistance;
		}
	}
}
const X::Math::Vector2& Player::GetPosition()
{
	return _position;
}
const X::Math::Vector2& Player::GetVelocity()
{
	return _velocity;
}
void Player::SetVelocity(const X::Math::Vector2& velocity)
{
	_velocity = velocity;
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
}

void Player::Cleanup()
{
}