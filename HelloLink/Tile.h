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

	const X::Math::Vector2& GetPosition();
	const X::Math::Rect& GetRect();

private:
	TileData _data;
};