#pragma once
#include <SDL.h>
#include <string.h>
#include "../Helpers/MathHelper.h"
#include "../Helpers/Timer.h"


class InputManager
{
public:
	enum MOUSE_BUTTONS
	{
		left = 0,
		right
	};

	static InputManager* Instatnce();
	static void Release();

	//Keyboard
	bool KeyDown(SDL_Scancode scanCode);
	bool KeyPressed(SDL_Scancode scanCode);
	bool KeyReleased(SDL_Scancode scanCode);

	//Mouse
	bool MouseButtonDown(MOUSE_BUTTONS mouseButton);
	bool MouseButtonPressed(MOUSE_BUTTONS mouseButton);
	bool MouseButtonReleased(MOUSE_BUTTONS mouseButton);

	Vector2d GetMousePos();

	void Update();
	void UpdatePrevInput();

private:
	static InputManager* sInstance;

	//Keyboard
	Uint8* mPrevKeybordState;
	int mKeybordLenght;
	const Uint8* mKeybordState;

	//Mouse
	Uint32 mPrevMouseState;
	Uint32 mMouseState;
	int mMouseXpos;
	int mMouseYpos;

	InputManager();
	~InputManager();
};

