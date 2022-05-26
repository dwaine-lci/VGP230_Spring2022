#pragma once

#include "XEngine.h"
#include "Enums.h"

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Cleanup();
	virtual bool IsAlive() { return _health > 0; }
	virtual bool CheckHit(const X::Math::Vector2& pos);
	virtual void OnHit(int damage);
	void SetPosition(X::Math::Vector2& pos);

private:
	X::TextureId _textureId;
	X::Math::Vector2 _position;
	X::Math::Vector2 _startPosition;
	X::Math::Vector2 _targetPosition;
	float _moveRadius;
	float _rotation;
	float _randomMoveTime;
	int _health;
	float _hitRadius;
};