#pragma once
#include "Player.h"

class Game
{
public:
	virtual ~Game();
	static Game* Get();

	void Init();
	void Update(float deltaTime);
	void Render();
	void Stop();

private:
	Game();
	static Game* _instance;

	Player _player;
};