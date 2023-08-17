/**
 * @file	event_sdl.hpp
 * @brief	
 * 
 * @author	Erlend Elias Isachsen
 * @date	16.08.2023
 * 
*/

#ifndef EVENT_SDL_HPP_
#define EVENT_SDL_HPP_


// External libraries header includes
#include <SDL_events.h>

// Project header includes
#include "event.hpp"

namespace trac
{
	/// @brief SDL event class.
	class EventSdl : public Event
	{
	public:
		// Constructors and destructors

		EventSdl(SDL_Event* sdl_event);
	
		//Public functions
	
		const char* GetName() const override;
		const EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;

		SDL_Event* GetSdlEvent() const;
		SDL_EventType GetSdlEventType() const;
	
	private:
		/// A pointer to the SDL event that triggered the event.
		SDL_Event* sdl_event_;
	
	};

} // Namespace trac


#endif // EVENT_SDL_HPP_ 