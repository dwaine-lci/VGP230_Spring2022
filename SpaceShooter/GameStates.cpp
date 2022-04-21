#include "GameStates.h"
#include "GameHUD.h"

GameStates::GameStates()
{

}

GameStates::~GameStates()
{

}

void GameStates::SetActiveGameState(GameStateType gameState)
{
	_activeGameState = gameState;
}

void GameStates::Init()
{
	_activeGameState = GameStateType::RunGame;
	_gameStates[GameStateType::RunGame] = new GameHUD();

	for (auto gs : _gameStates)
	{
		gs.second->Init();
	}
}
void GameStates::Update(float deltaTime)
{
	_gameStates[_activeGameState]->Update(deltaTime);
}
void GameStates::Render()
{
	_gameStates[_activeGameState]->Render();
}
void GameStates::Cleanup()
{
	for (auto gs : _gameStates)
	{
		gs.second->Cleanup();
	}
}