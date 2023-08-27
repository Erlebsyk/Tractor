/**
 * @file	sdl_hook_events.hpp
 * @brief	
 * 
 * @author	Erlend Elias Isachsen
 * @date	27.08.2023
 */

#ifndef SDL_HOOK_EVENTS_HPP_
#define SDL_HOOK_EVENTS_HPP_

// External libraries header includes
#include <SDL_events.h>

// Standard library header includes
#include <unordered_map>

// Project header includes
#include "event_types/event_base.hpp"

namespace trac
{
	void sdl_init_events();

	/// @brief	Tracks the number of listeners for each SDL event type, and enables/disables SDL event processing accordingly.
	class SdlListenerTracker
	{
	public:
		SdlListenerTracker();

		void AddListener(trac::EventType e_type);
		void AddListener(std::shared_ptr<trac::Event> e);

		void RemoveListener(trac::EventType e_type);
		void RemoveListener(std::shared_ptr<trac::Event> e);

	private:
		bool MapHasListener(SDL_EventType event_type);
		void MapInsertListener(SDL_EventType event_type);
		bool MapRemoveListener(SDL_EventType event_type);

		/// Map of SDL event types and the number of listeners registered to that event type.
		std::unordered_map<SDL_EventType, uint32_t> sdl_listener_counts_;
	};
} // namespace trac

#endif //SDL_HOOK_EVENTS_HPP_