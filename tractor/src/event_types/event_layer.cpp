/**
 * @file event_layer.cpp
 * @brief Source file for the layer event types module, see event_layer.hpp for more information.
 * 
 * @author Erlend Elias Isachsen
 */

/** Tractor PCH */
#include "tractor_pch.hpp"

/** Includes	*/
#include "event_types/event_layer.hpp"

#include <SDL_timer.h>

/** Definitions	*/

namespace trac
{
	/// @brief  Construct a new EventLayer event.
	EventLayer::EventLayer() : 
		Event(),
		timestamp_ms_	{ SDL_GetTicks64() }
	{}

	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t	The category flags of the event.
	 */
	event_category_t EventLayer::GetCategoryFlags() const
	{
		return EventCategory::kApplication;
	}

	/**
	 * @brief Get the timestamp of the event in milliseconds.
	 * 
	 * @return timestamp_t	The timestamp of the event in milliseconds.
	 */
	timestamp_t EventLayer::GetTimestampMs() const
	{
		return timestamp_ms_;
	}

	/**
	 * @brief Get a string representation of the event.
	 * 
	 * @return std::string	A string representation of the event.
	 */
	std::string EventLayer::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << timestamp_ms_ << " ms]";
		return ss.str();
	}

	/// @brief Construct a new EventLayerPushed event.
	EventLayerPushed::EventLayerPushed() : 
		EventLayer()
	{}

	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventLayerPushed::GetName() const
	{
		return "EventLayerPushed";
	}

	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventLayerPushed::GetType() const
	{
		return EventType::kLayerPushed;
	}

	/// @brief Construct a new EventLayerPopped event.
	EventLayerPopped::EventLayerPopped() : 
		EventLayer()
	{}

	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventLayerPopped::GetName() const
	{
		return "EventLayerPopped";
	}

	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventLayerPopped::GetType() const
	{
		return EventType::kLayerPopped;
	}

	/// @brief Construct a new EventLayerUpdated event.
	EventLayerUpdated::EventLayerUpdated() : 
		EventLayer()
	{}

	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char*	The name of the event.
	 */
	const char* EventLayerUpdated::GetName() const
	{
		return "EventLayerUpdated";
	}

	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType	The type of the event.
	 */
	EventType EventLayerUpdated::GetType() const
	{
		return EventType::kLayerUpdated;
	}

	/// @brief Construct a new EventLayerAttached event.
	EventLayerAttached::EventLayerAttached() : 
		EventLayer()
	{}

	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char*	The name of the event.
	 */
	const char* EventLayerAttached::GetName() const
	{
		return "EventLayerAttached";
	}

	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType	The type of the event.
	 */
	EventType EventLayerAttached::GetType() const
	{
		return EventType::kLayerAttached;
	}

	/// @brief Construct a new EventLayerDetached event.
	EventLayerDetached::EventLayerDetached() : 
		EventLayer()
	{}

	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char*	The name of the event.
	 */
	const char* EventLayerDetached::GetName() const
	{
		return "EventLayerDetached";
	}

	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType	The type of the event.
	 */
	EventType EventLayerDetached::GetType() const
	{
		return EventType::kLayerDetached;
	}


} // Namespace trac