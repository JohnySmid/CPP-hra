#include "CircleCollider.h"

CircleCollider::CircleCollider(float rad)
	: Collider(ColliderType::Circle)
{
	mRadius = rad;

	if (DEBUG_COLIDER)
	{
		SetDebugTXT(new Texture("Circle.png"));
		mDebugTXT->SetScale(Vec2_ONE * (rad * 2 / 128.0f));
	}

}


CircleCollider::~CircleCollider()
{}

Vector2d CircleCollider::GetPoint()
{
	return Vec2_RIGHT * (mRadius + GetPos(local).Magnitude());
}

float CircleCollider::GetRadius()
{
	return mRadius;
}