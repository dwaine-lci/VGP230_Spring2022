#pragma once
#include "Player.h"
#include "Enemy.h"

class Game
{
public:
	virtual ~Game();
	static Game* Get();

	void Init();
	void Update(float deltaTime);
	void Render();
	void Stop();
	
	std::vector<Enemy>& GetEnemies() { return _enemies; }

private:
	Game();
	static Game* _instance;

	Player _player;
	std::vector<Enemy> _enemies;
};