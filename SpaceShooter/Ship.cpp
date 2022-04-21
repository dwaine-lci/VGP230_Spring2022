#include "Ship.h"
#include "Bullet.h"
#include "BulletPool.h"
#include "Game.h"

Ship::Ship(BulletPool* bulletPool)
	: _bulletPool(bulletPool)
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
	XASSERT(_bulletPool != nullptr, "bullet pool does not exist");
	Bullet* firedBullet = _bulletPool->GetNextBullet();

	const float offset = 60.0f;
	X::Math::Vector2 firePos = _position + (X::Math::Vector2::Forward(_rotation) * offset);
	firedBullet->Activate(_bulletType, firePos, _rotation, 2.0f);
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