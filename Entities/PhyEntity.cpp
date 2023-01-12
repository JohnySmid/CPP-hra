#include "PhyEntity.h"
#include "../Helpers/PhyHelper.h"
#include "../Managers/PhyManager.h"

PhyEntity::PhyEntity()
{
	mCircleCollider = nullptr;
	mId = 0;
}

PhyEntity::~PhyEntity()
{
	for (int i = 0; i < mColliders.size(); i++)
	{
		delete mColliders[i];
		mColliders[i] = nullptr;
	}
	mColliders.clear();

	delete mCircleCollider;
	mCircleCollider = nullptr;

	if (mId != 0)
	{
		PhyManager::Instance()->UnregisterEntity(mId);
	}
}

unsigned long PhyEntity::GetId()
{
	return mId;
}

bool PhyEntity::CheckCollision(PhyEntity* other)
{
	if (IgnoreCollision() || other->IgnoreCollision())
	{
		return false;
	}
	bool check = false;
	if (mCircleCollider && other->mCircleCollider)
	{
		check = ColliderColliderCheck(mCircleCollider, other->mCircleCollider);
	}
	else
	{
		check = true;
	}

	if (check)
	{
		for (int i = 0; i < mColliders.size(); i++)
		{
			for (int j = 0; j < other->mColliders.size(); j++)
			{
				if (ColliderColliderCheck(mColliders[i], other->mColliders[j]))
					return true;
			}
		}
	}

	return false;
}

void PhyEntity::Hit(PhyEntity* other)
{}

bool PhyEntity::IgnoreCollision()
{
	return false;
}

void PhyEntity::AddCollider(Collider* coll, Vector2d localPos)
{
	coll->SetParent(this);
	coll->SetPos(localPos);
	mColliders.push_back(coll);

	if (mColliders.size() > 1 || mColliders[0]->GetColType() != Collider::ColliderType::Circle)
	{
		float PointDist = mColliders[0]->GetPoint().Magnitude();
		float dist = 0.0f;

		for (int i = 1; i < mColliders.size(); i++)
		{
			dist = mColliders[i]->GetPoint().Magnitude();

			if (dist > PointDist)
				PointDist = dist;
		}

		delete mCircleCollider;
		mCircleCollider = new CircleCollider(PointDist);
		mCircleCollider->SetParent(this);
		mCircleCollider->SetPos(Vec2_ZERO);

	}
}



void PhyEntity::Render()
{
	for (int i = 0; i < mColliders.size(); i++)
	{
		mColliders[i]->Render();
	}

	if (mCircleCollider)
		mCircleCollider->Render();
}