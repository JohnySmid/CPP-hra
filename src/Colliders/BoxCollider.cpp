#include "BoxCollider.h"

BoxCollider::BoxCollider(Vector2d size)
	: Collider(ColliderType::Box)
{
	AddVert(0, Vector2d(-0.5f * size.x, -0.5f * size.y));
	AddVert(1, Vector2d(0.5f * size.x, -0.5f * size.y));
	AddVert(2, Vector2d(-0.5f * size.x, 0.5f * size.y));
	AddVert(3, Vector2d(0.5f * size.x, 0.5f * size.y));

	if (DEBUG_COLIDER)
	{
		SetDebugTXT(new Texture("BoxCollider.png"));
		mDebugTXT->SetScale(size / 128.0f);
	}
}

BoxCollider::~BoxCollider()
{
	for (int i = 0; i < MAX_VERTS; i++)
	{
		delete mVerts[i];
		mVerts[i] = nullptr;
	}
}

void BoxCollider::AddVert(int index, Vector2d pos)
{
	mVerts[index] = new GameEntity(pos.x, pos.y);
	mVerts[index]->SetParent(this);
}

Vector2d BoxCollider::GetPoint()
{
	Vector2d localpos = GetPos(local);

	int pointindex = 0;
	float dist = (localpos + mVerts[0]->GetPos(local)).Magnitude();
	float helpdist = 0.0f;

	for (int i = 1; i < MAX_VERTS; i++)
	{
		helpdist = (localpos + mVerts[i]->GetPos(local)).MagnitudeSqr();
		if (helpdist > dist)
		{
			pointindex = i;
			dist = helpdist;
		}
	}

	return localpos + mVerts[pointindex]->GetPos(local);

}

Vector2d BoxCollider::GetVertexPos(int index)
{
	return mVerts[index]->GetPos();
}