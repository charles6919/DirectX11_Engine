#pragma once
#include "RenderWindow.h"
#include "Keyboard/Keyboard.h"
#include "Mouse/Mouse.h"
#include "Graphics/Graphics.h"

class WindowContainer
{
public:
	WindowContainer();
	LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	RenderWindow renderWindow;
	Keyboard keyboard;
	Mouse mouse;
	Graphics gfx;

private:

};

