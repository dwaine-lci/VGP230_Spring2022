#pragma once
#include <XEngine.h>
#include "Enums.h"
#include "StateMachine.h"

class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void Update(float deltaTime);
	void Render();
	void Cleanup();

	const X::Math::Vector2& GetPosition();
	const X::Math::Vector2& GetVelocity();
	void SetVelocity(const X::Math::Vector2& velocity);

private:
	X::TextureId _textureId;
	X::Math::Vector2 _position;
	X::Math::Vector2 _velocity;
	X::Math::Vector2 _desiredMoveDistance;
	StateMachine _stateMachine;
};