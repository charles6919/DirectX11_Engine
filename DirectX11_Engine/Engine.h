#pragma once
#include "WindowContainer.h"
class Engine : WindowContainer
{
public:
	bool Initialize(HINSTANCE _hInstance, string _windowTitle, string _windowClass, int _width, int _height);
	bool ProcessMessages();
	void Update();
	void Render();
};

