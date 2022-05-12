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

	int tileCount = _tileCols * _tileRows;
	for (int i = 0; i < tileCount; ++i)
	{
		_tiles[i].Update(deltaTime);
	}
}
void TileMap::Render()
{
	int tileCount = _tileCols * _tileRows;
	for (int i = 0; i < tileCount; ++i)
	{
		_tiles[i].Render();
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

	float tileWidth = X::GetSpriteWidth(cMapTextures[0]);
	float tileHeight = X::GetSpriteHeight(cMapTextures[0]);
	X::Math::Vector2 offset(tileWidth * 0.5f, tileHeight * 0.5f);
	int numTiles = _tileCols * _tileRows;
	for (int i = 0; i < numTiles; ++i)
	{
		int dataType = 0;
		inputStream >> dataType;

		TileData newData;
		newData.textureId = cMapTextures[dataType];
		newData.tileType = (dataType < 4)? TileType::Walkable : TileType::Wall;
		newData.xIndex = i % _tileCols;
		newData.yIndex = i / _tileCols;
		newData.position.x = tileWidth * newData.xIndex + offset.x;
		newData.position.y = tileHeight * newData.yIndex + offset.y;

		while (_tiles.size() <= i)
		{
			_tiles.push_back(Tile());
		}
		_tiles[i].Init(newData);
	}
}
bool TileMap::CanMoveToDirection(const X::Math::Rect& movingObject, X::Math::Vector2& direction)
{
	bool checkX = true;
	bool blocked = false;
	for (int i = 0; i < 2; ++i)
	{
		blocked = false;
		checkX = i == 0;
		// iterate through the tiles and see if the player can go that way
		X::Math::Vector2 checkDir(0.0f, 0.0f);
		if (checkX)
		{
			checkDir.x = direction.x;
		}
		else
		{
			checkDir.y = direction.y;
		}
		X::Math::Vector2 minValues(movingObject.left + checkDir.x, movingObject.top + checkDir.y);
		X::Math::Vector2 maxValues(movingObject.right + checkDir.x, movingObject.bottom + checkDir.y);

		float tileWidth = X::GetSpriteWidth(cMapTextures[0]);
		float tileHeight = X::GetSpriteHeight(cMapTextures[0]);
		float totalWidth = tileWidth * (float)_tileCols;
		float totalHeight = tileHeight * (float)_tileRows;

		// Top Left Point
		int xPos = (int)floor((minValues.x / totalWidth) * _tileCols);
		int yPos = (int)floor((minValues.y / totalHeight) * _tileRows);
		int index = (yPos * _tileCols) + xPos;
		if (index < 0 || index >= _tiles.size() || !_tiles[index].IsWalkable())
		{
			blocked = true;
		}

		// Top Right Point
		xPos = (int)floor((maxValues.x / totalWidth) * _tileCols);
		yPos = (int)floor((minValues.y / totalHeight) * _tileRows);
		index = (yPos * _tileCols) + xPos;
		if (index < 0 || index >= _tiles.size() || !_tiles[index].IsWalkable())
		{
			blocked = true;
		}

		// Bottom Right Point
		xPos = (int)floor((maxValues.x / totalWidth) * _tileCols);
		yPos = (int)floor((maxValues.y / totalHeight) * _tileRows);
		index = (yPos * _tileCols) + xPos;
		if (index < 0 || index >= _tiles.size() || !_tiles[index].IsWalkable())
		{
			blocked = true;
		}

		// Bottom Left Point
		xPos = (int)floor((minValues.x / totalWidth) * _tileCols);
		yPos = (int)floor((maxValues.y / totalHeight) * _tileRows);
		index = (yPos * _tileCols) + xPos;
		if (index < 0 || index >= _tiles.size() || !_tiles[index].IsWalkable())
		{
			blocked = true;
		}

		if (blocked)
		{
			if (checkX)
			{
				direction.x = 0.0f;
			}
			else
			{
				direction.y = 0.0f;
			}
		}
	}

	return X::Math::MagnitudeSqr(direction) > 0.0f;
}
