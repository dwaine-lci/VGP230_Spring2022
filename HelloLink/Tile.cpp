#include "Tile.h"

Tile::Tile()
{

}

Tile::~Tile()
{

}

void Tile::Init(const TileData& data)
{
	_data = data;
}
void Tile::Update(float deltaTime)
{
	// if we have animating tiles
}

void Tile::Render()
{
	X::DrawSprite(_data.textureId, _data.position);
}

int Tile::GetX()
{
	return _data.xIndex;
}
int Tile::GetY()
{
	return _data.yIndex;
}

float Tile::GetWidth()
{
	if (_data.textureId == 0)
	{
		return 0;
	}
	return X::GetSpriteWidth(_data.textureId);
}
float Tile::GetHeight()
{
	if (_data.textureId == 0)
	{
		return 0;
	}
	return X::GetSpriteHeight(_data.textureId);
}

bool Tile::IsWalkable()
{
	return _data.tileType == TileType::Walkable;
}
const X::Math::Vector2& Tile::GetPosition()
{
	return _data.position;
}
const X::Math::Rect& Tile::GetRect()
{
	return _data.rect;
}