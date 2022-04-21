#pragma once

#include "Entity.h"
#include "XEngine.h"

class GameHUD : public Entity
{
public:
	GameHUD();
	virtual ~GameHUD();

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Cleanup() override;

private:
	X::Math::Vector2 _healthBarPosition;
	X::Math::Vector2 _healthBarValuePosition;
	X::Math::Rect _healthRect;
	int _currentHealth;
	int _maxHealth;
	X::TextureId _healthBackground;
	X::TextureId _healthValue;
};