#include "States.h"
#include "Player.h"

const float cMaxSpeed = 100.0f;
const float cAcceleration = 100.0f;
const float cBreakAccel = 300.0f;
const float cGravity = 300.0f;
const float cJumpVelocity = -300.0f;
const float cMaxFallSpeed = 200.0f;

void IdleState::InitState(Player* player)
{
	player->SetVelocity(X::Math::Vector2::Zero());
	_playerPreviousPosition = player->GetPosition();
}

PlayerStates IdleState::Update(Player* player, float deltaTime)
{
	if (X::IsKeyDown(X::Keys::LEFT))
	{
		return PlayerStates::Walk;
	}
	else if (X::IsKeyDown(X::Keys::RIGHT))
	{
		return PlayerStates::Walk;
	}
	if (X::IsKeyDown(X::Keys::UP))
	{
		return PlayerStates::Jump;
	}
	if (player->GetPosition().y - _playerPreviousPosition.y > 0.0f)
	{
		return PlayerStates::Fall;
	}
	X::Math::Vector2 newVel = player->GetVelocity();
	newVel.y = cGravity * deltaTime;
	player->SetVelocity(newVel);

	return PlayerStates::Idle;
}
void IdleState::EndState()
{
}



void WalkState::InitState(Player* player)
{
	// update animations if possible
	_playerPreviousPosition = player->GetPosition();
}
PlayerStates WalkState::Update(Player* player, float deltaTime)
{
	X::Math::Vector2 newVel = player->GetVelocity();
	if (X::IsKeyDown(X::Keys::UP))
	{
		return PlayerStates::Jump;
	}
	if (X::IsKeyDown(X::Keys::LEFT))
	{
		float accel = (newVel.x > 0.0f) ? cBreakAccel : cAcceleration;
		newVel.x -= accel * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::RIGHT))
	{
		float accel = (newVel.x < 0.0f) ? cBreakAccel : cAcceleration;
		newVel.x += accel * deltaTime;
	}
	else
	{
		if (newVel.x > 0.0f)
		{
			newVel.x -= cBreakAccel * deltaTime;
		}
		else
		{
			newVel.x += cBreakAccel * deltaTime;
		}
	}
	newVel.y = cGravity * deltaTime;
	newVel.x = X::Math::Clamp(newVel.x, -cMaxSpeed, cMaxSpeed);
	player->SetVelocity(newVel);
	if (X::Math::Abs(newVel.x) <= 0.01f)
	{
		return PlayerStates::Idle;
	}
	if (player->GetPosition().y - _playerPreviousPosition.y > 0.0f)
	{
		return PlayerStates::Fall;
	}

	return PlayerStates::Walk;
}
void WalkState::EndState()
{
}

void JumpState::InitState(Player* player)
{
	// update animations if possible
	X::Math::Vector2 newVel = player->GetVelocity();
	newVel.y = cJumpVelocity;
	player->SetVelocity(newVel);
	_playerPreviousPosition = player->GetPosition();
}
PlayerStates JumpState::Update(Player* player, float deltaTime)
{
	X::Math::Vector2 newVel = player->GetVelocity();
	const X::Math::Vector2& position = player->GetPosition();
	if (position.y - _playerPreviousPosition.y >= 0.0f)
	{
		newVel.y = 0.0f;
	}
	if (X::IsKeyDown(X::Keys::LEFT))
	{
		newVel.x -= cAcceleration * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::RIGHT))
	{
		newVel.x += cAcceleration * deltaTime;
	}
	newVel.x = X::Math::Clamp(newVel.x, -cMaxSpeed, cMaxSpeed);
	newVel.y += cGravity * deltaTime;
	player->SetVelocity(newVel);
	if (newVel.y > 0.0f)
	{
		return PlayerStates::Fall;
	}

	_playerPreviousPosition = position;
	return PlayerStates::Jump;
}
void JumpState::EndState()
{
}

void FallState::InitState(Player* player)
{
	// update animations if possible
	_playerPreviousPosition = player->GetPosition();
}
PlayerStates FallState::Update(Player* player, float deltaTime)
{
	X::Math::Vector2 newVel = player->GetVelocity();
	const X::Math::Vector2& position = player->GetPosition();
	if (position.y - _playerPreviousPosition.y <= 0.0f)
	{
		if (X::Math::Abs(newVel.x) > 0.01f)
		{
			return PlayerStates::Walk;
		}
		else
		{
			return PlayerStates::Idle;
		}
	}
	else
	{
		if (X::IsKeyDown(X::Keys::LEFT))
		{
			newVel.x -= cAcceleration * deltaTime;
		}
		else if (X::IsKeyDown(X::Keys::RIGHT))
		{
			newVel.x += cAcceleration * deltaTime;
		}
		newVel.x = X::Math::Clamp(newVel.x, -cMaxSpeed, cMaxSpeed);
		newVel.y += cGravity * deltaTime;
		newVel.y = X::Math::Min(newVel.y, cMaxFallSpeed);
		player->SetVelocity(newVel);
	}
	_playerPreviousPosition = position;
	return PlayerStates::Fall;
}
void FallState::EndState()
{
}