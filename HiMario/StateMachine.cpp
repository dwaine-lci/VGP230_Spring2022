#include "StateMachine.h"

StateMachine::StateMachine()
{

}
StateMachine::~StateMachine()
{

}

void StateMachine::Init()
{
	_states.resize((int)PlayerStates::Count);
	_states[(int)PlayerStates::Idle] = new IdleState();
	_states[(int)PlayerStates::Walk] = new WalkState();
	_states[(int)PlayerStates::Jump] = new JumpState();
	_states[(int)PlayerStates::Fall] = new FallState();
	_currentState = PlayerStates::Fall;
}
void StateMachine::UpdateState(Player* player, float deltaTime)
{
	PlayerStates newState = _states[(int)_currentState]->Update(player, deltaTime);
	if (newState != _currentState)
	{
		_states[(int)_currentState]->EndState();
		_currentState = newState;
		_states[(int)_currentState]->InitState(player);
	}
}
void StateMachine::Cleanup()
{
	for (int i = 0; i < _states.size(); ++i)
	{
		delete _states[i];
	}
	_states.clear();
}
PlayerStates StateMachine::GetActiveState()
{
	return _currentState;
}