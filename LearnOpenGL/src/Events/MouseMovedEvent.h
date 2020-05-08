#pragma once

#include "Event.h"

class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(float xPos, float yPos) : m_XPos(xPos), m_YPos(yPos) {}

	float GetXPos() const { return m_XPos; }
	float GetYPos() const { return m_YPos; }

	virtual const char* GetName() const override { return m_Name; }
	virtual EventType GetEventType() const override { return EventType::MouseMoved; }

	static EventType GetStaticType() { return EventType::MouseMoved; }


private:
	float m_XPos;
	float m_YPos;

	const char* m_Name = "MouseMovedEvent";
};
