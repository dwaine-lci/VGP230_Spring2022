#pragma once
enum class EntityType
{
	UI,
	Ship,
	Enemy,
	BulletPool,
	Bullet
};
enum class BulletType
{
	BULLET_01,
	BULLET_02
};

enum class GameStateType
{
	StartGame,
	RunGame,
	EndGame,
	Count
};