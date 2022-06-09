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

	const std::vector<Tile>& GetTilesOfType(TileType tileType);
	void ReloadMap();
	bool CanMoveToDirection(const X::Math::Rect& movingObject, X::Math::Vector2& displacement);
	bool HitsBlockableObject(X::Math::Vector2& position);

	float GetTotalWidth();
	float GetTotalHeight();
	void SetOffset(const X::Math::Vector2& offset);
	const X::Math::Vector2& GetOffset();

private:
	TileMap();
	static TileMap* _instance;

	X::Math::Vector2 _offset;
	int _tileRows;
	int _tileCols;
	std::map<TileType, std::vector<Tile>> _tiles;
};