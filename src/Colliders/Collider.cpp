#include "Collider.h"

Collider::Collider(ColliderType type)
	: mType(type)
{
	mDebugTXT = nullptr;
}

Collider::~Collider()
{
	if (mDebugTXT)
	{
		delete mDebugTXT;
		mDebugTXT = nullptr;
	}
}

void Collider::SetDebugTXT(Texture* txt)
{
	delete mDebugTXT;
	mDebugTXT = txt;
	mDebugTXT->SetParent(this);		//textura = child of collider -> pokud posuneme collider, posune se txt
}

Collider::ColliderType Collider::GetColType()
{
	return mType;
}

void Collider::Render()
{
	if (DEBUG_COLIDER)
		mDebugTXT->Render();
}