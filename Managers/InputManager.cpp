#include "InputManager.h"


InputManager* InputManager::sInstance = nullptr;
InputManager* InputManager::Instatnce()
{
	if (sInstance == nullptr)
		sInstance = new InputManager();

	return sInstance;
}

void InputManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

InputManager::InputManager()
{
	mKeybordState = SDL_GetKeyboardState(&mKeybordLenght);
	mPrevKeybordState = new Uint8[mKeybordLenght];
	memcpy(mPrevKeybordState, mKeybordState, mKeybordLenght);
}

InputManager::~InputManager()
{
	delete[] mPrevKeybordState;
	mPrevKeybordState = nullptr;
}

// KEYBOARD
bool InputManager::KeyDown(SDL_Scancode scanCode)
{
	return mKeybordState[scanCode];
}

bool InputManager::KeyPressed(SDL_Scancode scanCode)
{
	return !mPrevKeybordState[scanCode] && mKeybordState[scanCode];
}

bool InputManager::KeyReleased(SDL_Scancode scanCode)
{
	return mPrevKeybordState[scanCode] && !mKeybordState[scanCode];
}

////////////////////////////////////////////////////////////////////

// MOUSE

Vector2d InputManager::GetMousePos()
{
	return Vector2d((float)mMouseXpos, (float)mMouseYpos);
}
bool InputManager::MouseButtonDown(MOUSE_BUTTONS mouseButton)
{
	Uint32 mask = 0;
	switch (mouseButton)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;

	case right:
		mask = SDL_BUTTON_RMASK;
		break;
	}

	return (mMouseState & mask);
}

bool InputManager::MouseButtonPressed(MOUSE_BUTTONS mouseButton)
{
	Uint32 mask = 0;
	switch (mouseButton)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;

	case right:
		mask = SDL_BUTTON_RMASK;
		break;
	}

	return !(mPrevMouseState & mask) && (mMouseState & mask);
}

bool InputManager::MouseButtonReleased(MOUSE_BUTTONS mouseButton)
{
	Uint32 mask = 0;
	switch (mouseButton)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;

	case right:
		mask = SDL_BUTTON_RMASK;
		break;
	}

	return (mPrevMouseState & mask) && !(mMouseState & mask);
}

////////////////////////////////////////////////////////////////////

void InputManager::Update()
{
	mMouseState = SDL_GetMouseState(&mMouseXpos, &mMouseYpos);
}

void InputManager::UpdatePrevInput()
{
	memcpy(mPrevKeybordState, mKeybordState, mKeybordLenght);
	mPrevMouseState = mMouseState;
}