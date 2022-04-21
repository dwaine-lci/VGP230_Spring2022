#pragma once
#include "Entity.h"
#include "XEngine.h"
#include "Enums.h"
#include <map>

class GameStates : public Entity
{
public:
	GameStates();
	virtual ~GameStates();

	void SetActiveGameState(GameStateType gameState);
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Cleanup() override;

private:
	GameStateType _activeGameState;
	std::map<GameStateType, Entity*> _gameStates;
};