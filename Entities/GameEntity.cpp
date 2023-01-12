#include "GameEntity.h"

GameEntity::GameEntity(float x, float y)
{
	mPos.x = x;
	mPos.y = y;
	mRotation = 0.0f;

	mActive = true;

	mParent = nullptr;

	mScale = Vec2_ONE;
}

GameEntity::~GameEntity()
{
	mParent = nullptr;
}

void GameEntity::SetPos(Vector2d pos)
{
	mPos = pos;
}

Vector2d GameEntity::GetPos(SPACE space)
{
	if (space == local || mParent == nullptr)
	{
		return mPos;
	}

	GameEntity* parent = mParent;
	Vector2d finalPos = mPos, parentScale = Vec2_ZERO;


	// Loop pres vsechny parents, **Fix** BoxBoxColl
	do
	{
		Vector2d parentScale = mParent->GetScale(local);
		finalPos = RotateVector(Vector2d(finalPos.x * parentScale.x, finalPos.y * parentScale.y), parent->GetRotation(local));
		finalPos += parent->GetPos(local);

		parent = parent->GetParent();

	} while (parent);


	return finalPos;
}

void GameEntity::SetRotation(float r)
{
	mRotation = r;

	if (mRotation > 360.0f) {
		int mul = mRotation / 360;
		mRotation -= 360.0f * mul;
	}
	else if (mRotation < 0.0f) {
		int mul = (mRotation / 360) - 1;
		mRotation -= 360.0f * mul;
	}
}

float GameEntity::GetRotation(SPACE space)
{
	if (space == local || mParent == nullptr)
		return mRotation;

	return mParent->GetRotation(world) + mRotation;
}


void GameEntity::SetScale(Vector2d scale)
{
	mScale = scale;
}

Vector2d GameEntity::GetScale(SPACE space)
{
	if (space == local || mParent == nullptr)
		return mScale;

	Vector2d scale = mParent->GetScale(world);
	scale.x *= mScale.x;
	scale.y *= mScale.y;

	return scale;
}

void GameEntity::SetActive(bool active)
{
	mActive = active;
}

bool GameEntity::GetActice()
{
	return mActive;
}

void GameEntity::SetParent(GameEntity* parent)
{

	if (parent == nullptr)
	{
		mPos = GetPos(world);
		mRotation = GetRotation(world);
		mScale = GetScale(world);
	}
	else
	{
		if (mParent != nullptr)
			SetParent(nullptr);

		Vector2d parentScale = parent->GetScale(world);

		//Pozice		
		mPos = RotateVector(GetPos(world) - parent->GetPos(world), parent->GetRotation(world));
		mPos.x /= parentScale.x;
		mPos.y /= parentScale.y;

		//Rotace
		mRotation -= parent->GetRotation(world);

		//Scale
		mScale = Vector2d(mScale.x / parentScale.x, mScale.y / parentScale.y);
	}

	mParent = parent;
}

GameEntity* GameEntity::GetParent()
{
	return mParent;
}

void GameEntity::Update()
{

}

void GameEntity::Render()
{

}

void GameEntity::SetTranslate(Vector2d vec, SPACE space)
{
	if (space == world)
		mPos += vec;			//overloading +=
	else
	{
		mPos += RotateVector(vec, GetRotation());
	}
}

void GameEntity::Rotation(float num)
{
	mRotation += num;
}
