#pragma once
#include <vector>
#include "../Colliders/Collider.h"
class PhyEntity : public GameEntity
{
public:
	PhyEntity();
	virtual ~PhyEntity();

	unsigned long GetId();
	bool CheckCollision(PhyEntity* other);
	virtual void Hit(PhyEntity* other);

	virtual void Render();

	unsigned long mId;
protected:

	virtual bool IgnoreCollision();

	std::vector<Collider*> mColliders;
	Collider* mCircleCollider;

	void AddCollider(Collider* coll, Vector2d localPos = Vec2_ZERO);

};

