#pragma once

#include "Event.h"

class MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

	float GetXOffset() const { return m_XOffset; }
	float GetYOffset() const { return m_YOffset; }

	virtual const char* GetName() const override { return m_Name; }
	virtual EventType GetEventType() const override { return EventType::MouseScrolled; }

	static EventType GetStaticType() { return EventType::MouseScrolled; }


private:
	float m_XOffset;
	float m_YOffset;

	const char* m_Name = "MouseScrolledEvent";
};