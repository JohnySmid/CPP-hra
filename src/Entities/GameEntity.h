#pragma once
#include "../Helpers/MathHelper.h"

class GameEntity
{
public:
	enum SPACE
	{
		local = 0,
		world = 1
	};

	GameEntity(float x = 0.0f, float y = 0.0f);
	~GameEntity();

	void SetPos(Vector2d pos);
	Vector2d GetPos(SPACE space = world);

	void SetRotation(float rotation);
	float GetRotation(SPACE space = world);

	void SetScale(Vector2d scale);
	Vector2d GetScale(SPACE space = world);

	void SetActive(bool active);
	bool GetActice();

	void SetParent(GameEntity* parent);
	GameEntity* GetParent();

	virtual void Update();		//overriden
	virtual void Render();

	void SetTranslate(Vector2d vec, SPACE space);
	void Rotation(float num);


private:
	Vector2d mPos;
	float mRotation;
	Vector2d mScale;

	bool mActive;
	GameEntity* mParent;
};