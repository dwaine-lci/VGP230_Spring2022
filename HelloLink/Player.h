#pragma once
#include <XEngine.h>

class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void Update(float deltaTime);
	void Render();
	void Cleanup();

private:
	X::TextureId _textureId;
	X::Math::Vector2 _position;
};