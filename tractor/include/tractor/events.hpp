/**
 * @file	events.hpp
 * @brief	Main header file for the event module. The event module defines the event system used by the tractor game engine library, including how events are
 * 			dispatched and how event listeners are set up. Including this header file will also include all event types and event categories, and is meant to be
 * 			a single include file for all event related functionality.
 * 
 *	Events and event types are introduced in this library, but the external library 'eventpp' is used to set up the event system. The eventpp library provides
 *	all the mechanisms needed to set up the event system, such as event listeners, dispatchment, etc. The event module defines multiple event types and event
 *	categories, where each event type has a corresponding event class that contains the relevant event data. The eventpp library is used to handle event
 *	dispatchment and event listeners, and the eventpp library is set up to use the event types defined in this library such that event listeneres can listen to
 *	the defined event types.
 * 
 * @author	Erlend Elias Isachsen
 * @date	27.08.2023
 */

#ifndef EVENTS_HPP_
#define EVENTS_HPP_

// Standard library header includes
#include <functional>
#include <memory>

// External libraries header includes
#include "eventpp/eventdispatcher.h"
#include "eventpp/eventqueue.h"

// Base header file for all events
#include "event_types/event_base.hpp"

// Event type header files
#include "event_types/event_application.hpp"
#include "event_types/event_audio.hpp"
#include "event_types/event_controller.hpp"
#include "event_types/event_display.hpp"
#include "event_types/event_gesture.hpp"
#include "event_types/event_joystick.hpp"
#include "event_types/event_keyboard.hpp"
#include "event_types/event_layer.hpp"
#include "event_types/event_mouse.hpp"
#include "event_types/event_render.hpp"
#include "event_types/event_system.hpp"
#include "event_types/event_touch.hpp"
#include "event_types/event_window.hpp"

namespace trac
{
	/**
	 * @brief	Macro for creating a wrapper function around a member function inside current class (this). Intended to be used
	 * 			with the event_listener_add_b and event_listener_add_nb to enable processing of member functions as event
	 * 			callbacks, where the member functions are of the native type 'event_cb_b_fn' or 'event_cb_nb_fn'.
	 * 
	 * @param x	The member function to create a wrapper for.
	 */
	#define BIND_THIS_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	/**
	 * @brief	Macro for creating a wrapper function around a member function inside an object. Intended to be used with the
	 * 			event_listener_add_b and event_listener_add_nb to enable processing of member functions as event callbacks, where
	 * 			the member functions are of the native type 'event_cb_b_fn' or 'event_cb_nb_fn'.
	 * 
	 * @param x	The member function to create a wrapper for.
	 * @param obj	The object containing the member function.
	 */
	#define BIND_EVENT_FN(x, obj) std::bind(&x, &obj, std::placeholders::_1)

	struct EventPolicyB;
	struct EventPolicyNb;
	class EventDispatcher;

	/// Defines the type for the event category bitfield.
	typedef uint32_t event_category_t;

	/// Defines the type for the blocking event dispatcher function. The blocking dispatcher can forward the event as a reference where performance is critical.
	typedef void (event_cb_b_fn)(Event& e);
	/// Defines the type for the non-blocking event dispatcher function. The non-blocking dispatcher must forward the event as a shared pointer.
	typedef void (event_cb_nb_fn)(std::shared_ptr<Event> e);
	/// Defines the type for the event dispatcher.
	typedef eventpp::EventDispatcher<EventType, event_cb_b_fn, EventPolicyB> event_dispatcher_t;
	/// Defines the type for the event queue.
	typedef eventpp::EventQueue<EventType, event_cb_nb_fn, EventPolicyNb> event_queue_t;
	/// Defines the listener id type.
	typedef uint64_t listener_id_t;

	/// Defines the type for blocking event handle, used for registering and unregistering blocking event listeners.
	typedef eventpp::internal_::EventDispatcherBase<trac::EventType, trac::event_cb_b_fn, trac::EventPolicyB, void>::Handle handle_b_t;
	/// Defines the type for non-blocking event handle, used for registering and unregistering non-blocking event listeners.
	typedef eventpp::internal_::EventQueueBase<trac::EventType, trac::event_cb_nb_fn, trac::EventPolicyNb>::Handle handle_nb_t;

	/// Documented in events.tpp
	template<typename T> listener_id_t event_listener_add_b(const EventType type, T&& arg);
	/// Documented in events.tpp
	template<typename T> listener_id_t event_listener_add_nb(const EventType type, T&& callback);

	listener_id_t add_listener_to_tracker_b(const EventType type, const handle_b_t &handle);
	listener_id_t add_listener_to_tracker_nb(const EventType type, const handle_nb_t &handle);

	void event_queue_process();
	bool event_queue_process_one();
	bool event_queue_empty();
	void event_queue_clear();

	void event_dispatch(std::shared_ptr<Event> e);
	void event_dispatch_b(Event& e);
	void event_dispatch_nb(std::shared_ptr<Event> e);

	listener_id_t event_listener_add_b(EventType type, event_cb_b_fn cb_fn);
	listener_id_t event_listener_add_nb(EventType type, event_cb_nb_fn cb_fn);

	void event_listener_remove_b(listener_id_t id);
	void event_listener_remove_nb(listener_id_t id);
	void event_listener_remove_all_b();
	void event_listener_remove_all_nb();
	void event_listener_remove_all();

	/**
	 * @brief	Defines a policy for the blocking event dispatcher. This policy is used to get the event type from the event, allowing events to be dispatched
	 * 			directly without having to explicitly specify the event type.
	 */
	struct EventPolicyB
	{
		static EventType GetEventType(const Event& e);
	};
	
	/**
	 * @brief	Defines a policy for the non-blocking event dispatcher. This policy is used to get the event type from the event, allowing events to be
	 * 			dispatched directly without having to explicitly specify the event type.
	 */
	struct EventPolicyNb
	{
		static EventType GetEventType(const std::shared_ptr<Event>& e);
	};

	/// @brief	The EventDispatcher class is used to dispatch events to the event listeners.
	class EventDispatcher
	{
	public:
		static void Initialize();
		static std::shared_ptr<event_dispatcher_t>& GetEngineDispatcher();
		static std::shared_ptr<event_queue_t>& GetEngineQueue();

	private:
		static std::shared_ptr<event_dispatcher_t> engine_dispatcher_s_;
		static std::shared_ptr<event_queue_t> engine_queue_s_;
	};

} // Namespace trac

// Include the inline implementations of the logger module.
#include "events.tpp"

#endif // EVENTS_HPP_ 
