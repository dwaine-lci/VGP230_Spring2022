#include "GameHUD.h"

GameHUD::GameHUD()
{

}
GameHUD::~GameHUD()
{

}

void GameHUD::Init()
{
	_currentHealth = 3;
	_maxHealth = 10;
	_healthBackground = X::LoadTexture("bar_empty.png");
	_healthValue = X::LoadTexture("bar_red.png");

	_healthRect.right = X::GetSpriteWidth(_healthBackground);
	_healthRect.bottom = X::GetSpriteHeight(_healthBackground);

	_healthBarPosition = X::Math::Vector2(X::GetScreenWidth() / 2, 20);
	_healthBarValuePosition = _healthBarPosition;
	_healthBarValuePosition.x -= (_healthRect.right * 0.5f);
}

void GameHUD::Update(float deltaTime)
{
}

void GameHUD::Render()
{
	_healthRect.right = ((float)_currentHealth / (float)_maxHealth) * X::GetSpriteWidth(_healthBackground);
	X::DrawSprite(_healthBackground, _healthBarPosition);
	X::DrawSprite(_healthValue, _healthRect, _healthBarValuePosition, X::Pivot::Left);
}
void GameHUD::Cleanup()
{

}