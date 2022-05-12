#pragma once
#include "XEngine.h"
#include "Enums.h"

class Entity
{
public:
	Entity() : _entityType(EntityType::UI) {}
	Entity(EntityType entityType) : _entityType(entityType) {}
	EntityType GetType() { return _entityType; }
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Cleanup() = 0;
	virtual bool IsAlive() { return true; }
	virtual bool CheckHit(const X::Math::Vector2& pos) { return false; }
	virtual void OnHit(int damage) {}
	virtual const X::Math::Vector2& GetPosition() { return X::Math::Vector2::Zero(); }
protected:
	EntityType _entityType;
};