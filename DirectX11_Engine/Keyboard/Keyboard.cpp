#include "../stdafx.h"
#include "Keyboard.h"

Keyboard::Keyboard()
{
	for (int i = 0; i < 256; i++)
	{
		keyStates[i] = false;
	}
}

bool Keyboard::KeyIsPressed(const unsigned char _keycode)
{
	return keyStates[_keycode];
}

bool Keyboard::KeyBufferIsEmpty()
{
	return keyBuffer.empty();
}

bool Keyboard::CharBufferIsEmpty()
{
	return charBuffer.empty();
}

KeyboardEvent Keyboard::ReadKey()
{
	if (keyBuffer.empty())
	{
		return KeyboardEvent();
	}
	else
	{
		KeyboardEvent e = keyBuffer.front();
		keyBuffer.pop();
		return e;
	}
}

unsigned char Keyboard::ReadChar()
{
	if (charBuffer.empty())
	{
		return 0u;
	}
	else
	{
		unsigned char e = charBuffer.front();
		charBuffer.pop();
		return e;
	}
}

void Keyboard::OnKeyPressed(const unsigned char _key)
{
	keyStates[_key] = true;
	keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, _key));
}

void Keyboard::OnKeyReleased(const unsigned char _key)
{
	keyStates[_key] = false;
	keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, _key));
}

void Keyboard::OnChar(const unsigned char _key)
{
	charBuffer.push(_key);
}

void Keyboard::EnableAutoRepeatKeys()
{
	autoRepeatKeys = true;
}

void Keyboard::DisableAutoRepeatKeys()
{
	autoRepeatKeys = false;
}

void Keyboard::EnableAutoRepeatChars()
{
	autoRepeatChars = true;
}

void Keyboard::DisableAutoRepeatChars()
{
	autoRepeatChars = false;
}

bool Keyboard::IsKeyAutoRepeat()
{
	return autoRepeatKeys;
}

bool Keyboard::IsCharsAutoRepeat()
{
	return autoRepeatChars;
}
