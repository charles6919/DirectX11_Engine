#include "../stdafx.h"
#include "MouseEvent.h"

MouseEvent::MouseEvent()
    :type(EventType::Invalid), x(0), y(0)
{
}

MouseEvent::MouseEvent(const EventType _type, const int _x, const int _y)
    : type(_type), x(_x), y(_y)
{
}

bool MouseEvent::IsValid() const
{
    return type != EventType::Invalid;
}

MouseEvent::EventType MouseEvent::GetType() const
{
    return type;
}

MousePoint MouseEvent::GetPoint() const
{
    return MousePoint{ x, y };
}

int MouseEvent::GetPointX() const
{
    return x;
}

int MouseEvent::GetPointY() const
{
    return y;
}
