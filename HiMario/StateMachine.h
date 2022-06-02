#pragma once
#include "Enums.h"
#include "States.h"
#include <vector>

class Player;

class StateMachine
{
public:
	StateMachine();
	virtual ~StateMachine();

	void Init();
	void UpdateState(Player* player, float deltaTime);
	void Cleanup();

private:
	PlayerStates _currentState;
	std::vector<States*> _states;
};