#pragma once
#include "XEngine.h"
class Entity;

class Game
{
public:
	Game();
	virtual ~Game();

	void Init();

	bool Update(float deltaTime);
	void Render();

	void Cleanup();

	bool AddEntity(Entity* entity);

private:
	std::vector<Entity*> _entities;
};