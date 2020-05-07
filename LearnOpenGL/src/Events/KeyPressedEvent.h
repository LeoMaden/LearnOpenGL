#pragma once
#include "Event.h"

class KeyPressedEvent : public Event
{
public:
	KeyPressedEvent(int32_t keyCode) : m_KeyCode(keyCode) {}

	virtual const char* GetName() const override { return m_Name; }
	virtual EventType GetEventType() const override { return EventType::KeyPressed; }

	static EventType GetStaticType() { return EventType::KeyPressed; }

private:
	int32_t m_KeyCode;
	const char* m_Name = "KeyPressedEvent";
};