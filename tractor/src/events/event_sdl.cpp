/**
 * @file	event_sdl.cpp
 * @brief	
 * 
 * @author	Erlend Elias Isachsen
 * @date	16.08.2023
 * 
*/

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "events/event_sdl.hpp"

// Standard library header includes
#include <sstream>

namespace trac
{
	/**
	 * @brief	Construct an SDL event.
	 * 
	 * @param sdl_event	A pointer to the SDL event that triggered the event.
	 */
	EventSdl::EventSdl(SDL_Event* sdl_event) : 
		Event(),
		sdl_event_{ sdl_event }
	{}

	/**
	 * @brief	Get the name of the event.
	 * 
	 * @return const char*	The name of the event.
	 */
	const char* EventSdl::GetName() const
	{
		return "EventSdl";
	}

	/**
	 * @brief	Get the type of the event.
	 * 
	 * @return const EventType	The type of the event.
	 */
	const EventType EventSdl::GetType() const
	{
		return EventType::kSdl;
	}

	/**
	 * @brief	Get the category flags of the event.
	 * 
	 * @return event_category_t	The category flags of the event.
	 */
	event_category_t EventSdl::GetCategoryFlags() const
	{
		return (EventCategory::kSdl);
	}

	/**
	 * @brief	Create a string representation of the event containing the SDL event type.
	 * 
	 * @return std::string	A string representation of the event.
	 */
	std::string EventSdl::ToString() const
	{
		std::stringstream ss;
		ss << "EventSdl: " << sdl_event_->type;
		return ss.str();
	}

	/**
	 * @brief	Get the SDL event that triggered the event.
	 * 
	 * @return SDL_Event*	A pointer to the SDL event that triggered the event.
	 */
	SDL_Event* EventSdl::GetSdlEvent() const
	{
		return sdl_event_;
	}

	/**
	 * @brief	Get the SDL event type.
	 * 
	 * @return SDL_EventType	The SDL event type.
	 */
	SDL_EventType EventSdl::GetSdlEventType() const
	{
		return (SDL_EventType)(sdl_event_->type);
	}

} // Namespace trac