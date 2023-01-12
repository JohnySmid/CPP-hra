#pragma once
#include <math.h>

#define PI 3.14159265
#define DEG_TO_RED PI / 180.0f

struct Vector2d
{
	float x;
	float y;

	Vector2d(float _x = 0.0f, float _y = 0.0f)
		: x(_x), y(_y) {}

	float MagnitudeSqr()
	{
		return x * x + y * y;
	}

	float Magnitude()
	{
		return (float)sqrt(x*x + y*y);
	}

	Vector2d Normalized()
	{
		float mag = Magnitude();

		return Vector2d(x / mag, y / mag);
	}

	// Overloading
	Vector2d operator+=(const Vector2d& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vector2d operator-=(const Vector2d& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	//otoceni vektoru; flip
	Vector2d operator-() const
	{
		return Vector2d(-x, -y);
	}

};


// Overloading s 2 vektory
inline Vector2d operator+(const Vector2d& lhs, const Vector2d& rhs)
{
	return Vector2d(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Vector2d operator-(const Vector2d& lhs, const Vector2d& rhs)
{
	return Vector2d(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline Vector2d operator*(const Vector2d& lhs, const float& rhs)
{
	return Vector2d(lhs.x * rhs, lhs.y * rhs);
}

inline Vector2d operator/(const Vector2d& lhs, const float& rhs)
{
	return Vector2d(lhs.x / rhs, lhs.y / rhs);
}

// Rotace a Dot, Clamp, Lerp
inline Vector2d RotateVector(const Vector2d& vec, float angle)
{
	float radAngle = (float)(angle * DEG_TO_RED);

	return Vector2d((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle)));
}

inline float Dot(const Vector2d& vec1, const Vector2d& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

inline float Clamp(const float& val, const float& min, const float& max)
{
	if (val > max)
		return max;

	if (val < min)
		return min;

	return val;
}

inline Vector2d lerp(const Vector2d& start, const Vector2d end, float time)
{
	if (time <= 0.0f)
		return start;
	if (time >= 1.0f)
		return end;

	Vector2d dir = (end - start).Normalized();
	float mag = (end - start).Magnitude();

	return start + dir * mag * time;
}

// Const vektory, ktere vyuzivame -> spolecne s overloaded - mame vsechny strany
const Vector2d Vec2_ZERO = { 0.0f, 0.0f };
const Vector2d Vec2_ONE = { 1.0f, 1.0f };

const Vector2d Vec2_UP = { 0.0f, 1.0f };
const Vector2d Vec2_RIGHT = { 1.0f, 0.0f };