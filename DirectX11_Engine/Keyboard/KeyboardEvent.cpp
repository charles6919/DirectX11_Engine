#include "../stdafx.h"
#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent()
	: type(EventType::Invalid), key(0u)
{
}

KeyboardEvent::KeyboardEvent(const EventType _type, const unsigned char _key)
	: type(_type), key(_key)
{
}

bool KeyboardEvent::IsPress() const
{
	return type == EventType::Press;
}

bool KeyboardEvent::IsRelease() const
{
	return type == EventType::Release;
}

bool KeyboardEvent::IsValid() const
{
	return type != EventType::Invalid;
}

unsigned char KeyboardEvent::GetKeyCode() const
{
	return key;
}
