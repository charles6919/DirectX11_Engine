#include "stdafx.h"
#include "Engine.h"

bool Engine::Initialize(HINSTANCE _hInstance, string _windowTitle, string _windowClass, int _width, int _height)
{
	if (renderWindow.Initialize(this, _hInstance, _windowTitle, _windowClass, _width, _height) == false)
	{
		return false;
	}

	if (gfx.Initialize(renderWindow.GetHWND(), _width, _height) == false)
	{
		return false;
	}

	return true;
}

bool Engine::ProcessMessages()
{
	return renderWindow.ProcessMessages();
}

void Engine::Update()
{
	while (!keyboard.CharBufferIsEmpty())
	{
		unsigned char ch = keyboard.ReadChar();
		string outMsg = "Char: ";
		outMsg += ch;
		outMsg += "\n";
		OutputDebugStringA(outMsg.c_str());
	}

	while (!keyboard.KeyBufferIsEmpty())
	{
		KeyboardEvent kbe = keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
		string outMsg = "";
		if (kbe.IsPress())
		{
			outMsg += "Key Press: ";
		}
		else
		{
			outMsg += "Key Release: ";
		}
		outMsg += keycode;
		outMsg += "\n";
		OutputDebugStringA(outMsg.c_str());
	}

	while (!mouse.EventBufferIsEmpty())
	{
		MouseEvent me = mouse.ReadEvent();
		switch(me.GetType())
		{
			case MouseEvent::EventType::Move:
			{
				string outMsg = "X: ";
				outMsg += to_string(me.GetPointX());
				outMsg += ", Y: ";
				outMsg += to_string(me.GetPointY());
				outMsg += "\n";
				OutputDebugStringA(outMsg.c_str());
				break;
			}

			case  MouseEvent::EventType::WheelUp:
			{
				string outMsg = "WheelUp\n";
				OutputDebugStringA(outMsg.c_str());
				break;
			}

			case  MouseEvent::EventType::WheelDown:
			{
				string outMsg = "WheelDown\n";
				OutputDebugStringA(outMsg.c_str());
				break;
			}

			case MouseEvent::EventType::RAW_MOVE:
				string outMsg = "Raw X: ";
				outMsg += to_string(me.GetPointX());
				outMsg += ", Raw Y: ";
				outMsg += to_string(me.GetPointY());
				outMsg += "\n";
				OutputDebugStringA(outMsg.c_str());
		}
	}
}

void Engine::Render()
{
	gfx.Render();
}
