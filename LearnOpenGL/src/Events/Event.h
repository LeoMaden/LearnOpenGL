#pragma once
 
#include <string>

enum class EventType
{
	None = 0,
	KeyPressed, KeyReleased,
	MouseMoved, MouseButtonPressed, MouseScrolled
};

class Event
{
public:
	bool Handled = false;
	virtual const char* GetName() const = 0;
	virtual EventType GetEventType() const = 0;
};

class EventDispatcher
{
	//template<typename EventT>
	//using EventHandler = void (*x)(EventT&);

public:
	EventDispatcher(Event& e)
		: m_Event(e)
	{
	}

	template<typename EventT, typename FuncT>
	bool Dispatch(const FuncT& handler)
	{
		if (m_Event.GetEventType() == EventT::GetStaticType())
		{
			m_Event.Handled = handler(static_cast<EventT&>(m_Event));
			return true;
		}

		return false;
	}

private:
	Event& m_Event;
};
