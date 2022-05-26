#include "TileMap.h"
#include <fstream>
#include <iostream>

X::TextureId cMapTextures[6];

TileMap* TileMap::_instance = nullptr;
TileMap::TileMap()
{

}

TileMap::~TileMap()
{


}
TileMap* TileMap::Get()
{
	if(_instance == nullptr)
	{
		_instance = new TileMap();
	}

	return _instance;
}

void TileMap::Init()
{
	cMapTextures[0] = X::LoadTexture("white.jpg");
	cMapTextures[1] = X::LoadTexture("blue.jpg");
	cMapTextures[2] = X::LoadTexture("green.jpg");
	cMapTextures[3] = X::LoadTexture("purple.jpg");
	cMapTextures[4] = X::LoadTexture("red.jpg");
	cMapTextures[5] = X::LoadTexture("yellow.jpg");

	_tileRows = 0;
	_tileCols = 0;
	_tiles.clear();

	ReloadMap();
}
void TileMap::Update(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::ENTER))
	{
		ReloadMap();
	}

	for (auto tileType : _tiles)
	{
		for (auto tile : tileType.second)
		{
			tile.Update(deltaTime);
		}
	}
}
void TileMap::Render()
{
	for (auto tileType : _tiles)
	{
		for (auto tile : tileType.second)
		{
			tile.Render();
		}
	}
}
void TileMap::Cleanup()
{
	_tileCols = 0;
	_tileRows = 0;
	_tiles.clear();
}

void TileMap::ReloadMap()
{
	const char fileName[255] = "./level.lvl";
	std::fstream inputStream;
	inputStream.open(fileName);
	
	inputStream >> _tileCols;
	inputStream >> _tileRows;

	_tiles.clear();
	float tileWidth = X::GetSpriteWidth(cMapTextures[0]);
	float tileHeight = X::GetSpriteHeight(cMapTextures[0]);
	X::Math::Vector2 offset(tileWidth * 0.5f, tileHeight * 0.5f);
	int numTiles = _tileCols * _tileRows;
	int dataType = 0;
	int tileIndex = 0;
	while(inputStream >> dataType)
	{
		TileData newData;
		newData.textureId = cMapTextures[dataType];
		newData.tileType = (dataType < 4)? TileType::Walkable : TileType::Wall;
		newData.xIndex = tileIndex % _tileCols;
		newData.yIndex = tileIndex / _tileCols;
		newData.position.x = tileWidth * newData.xIndex + offset.x;
		newData.position.y = tileHeight * newData.yIndex + offset.y;
		newData.rect.max = newData.position + offset;
		newData.rect.min = newData.position - offset;

		Tile newTile;
		newTile.Init(newData);
		_tiles[newData.tileType].push_back(newTile);
		++tileIndex;
	}
}
bool TileMap::CanMoveToDirection(const X::Math::Rect& movingObject, X::Math::Vector2& direction)
{
	bool checkX = true;
	float offsetX = 0.0f;
	float offsetY = 0.0f;
	float tileWidth = X::GetSpriteWidth(cMapTextures[0]);
	float tileHeight = X::GetSpriteHeight(cMapTextures[0]);
	float totalWidth = tileWidth * (float)_tileCols;
	float totalHeight = tileHeight * (float)_tileRows;
	X::Math::Rect moveRect;
	X::Math::Rect mapRect(0.0f, 0.0f, totalWidth, totalHeight);
	for (int i = 0; i < 2; ++i)
	{
		checkX = i == 0;
		// iterate through the tiles and see if the player can go that way
		X::Math::Vector2 checkDir(0.0f, 0.0f);
		if (checkX)
		{
			checkDir.x = direction.x;
			if (direction.x == 0.0f)
			{
				continue;
			}
		}
		else
		{
			checkDir.y = direction.y;
			if (direction.y == 0.0f)
			{
				continue;
			}
		}
		moveRect.min = X::Math::Vector2(movingObject.left + checkDir.x, movingObject.top + checkDir.y);
		moveRect.max = X::Math::Vector2(movingObject.right + checkDir.x, movingObject.bottom + checkDir.y);

		for(auto tile : _tiles[TileType::Wall])
		{
			const X::Math::Rect& tileRect = tile.GetRect();
			if (!tile.IsWalkable() && X::Math::Intersect(moveRect, tileRect))
			{
				if (checkX)
				{
					if (checkDir.x > 0.0f)
					{
						offsetX = X::Math::Min(direction.x, moveRect.max.x - tileRect.min.x + 0.5f);
					}
					else if (checkDir.x < 0.0f)
					{
						offsetX = X::Math::Min(X::Math::Abs(direction.x), tileRect.max.x - moveRect.min.x + 0.5f);
					}
				}
				else
				{
					if (checkDir.y > 0.0f)
					{
						offsetY = X::Math::Min(direction.y, moveRect.max.y - tileRect.min.y + 0.5f);
					}
					else if (checkDir.y < 0.0f)
					{
						offsetY = X::Math::Min(X::Math::Abs(direction.y), tileRect.max.y - moveRect.min.y + 0.5f);
					}
				}
			}
		}
	}
	moveRect.min = X::Math::Vector2(movingObject.left + direction.x, movingObject.top + direction.y);
	moveRect.max = X::Math::Vector2(movingObject.right + direction.x, movingObject.bottom + direction.y);
	if (moveRect.min.x <= mapRect.min.x || moveRect.min.y <= mapRect.min.y
		|| moveRect.max.x >= mapRect.max.x || moveRect.max.y >= mapRect.max.y)
	{
		return false;
	}

	if (offsetX > 0.0f || offsetY > 0.0f)
	{
		if (direction.x > 0.0f)
		{
			direction.x = X::Math::Max(direction.x - offsetX, 0.0f);
		}
		else if (direction.x < 0.0f)
		{
			direction.x = X::Math::Min(direction.x + offsetX, 0.0f);
		}
		if (direction.y > 0.0f)
		{
			direction.y = X::Math::Max(direction.y - offsetY, 0.0f);
		}
		else if (direction.y < 0.0f)
		{
			direction.y = X::Math::Min(direction.y + offsetY, 0.0f);
		}
	}

	return X::Math::MagnitudeSqr(direction) > 0.0f;
}
bool TileMap::HitsBlockableObject(X::Math::Vector2& position)
{
	bool hasHit = false;
	for (auto tile : _tiles[TileType::Wall])
	{
		if (X::Math::PointInRect(position, tile.GetRect()))
		{
			hasHit = true;
			break;
		}
	}

	return hasHit;
}
