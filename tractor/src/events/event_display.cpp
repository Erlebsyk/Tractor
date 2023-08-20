/**
 * @file	event_display.cpp
 * @brief	Source file for display events. See event_display.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 */

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "events/event_display.hpp"

// External library includes
#include <SDL_video.h>
#include <SDL_timer.h>

namespace trac
{
	/**
	 * @brief	Constructs a new EventDisplay object.
	 * 
	 * @param display_index	The index of the display.
	 */
	EventDisplay::EventDisplay(const display_index_t display_index) :
		Event(),
		display_index_	{ display_index		},
		timestamp_ms_	{ SDL_GetTicks64()	}
	{}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventDisplay::GetCategoryFlags() const
	{
		return EventCategory::kDisplay;
	}
	
	/**
	 * @brief Get the timestamp of the event in milliseconds.
	 * 
	 * @return timestamp_t The timestamp of the event in milliseconds.
	 */
	timestamp_t EventDisplay::GetTimestampMs() const
	{
		return timestamp_ms_;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventDisplay::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": " << display_index_;
		return ss.str();
	}

	/**
	 * @brief	Get the index of the display.
	 * 
	 * @return display_index_t	The index of the display.
	 */
	display_index_t EventDisplay::GetDisplayIndex() const
	{
		return display_index_;
	}

	/**
	 * @brief	Constructs a new DisplayOrientation event.
	 * 
	 * @param display_index	The index of the display that changed orientation.
	 * @param orientation	The new orientation of the display.
	 */
	EventDisplayOrientation::EventDisplayOrientation(const display_index_t display_index, const DisplayOrientation orientation) :
		EventDisplay(display_index),
		orientation_ { orientation }
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventDisplayOrientation::GetName() const
	{
		return "EventDisplayOrientation";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventDisplayOrientation::GetType() const
	{
		return EventType::kDisplayOrientation;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventDisplayOrientation::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": " << GetDisplayIndex() << ", " << (uint32_t)orientation_;
		return ss.str();
	}

	/**
	 * @brief	Get the orientation of the display.
	 * 
	 * @return DisplayOrientation	The orientation of the display.
	 */
	DisplayOrientation EventDisplayOrientation::GetOrientationData() const
	{
		return orientation_;
	}

	/**
	 * @brief	Constructs a new DisplayConnected event.
	 * 
	 * @param display_index	The index of the display that was connected.
	 */
	EventDisplayConnected::EventDisplayConnected(const display_index_t display_index) :
		EventDisplay(display_index)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventDisplayConnected::GetName() const
	{
		return "EventDisplayConnected";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventDisplayConnected::GetType() const
	{
		return EventType::kDisplayConnected;
	}

	/**
	 * @brief	Get the category flags of the event.
	 * 
	 * @return event_category_t	The category flags of the event.
	 */
	event_category_t EventDisplayConnected::GetCategoryFlags() const
	{
		return EventCategory::kDisplay | EventCategory::kDevice;
	}
	
	/**
	 * @brief	Constructs a new DisplayDisconnected event.
	 * 
	 * @param display_index	The index of the display that was disconnected.
	 */
	EventDisplayDisconnected::EventDisplayDisconnected(const display_index_t display_index) :
		EventDisplay(display_index)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventDisplayDisconnected::GetName() const
	{
		return "EventDisplayDisconnected";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventDisplayDisconnected::GetType() const
	{
		return EventType::kDisplayDisconnected;
	}

	/**
	 * @brief	Get the category flags of the event.
	 * 
	 * @return event_category_t	The category flags of the event.
	 */
	event_category_t EventDisplayDisconnected::GetCategoryFlags() const
	{
		return EventCategory::kDisplay | EventCategory::kDevice;
	}

} // namespace trac