#pragma once
#include "Tile.h"

class TileMap
{
public:
	virtual ~TileMap();
	static TileMap* Get();

	void Init();
	void Update(float deltaTime);
	void Render();
	void Cleanup();

	void ReloadMap();
	bool CanMoveToDirection(const X::Math::Rect& movingObject, X::Math::Vector2& displacement);

private:
	TileMap();
	static TileMap* _instance;

	int _tileRows;
	int _tileCols;
	std::vector<Tile> _tiles;
};