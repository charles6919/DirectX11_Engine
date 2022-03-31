#pragma once
struct MousePoint
{
	int x;
	int y;
};

class MouseEvent
{
public:
	enum EventType
	{
		LPress,
		LRelease,
		RPress,
		RRelease,
		MPress,
		MRelease,
		WheelUp,
		WheelDown,
		Move,
		RAW_MOVE,
		Invalid
	};

private:
	EventType type;
	int x;
	int y;
public:
	MouseEvent();
	MouseEvent(const EventType _type, const int _x, const int _y);
	bool IsValid() const;
	EventType GetType() const;
	MousePoint GetPoint() const;
	int GetPointX() const;
	int GetPointY() const;
};

