#pragma once
#include "Enums.h"
#include "XEngine.h"

class Player;

class States
{
public:
	States() {}
	virtual ~States() {}

	virtual void InitState(Player* player) = 0;
	virtual PlayerStates Update(Player* player, float deltaTime) = 0;
	virtual void EndState() = 0;
};

class IdleState : public States
{
public:
	IdleState() : States() {}
	virtual ~IdleState() {}
	virtual void InitState(Player* player) override;
	virtual PlayerStates Update(Player* player, float deltaTime) override;
	virtual void EndState() override;
private:
	X::Math::Vector2 _playerPreviousPosition;
};

class WalkState : public States
{
public:
	WalkState() : States() {}
	virtual ~WalkState() {}
	virtual void InitState(Player* player) override;
	virtual PlayerStates Update(Player* player, float deltaTime) override;
	virtual void EndState() override;
private:
	X::Math::Vector2 _playerPreviousPosition;
};

class JumpState : public States
{
public:
	JumpState() : States() {}
	virtual ~JumpState() {}
	virtual void InitState(Player* player) override;
	virtual PlayerStates Update(Player* player, float deltaTime) override;
	virtual void EndState() override;
private:
	X::Math::Vector2 _playerPreviousPosition;
};

class FallState : public States
{
public:
	FallState() : States() {}
	virtual ~FallState() {}
	virtual void InitState(Player* player) override;
	virtual PlayerStates Update(Player* player, float deltaTime) override;
	virtual void EndState() override;
private:
	X::Math::Vector2 _playerPreviousPosition;
};