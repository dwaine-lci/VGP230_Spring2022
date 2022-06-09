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
	_desiredMoveDistance = X::Math::Vector2::One();
	_stateMachine.Init();
	_flip = X::Flip::None;

	const float frameRate = 0.1f;
	Animation animIdle;
	animIdle.Init(frameRate);
	animIdle.SetFrame(0, X::LoadTexture("mario_idle_01.png"));
	animIdle.SetFrame(1, X::LoadTexture("mario_idle_02.png"));

	Animation animWalk;
	animWalk.Init(frameRate);
	animWalk.SetFrame(0, X::LoadTexture("mario_walk_01.png"));
	animWalk.SetFrame(1, X::LoadTexture("mario_walk_02.png"));

	Animation animJump;
	animJump.Init(frameRate);
	animJump.SetFrame(0, X::LoadTexture("mario_jump_01.png"));

	Animation animFall;
	animFall.Init(frameRate);
	animFall.SetFrame(0, X::LoadTexture("mario_fall_01.png"));

	_animationController.AddAnimation((int)PlayerStates::Idle, animIdle);
	_animationController.AddAnimation((int)PlayerStates::Walk, animWalk);
	_animationController.AddAnimation((int)PlayerStates::Jump, animJump);
	_animationController.AddAnimation((int)PlayerStates::Fall, animFall);

	_animationController.PlayAnimation((int)PlayerStates::Idle);
}

void Player::Update(float deltaTime)
{
	const X::TextureId& activeTexture = _animationController.GetCurrentAnimationTexture();
	float halfWidth = X::GetSpriteWidth(activeTexture) * 0.5f;
	float halfHeight = X::GetSpriteHeight(activeTexture) * 0.5f;
	const float edgeBuffer = 5.0f;
	X::Math::Rect playerRect;
	playerRect.left = _position.x - halfWidth + edgeBuffer;
	playerRect.right = _position.x + halfWidth - edgeBuffer;
	playerRect.top = _position.y - halfHeight + edgeBuffer;
	playerRect.bottom = _position.y + halfHeight;

	PlayerStates currentState = _stateMachine.GetActiveState();
	_stateMachine.UpdateState(this, deltaTime);
	PlayerStates newState = _stateMachine.GetActiveState();
	if (newState != currentState)
	{
		_animationController.PlayAnimation((int)newState);
	}
	_animationController.Update(deltaTime);

	_desiredMoveDistance = _velocity * deltaTime;
	if (_velocity.x < -0.1f)
	{
		_flip = X::Flip::Horizontal;
	}
	else if (_velocity.x > 0.1f)
	{
		_flip = X::Flip::None;
	}
	if (X::Math::MagnitudeSqr(_desiredMoveDistance) > 0.0f)
	{
		if (TileMap::Get()->CanMoveToDirection(playerRect, _desiredMoveDistance))
		{
			float screenWidth = X::GetScreenWidth();
			X::Math::Vector2 offset = TileMap::Get()->GetOffset();
			float totalWidth = TileMap::Get()->GetTotalWidth();
			if ((offset.x >= 0.0f && _desiredMoveDistance.x < 0.0f)
				|| (totalWidth + offset.x <= screenWidth && _desiredMoveDistance.x > 0.0f)
				|| (_position.x > screenWidth * 0.25f && _desiredMoveDistance.x < 0.0f)
				|| (_position.x < screenWidth * 0.75f && _desiredMoveDistance.x > 0.0f))
			{
				_position += _desiredMoveDistance;
			}
			else
			{
				offset.x -= _desiredMoveDistance.x;
				_position.y += _desiredMoveDistance.y;
				offset.x = X::Math::Clamp(offset.x, screenWidth - totalWidth, 0.0f);
				TileMap::Get()->SetOffset(offset);
			}
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
	const X::TextureId& activeTexture = _animationController.GetCurrentAnimationTexture();
	float halfWidth = X::GetSpriteWidth(activeTexture) * 0.5f;
	float halfHeight = X::GetSpriteHeight(activeTexture) * 0.5f;
	const float edgeBuffer = 5.0f;
	X::Math::Rect playerRect;
	playerRect.left = _position.x - halfWidth + edgeBuffer;
	playerRect.right = _position.x + halfWidth - edgeBuffer;
	playerRect.top = _position.y - halfHeight + edgeBuffer;
	playerRect.bottom = _position.y + halfHeight;

	X::DrawSprite(activeTexture, _position, X::Pivot::Center, _flip);
	X::DrawScreenRect(playerRect, X::Colors::Green);
}

void Player::Cleanup()
{
}