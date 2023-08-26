/**
 * @file	event_system.cpp
 * @brief	Source file for system events. See event_system.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 */

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "events/event_system.hpp"

// External libraries header includes
#include <SDL_timer.h>

namespace trac
{
	/// @brief Construct a new EventSystem event.
	EventSystem::EventSystem() :
		Event(),
		timestamp_ms_ { SDL_GetTicks64() }
	{}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventSystem::GetCategoryFlags() const
	{
		return EventCategory::kApplication;
	}
	
	/**
	 * @brief Get the timestamp of the event in milliseconds.
	 * 
	 * @return timestamp_t The timestamp of the event in milliseconds.
	 */
	timestamp_t EventSystem::GetTimestampMs() const
	{
		return timestamp_ms_;
	}
	
	/// @brief Construct a new EventQuit event.
	EventQuit::EventQuit() :
		EventSystem()
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventQuit::GetName() const
	{
		return "EventQuit";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventQuit::GetType() const
	{
		return EventType::kQuit;
	}
	
	/// @brief Construct a new EventLocaleChanged event.
	EventLocaleChanged::EventLocaleChanged() :
		EventSystem()
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventLocaleChanged::GetName() const
	{
		return "EventLocaleChanged";
	}
	
	/// @brief Construct a new EventLocaleChanged event.
	EventClipboardUpdate::EventClipboardUpdate() :
		EventSystem()
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventClipboardUpdate::GetName() const
	{
		return "EventClipboardUpdate";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventClipboardUpdate::GetType() const
	{
		return EventType::kClipboardUpdate;
	}

	/**
	 * @brief	Construct a new EventDrop event.
	 * 
	 * @param drop	The drop event data. Is either file name or drop text.
	 * @param window_id	The ID of the window that the data was dropped on.
	 */
	EventDrop::EventDrop(const std::string drop, const window_id_t window_id) :
		EventSystem(),
		drop_		{ drop		},
		window_id_	{ window_id	}
	{}
	
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventDrop::GetCategoryFlags() const
	{
		return EventCategory::kApplication | EventCategory::kInput;
	}
	
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventDrop::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [(" << GetDrop() << "), " << GetWindowId() << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the dropped data. Is either file name or drop text.
	 * 
	 * @return std::string	The dropped data.
	 */
	std::string EventDrop::GetDrop() const
	{
		return drop_;
	}

	/**
	 * @brief	Get the ID of the window that received the drop event.
	 * 
	 * @return window_id_t	The ID of the window that received the drop event.
	 */
	window_id_t EventDrop::GetWindowId() const
	{
		return window_id_;
	}

	/**
	 * @brief	Construct a new EventDropText event.
	 * 
	 * @param file_name	The name of the file that was dropped.
	 * @param window_id	The ID of the window that received the drop event.
	 */
	EventDropFile::EventDropFile(const std::string file_name, const window_id_t window_id) :
		EventDrop(file_name, window_id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventDropFile::GetName() const
	{
		return "EventDropFile";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventDropFile::GetType() const
	{
		return EventType::kDropFile;
	}
	
	/**
	 * @brief	Construct a new EventDropText event.
	 * 
	 * @param text	The text that was dropped.
	 * @param window_id	The ID of the window that received the drop event.
	 */
	EventDropText::EventDropText(const std::string text, const window_id_t window_id) :
		EventDrop(text, window_id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventDropText::GetName() const
	{
		return "EventDropText";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventDropText::GetType() const
	{
		return EventType::kDropText;
	}

	/**
	 * @brief	Construct a new EventDropComplete event.
	 * 
	 * @param window_id	The ID of the window that received the drop event.
	 */
	EventDropBegin::EventDropBegin(const window_id_t window_id) :
		EventDrop("", window_id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventDropBegin::GetName() const
	{
		return "EventDropBegin";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventDropBegin::GetType() const
	{
		return EventType::kDropBegin;
	}
	
	/**
	 * @brief	Construct a new EventDropComplete event.
	 * 
	 * @param window_id	The ID of the window that received the drop event.
	 */
	EventDropComplete::EventDropComplete(const window_id_t window_id) :
		EventDrop("", window_id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventDropComplete::GetName() const
	{
		return "EventDropComplete";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventDropComplete::GetType() const
	{
		return EventType::kDropComplete;
	}
} // namespace trac