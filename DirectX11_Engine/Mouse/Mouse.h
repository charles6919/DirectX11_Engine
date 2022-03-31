#pragma once
#include "MouseEvent.h"
#include <queue>

class Mouse
{
public:
	void OnLeftPressed(int _x, int _y);
	void OnLeftReleased(int _x, int _y);
	void OnRightPressed(int _x, int _y);
	void OnRightReleased(int _x, int _y);
	void OnMiddlePressed(int _x, int _y);
	void OnMiddleReleased(int _x, int _y);
	void OnWheelUp(int _x, int _y);
	void OnWheelDown(int _x, int _y);
	void OnMouseMove(int _x, int _y);
	void OnMouseMoveRaw(int _x, int _y);

	bool IsLeftDown();
	bool IsMiddelDown();
	bool IsRightDown();

	int GetPointX();
	int GetPointY();
	MousePoint GetPoint();

	bool EventBufferIsEmpty();
	MouseEvent ReadEvent();

private:
	std::queue<MouseEvent> eventBuffer;
	bool isLeftButtonDown = false;
	bool isRightButtonDown = false;
	bool isMiddleButtonDown = false;
	int x = 0;
	int y = 0;
};

