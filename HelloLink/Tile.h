#pragma once
#include "Data.h"

class Tile
{
public:
	Tile();
	virtual ~Tile();
	
	void Init(const TileData& data);
	void Update(float deltaTime);
	void Render();

	int GetX();
	int GetY();

	float GetWidth();
	float GetHeight();

	bool IsWalkable();

private:
	TileData _data;
};