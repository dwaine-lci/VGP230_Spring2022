#pragma once
#include <XEngine.h>
#include "Enums.h"

struct TileData
{
	X::TextureId textureId;
	TileType tileType;
	X::Math::Vector2 position;
	int xIndex;
	int yIndex;

	TileData()
		: textureId(0)
		, tileType(TileType::Walkable)
		, position(0, 0)
		, xIndex(0)
		, yIndex(0)
	{

	}
};