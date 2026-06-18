#include <functional>
#include <map>
#include <vector>
#pragma once

enum class EventType
{
	MouseClick,
	KeyPress,
	WindowResize,
	OPEN_SCENE,
	CLOSE_SCENE,
	// Add more event types as needed
};
using EventCallback = std::function<void()>;
class EventHandler
{
public:
	void subscribe(EventType eventType, EventCallback callback)
	{
		eventCallbacks[eventType].push_back(callback);
	}
	void HandleEvent(EventType eventType)
	{
		if (eventCallbacks.find(eventType) != eventCallbacks.end())
		{
			for (const auto& callback : eventCallbacks[eventType])
			{
				callback();
			}
		}
	}
	static EventHandler& GetInstance()
	{
		static EventHandler instance;
		return instance;
	}
private:
	EventHandler() = default;
	std::map<EventType, std::vector<EventCallback>> eventCallbacks;
};

