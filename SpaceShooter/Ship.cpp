#include "Ship.h"
#include "Game.h"

Ship::Ship(Game* game)
	: _game(game)
{

}
Ship::~Ship()
{

}

void Ship::Init()
{
	_textureId = X::LoadTexture("carrier_01.png");
	XASSERT(_textureId != 0, "Missing Texture");

	_rotation = 0.0f;
	_position.x = X::GetScreenWidth() * 0.5f;
	_position.y = X::GetScreenHeight() * 0.5f;

	_nextBulletIndex = 0;
	const int poolSize = 30;
	for (int i = 0; i < poolSize; ++i)
	{
		Bullet* bullet = new Bullet();
		_bullets.push_back(bullet);
		_game->AddEntity((Entity*)bullet);
	}
}
void Ship::Update(float deltaTime)
{
	const float rotationSpeed = X::Math::kPi * 0.5f;
	if (X::IsKeyDown(X::Keys::LEFT))
	{
		_rotation -= rotationSpeed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::RIGHT))
	{
		_rotation += rotationSpeed * deltaTime;
	}
	
	if (X::IsKeyPressed(X::Keys::SPACE))
	{
		FireBullet();
	}
	else if (X::IsKeyPressed(X::Keys::LSHIFT))
	{
		SwitchBullet();
	}
}
void Ship::Render()
{
	X::DrawSprite(_textureId, _position, _rotation);
}
void Ship::Cleanup()
{

}

void Ship::FireBullet()
{
	Bullet* firedBullet = _bullets[_nextBulletIndex];
	_nextBulletIndex = (_nextBulletIndex + 1) % _bullets.size();

	const float offset = 60.0f;
	float rotationCorrection = (X::Math::kDegToRad * 90.0f) - _rotation;
	X::Math::Vector2 firePos = _position + (X::Math::Vector2::Forward(rotationCorrection) * offset);
	firedBullet->Activate(_bulletType, firePos, rotationCorrection, 2.0f);
}

void Ship::SwitchBullet()
{
	if (_bulletType == BulletType::BULLET_01)
	{
		_bulletType = BulletType::BULLET_02;
	}
	else
	{
		_bulletType = BulletType::BULLET_01;
	}
}