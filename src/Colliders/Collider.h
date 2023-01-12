#pragma once
#include "../Entities/Textures/Texture.h"

class Collider : public GameEntity
{
public:
	enum class ColliderType
	{
		Box,
		Circle
	};

	Collider(ColliderType type);
	virtual ~Collider();

	virtual Vector2d GetPoint() = 0;
	ColliderType GetColType();

	virtual void Render();

protected:
	ColliderType mType;
	static const bool DEBUG_COLIDER = false;	//true pro videni collider txt
	Texture* mDebugTXT;

	void SetDebugTXT(Texture* txt);
};

