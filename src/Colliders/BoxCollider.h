#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
public:
	BoxCollider(Vector2d size);
	~BoxCollider();

	Vector2d GetPoint() override;
	Vector2d GetVertexPos(int index);

private:
	static const int MAX_VERTS = 4;
	GameEntity* mVerts[MAX_VERTS];

	void AddVert(int index, Vector2d pos);
};

