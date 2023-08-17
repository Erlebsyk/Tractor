/**
 * @file	sdl_hook.cpp
 * @brief	Sources file for the SDL hook. See sdl_hook.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	16.08.2023
 * 
*/

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "sdl_hook.hpp"

// External libraries header includes
#include <SDL_events.h>

// Project header includes
#include "events/event_application.hpp"
#include "events/event_key.hpp"
#include "events/event_mouse.hpp"
#include "events/event_sdl.hpp"
#include "events/event.hpp"

namespace trac
{
	static int sdl_event_filter(void *data, SDL_Event *event);
	static int sdl_event_callback(void *data, SDL_Event *event);

	static void sdl_dispatch_window_event(SDL_Event* event);

	/// List of SDL events to ignore.
	static const SDL_EventType sdl_event_ignore_list[] = {
		SDL_FIRSTEVENT,
		SDL_POLLSENTINEL,
		SDL_LASTEVENT
	};
 
	/**
	 * @brief	Filter SDL events. This function is called before the event is dispatched, and will remove any events in the ignore list.
	 * 
	 * @param data	Pointer to user data.
	 * @param event	Pointer to the SDL event to filter.
	 * @return int	Whether or not to dispatch the event.
	 * @retval 0	Do not dispatch the event.
	 * @retval 1	Dispatch the event.
	 */
	int sdl_event_filter(void *data, SDL_Event *event)
	{
		for(auto type : sdl_event_ignore_list)
		{
			if(event->type == type)
				return 0;
		}
		return 1;
	}

	/**
	 * @brief	Callback function for SDL events. This function is called after the event filter.
	 * 
	 * @param data	Pointer to user data.
	 * @param event	Pointer to the SDL event to dispatch.
	 * @return int	Ignored for this usecase (though required by SDL). Returns 0 on success.
	 */
	int sdl_event_callback(void *data, SDL_Event *event)
	{
		// Check for window and input events
		if(event->type == SDL_WINDOWEVENT)
			sdl_dispatch_window_event(event);
		//else if(event->type == SDL_KEYDOWN)
		//	event_dispatch(std::make_shared<EventKeyPressed>(event->key.keysym.sym, event->key.repeat));
		//else if(event->type == SDL_KEYUP)
		//	event_dispatch(std::make_shared<EventKeyReleased>(event->key.keysym.sym));
		//else if(event->type == SDL_MOUSEBUTTONDOWN)
		//	event_dispatch(std::make_shared<EventMouseButtonPress>(event->button.button));
		//else if(event->type == SDL_MOUSEBUTTONUP)
		//	event_dispatch(std::make_shared<EventMouseButtonRelease>(event->button.button));
		else if(event->type == SDL_MOUSEMOTION)
			event_dispatch(std::make_shared<EventMouseMovement>((float)event->motion.x, (float)event->motion.y));
		else if(event->type == SDL_MOUSEWHEEL)
			event_dispatch(std::make_shared<EventMouseScrolled>((float)event->wheel.x, (float)event->wheel.y));

		// Dispatch the SDL event
		std::shared_ptr<EventSdl> sdl_event = std::make_shared<EventSdl>(event);
		event_dispatch(sdl_event);

		return 0;
	}

	/**
	 * @brief	Creates a tractor window event from an SDL window event.
	 * 
	 * @param event	The SDL window event.
	 */
	void sdl_dispatch_window_event(SDL_Event* event)
	{
		if(event->window.event == SDL_WINDOWEVENT_CLOSE)
			event_dispatch(std::make_shared<EventWindowClose>());
		else if(event->window.event == SDL_WINDOWEVENT_RESIZED)
			event_dispatch(std::make_shared<EventWindowResize>((uint32_t)event->window.data1, (uint32_t)event->window.data2));
		else if(event->window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
			event_dispatch(std::make_shared<EventWindowFocus>());
		else if(event->window.event == SDL_WINDOWEVENT_FOCUS_LOST)
			event_dispatch(std::make_shared<EventWindowLostFocus>());
		else if(event->window.event == SDL_WINDOWEVENT_MOVED)
			event_dispatch(std::make_shared<EventWindowMoved>((uint32_t)event->window.data1, (uint32_t)event->window.data2));
	}

	/// @brief	Links the SDL window events to the the event dispatcher.
	void sdl_link_events()
	{
		SDL_SetEventFilter(sdl_event_filter, nullptr);
		SDL_AddEventWatch(sdl_event_callback, nullptr);
	}

} // Namespace trac