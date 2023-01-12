#pragma once
#include "../Colliders/CircleCollider.h"
#include "../Colliders/BoxCollider.h"
#include "MathHelper.h"

inline float PointInPolygon(Vector2d* verts, int vertCount, const Vector2d& point)
{
	bool retVal = false;

	for (int i = 0, j = vertCount - 1; i < vertCount; j = i++)
	{
		if ((verts[i].y >= point.y) != (verts[j].y >= point.y))
		{
			Vector2d vec1 = (verts[i] - verts[j]).Normalized();
			Vector2d proj = verts[j] + vec1 * Dot(point - verts[j], vec1);
			if (proj.x > point.x)
			{
				retVal = !retVal;
			}
		}
	}

	return retVal;
}

inline float PointToLineDistance(const Vector2d& lineStart, const Vector2d& lineEnd, const Vector2d& point)
{
	Vector2d slope = lineEnd - lineStart;

	// vect mezi dotem a start linem, pak jej promitneme a odstranime magnitudemSqr-> pak projektujeme, a pokud je pred tak = start, pokud je za, tak = konec
	float param = Clamp(Dot(point - lineStart, slope) / slope.MagnitudeSqr(), 0.0f, 1.0f);

	Vector2d nearestPoint = lineStart + slope * param;

	return (point - nearestPoint).Magnitude();
}


inline bool CircleCircleCollision(CircleCollider* c1, CircleCollider* c2)
{
	return(c1->GetPos() - c2->GetPos()).Magnitude() < (c1->GetRadius() + c2->GetRadius());
}

inline bool BoxCirlceCollision(BoxCollider* box, CircleCollider* circle)
{
	float radCircle = circle->GetRadius();
	Vector2d posCircle = circle->GetPos();

	Vector2d quad[4];
	quad[0] = box->GetVertexPos(0);
	quad[1] = box->GetVertexPos(1);
	quad[2] = box->GetVertexPos(3);
	quad[3] = box->GetVertexPos(2);


	// Pokud se nachazi uvnitr kruhu
	for (int i = 0; i < 4; i++)
	{
		if ((quad[i] - posCircle).Magnitude() < radCircle)
			return true;
	}

	// Linie, podle zacatku / konce
	if (PointToLineDistance(box->GetVertexPos(0), box->GetVertexPos(1), posCircle) < radCircle ||
		PointToLineDistance(box->GetVertexPos(0), box->GetVertexPos(2), posCircle) < radCircle ||
		PointToLineDistance(box->GetVertexPos(2), box->GetVertexPos(3), posCircle) < radCircle ||
		PointToLineDistance(box->GetVertexPos(3), box->GetVertexPos(1), posCircle) < radCircle)
	{
		return true;
	}


	if (PointInPolygon(quad, 4, posCircle))
	{
		return true;
	}

	return false;
}

inline bool BoxBoxCollision(BoxCollider* b1, BoxCollider* b2)
{
	Vector2d projAxis[4];

	// Box 1
	projAxis[0] = (b1->GetVertexPos(0) - b1->GetVertexPos(1)).Normalized();
	projAxis[1] = (b1->GetVertexPos(0) - b1->GetVertexPos(2)).Normalized();
	float b1Min = 0.0f, b1Max = 0.0f;

	// Box 2
	projAxis[2] = (b2->GetVertexPos(0) - b2->GetVertexPos(1)).Normalized();
	projAxis[3] = (b2->GetVertexPos(0) - b2->GetVertexPos(2)).Normalized();
	float b2Min = 0.0f, b2Max = 0.0f;


	float proj1 = 0.0f, proj2 = 0.0f;


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			proj1 = Dot(b1->GetVertexPos(j), projAxis[i]);
			proj2 = Dot(b2->GetVertexPos(j), projAxis[i]);

			// Prvni projekce
			if (j == 0)
			{
				b1Min = b1Max = proj1;
				b2Min = b2Max = proj2;
			}
			else
			{
				// Min
				if (proj1 < b1Min)
					b1Min = proj1;
				if (proj2 < b2Min)
					b2Min = proj2;

				// Max
				if (proj1 > b1Max)
					b1Max = proj1;
				if (proj2 > b2Max)
					b2Max = proj2;
			}
		}

		// Half dist
		float halfDist1 = (b1Max - b1Min) * 0.5f;
		float halfDist2 = (b2Max - b2Min) * 0.5f;

		// Mid point
		float midPoint1 = b1Min + halfDist1;
		float midPoint2 = b2Min + halfDist2;


		// Overlap; abs = absolute dist.
		if (abs(midPoint1 - midPoint2) > (halfDist1 + halfDist2))
			return false;
	}

	return true;
}

inline bool ColliderColliderCheck(Collider* c1, Collider* c2)
{
	if (c1->GetColType() == Collider::ColliderType::Circle && c2->GetColType() == Collider::ColliderType::Circle)
		return CircleCircleCollision(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
	else if (c1->GetColType() == Collider::ColliderType::Box && c2->GetColType() == Collider::ColliderType::Circle)
		return BoxCirlceCollision(static_cast<BoxCollider*>(c1), static_cast<CircleCollider*>(c2));
	else if (c2->GetColType() == Collider::ColliderType::Box && c1->GetColType() == Collider::ColliderType::Circle)
		return BoxCirlceCollision(static_cast<BoxCollider*>(c2), static_cast<CircleCollider*>(c1));
	else if (c1->GetColType() == Collider::ColliderType::Box && c2->GetColType() == Collider::ColliderType::Box)
		return BoxBoxCollision(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2));

}