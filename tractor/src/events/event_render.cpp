/**
 * @file	event_render.cpp
 * @brief	Source file for render events. See event_render.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 */

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "events/event_render.hpp"

// External libraries header includes
#include <SDL_timer.h>

namespace trac
{
	/// @brief Construct a new EventRenderTargetsReset object.
	EventRenderTargetsReset::EventRenderTargetsReset() :
		Event(),
		timestamp_ms_ { SDL_GetTicks64() }
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventRenderTargetsReset::GetName() const
	{
		return "EventRenderTargetsReset";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventRenderTargetsReset::GetType() const
	{
		return EventType::kRenderTargetsReset;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventRenderTargetsReset::GetCategoryFlags() const
	{
		return EventCategory::kApplication;
	}
	
	/**
	 * @brief Get the timestamp of the event in milliseconds.
	 * 
	 * @return timestamp_t The timestamp of the event in milliseconds.
	 */
	timestamp_t EventRenderTargetsReset::GetTimestampMs() const
	{
		return timestamp_ms_;
	}
	
	/// @brief Construct a new EventRenderDeviceReset object.
	EventRenderDeviceReset::EventRenderDeviceReset() :
		Event(),
		timestamp_ms_ { SDL_GetTicks64() }
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventRenderDeviceReset::GetName() const
	{
		return "EventRenderDeviceReset";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventRenderDeviceReset::GetType() const
	{
		return EventType::kRenderDeviceReset;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventRenderDeviceReset::GetCategoryFlags() const
	{
		return EventCategory::kDevice;
	}
	
	/**
	 * @brief Get the timestamp of the event in milliseconds.
	 * 
	 * @return timestamp_t The timestamp of the event in milliseconds.
	 */
	timestamp_t EventRenderDeviceReset::GetTimestampMs() const
	{
		return timestamp_ms_;
	}

} // namespace trac