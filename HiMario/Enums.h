#pragma once

enum class TileType
{
	Walkable,
	Platform
};

enum class PlayerStates : int
{
	Idle,
	Walk,
	Jump,
	Fall,
	Count
};