#include "../stdafx.h"
#include "Mouse.h"

void Mouse::OnLeftPressed(int _x, int _y)
{
	isLeftButtonDown = true;
	MouseEvent e(MouseEvent::EventType::LPress, _x, _y);
	eventBuffer.push(e);
}

void Mouse::OnLeftReleased(int _x, int _y)
{
	isLeftButtonDown = false;
	MouseEvent e(MouseEvent::EventType::LRelease, _x, _y);
	eventBuffer.push(e);
}

void Mouse::OnRightPressed(int _x, int _y)
{
	isRightButtonDown = true;
	MouseEvent e(MouseEvent::EventType::RPress, _x, _y);
	eventBuffer.push(e);
}

void Mouse::OnRightReleased(int _x, int _y)
{
	isRightButtonDown = false;
	MouseEvent e(MouseEvent::EventType::RRelease, _x, _y);
	eventBuffer.push(e);
}

void Mouse::OnMiddlePressed(int _x, int _y)
{
	isMiddleButtonDown = true;
	MouseEvent e(MouseEvent::EventType::MPress, _x, _y);
	eventBuffer.push(e);
}

void Mouse::OnMiddleReleased(int _x, int _y)
{
	isMiddleButtonDown = false;
	MouseEvent e(MouseEvent::EventType::MRelease, _x, _y);
	eventBuffer.push(e);
}

void Mouse::OnWheelUp(int _x, int _y)
{
	eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelUp, _x, _y));
}

void Mouse::OnWheelDown(int _x, int _y)
{
	eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelDown, _x, _y));
}

void Mouse::OnMouseMove(int _x, int _y)
{
	x = _x;
	y = _y;
	eventBuffer.push(MouseEvent(MouseEvent::EventType::Move, _x, _y));
}

void Mouse::OnMouseMoveRaw(int _x, int _y)
{
	eventBuffer.push(MouseEvent(MouseEvent::EventType::RAW_MOVE, _x, _y));
}

bool Mouse::IsLeftDown()
{
	return isLeftButtonDown;
}

bool Mouse::IsMiddelDown()
{
	return isMiddleButtonDown;
}

bool Mouse::IsRightDown()
{
	return isRightButtonDown;
}

int Mouse::GetPointX()
{
	return x;
}

int Mouse::GetPointY()
{
	return y;
}

MousePoint Mouse::GetPoint()
{
	return MousePoint{x, y};
}

bool Mouse::EventBufferIsEmpty()
{
	return eventBuffer.empty();
}

MouseEvent Mouse::ReadEvent()
{
	if (EventBufferIsEmpty())
	{
		return MouseEvent();
	}
	else
	{
		MouseEvent e = eventBuffer.front();
		eventBuffer.pop();
		return e;
	}
}