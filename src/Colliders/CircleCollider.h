#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
public:
	CircleCollider(float rad);
	~CircleCollider();
	Vector2d GetPoint() override;

	float GetRadius();

private:
	float mRadius;
};

