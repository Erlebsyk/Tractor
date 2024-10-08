/**
 * @file	events.cpp
 * @brief	Main source file for the event module. See events.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	27.08.2023
 */

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "events.hpp"

// Project includes
#include "sdl_hook_events.hpp"
#include "logger.hpp"

namespace trac
{

#ifndef SKIP_NULLPTR_CHECKS_EVENTS
/// @brief	Checks whether the provided event pointer is null or not, and shows file and line number if it is null.
# define CHECK_EVENT_NULLPTR(e) \
	if(e == nullptr) \
		throw std::runtime_error(\
			"Non-blocking event pointer is null. File: " + std::string(__FILE__) + ", Line: " + std::to_string(__LINE__) \
		);
#else
/// @brief	Event check macro that does nothing since SKIP_NULLPTR_CHECKS_EVENTS is defined.
# define CHECK_EVENT_NULLPTR(e)
#endif
	/**
	 * @brief	The ListenerDataB struct defines the data needed to register and unregister a blocking event listener.
	 */
	struct ListenerDataB
	{
		/// The type of event bound to the listener.
		const EventType type;
		/// The handle of the listener.
		const handle_b_t handle;
	};

	/**
	 * @brief	The ListenerDataNb struct defines the data needed to register and unregister a non-blocking event listener.
	 */
	struct ListenerDataNb
	{
		/// The type of event bound to the listener.
		const EventType type;
		/// The handle of the listener.
		const handle_nb_t handle;
	};

	/// A map of all registered blocking event listeners.
	std::map<listener_id_t, ListenerDataB> listeners_b;
	/// A map of all registered non-blocking event listeners.
	std::map<listener_id_t, ListenerDataNb> listeners_nb;
	/// A map of all registered blocking event listeners.
	static listener_id_t event_id_b = 0;
	/// A map of all registered non-blocking event listeners.
	static listener_id_t event_id_nb = 0;
	/// A tracker for SDL event listeners.
	static SdlListenerTracker listener_tracker;

	/// The global engine event dispatcher.
	std::shared_ptr<event_dispatcher_t> EventDispatcher::engine_dispatcher_s_ = nullptr;
	/// The global engine event queue.
	std::shared_ptr<event_queue_t> EventDispatcher::engine_queue_s_ = nullptr;
	
	/**
	 * @brief Adds a single listener to the tracker of all blocking event listeners.
	 * 
	 * @param type	The type of event to listen for.
	 * @param handle	The handle of the listener (lookup information and callback function).
	 * @return listener_id_t	The unique identifier of the event listener.
	 */
	listener_id_t add_listener_to_tracker_b(const EventType type, const handle_b_t &handle)
	{
		event_id_b++;
		listeners_b.emplace(event_id_b, ListenerDataB{type, handle});
		listener_tracker.AddListener(type);
		return event_id_b;
	}

	/**
	 * @brief Adds a single listener to the tracker of all non-blocking event listeners.
	 * 
	 * @param type	The type of event to listen for.
	 * @param handle	The handle of the listener (lookup information and callback function).
	 * @return listener_id_t	The unique identifier of the event listener.
	 */
	listener_id_t add_listener_to_tracker_nb(const EventType type, const handle_nb_t &handle)
	{
		event_id_nb++;
		listeners_nb.emplace(event_id_nb, ListenerDataNb{type, handle});
		listener_tracker.AddListener(type);
		return event_id_nb;
	}

	/// @brief	Processes all queued events submitted through the non-blocking event dispatcher (i.e event_dispatch or event_dispatch_nb).
	void event_queue_process()
	{
		SDL_PumpEvents();
		EventDispatcher::GetEngineQueue()->process();
	}

	/**
	 * @brief	Processes a single queued event submitted through the non-blocking event dispatcher (i.e event_dispatch or event_dispatch_nb).
	 * 
	 * @return bool Whether the event queue is empty or not after processing the event.
	 * @retval True	The event queue is empty after processing the event.
	 * @retval False	The event queue is not empty after processing the event.
	 */
	bool event_queue_process_one()
	{
		SDL_PumpEvents();
		EventDispatcher::GetEngineQueue()->processOne();
		return event_queue_empty();
	}

	/**
	 * @brief	Checks whether the event queue is empty or not.
	 * 
	 * @return bool	Whether the event queue is empty or not.
	 * @retval True	The event queue is empty.
	 * @retval False	The event queue is not empty.
	 */
	bool event_queue_empty()
	{
		return EventDispatcher::GetEngineQueue()->emptyQueue();
	}

	/// @brief	Clears all queued events from the event queue.
	void event_queue_clear()
	{
		EventDispatcher::GetEngineQueue()->clearEvents();
	}

	/**
	 * @brief	Dispatches the provided event to the event listeners. This will dispatch the event to both the blocking and non-blocking event dispatchers.
	 * 
	 * @param e	The event to dispatch.
	 */
	void event_dispatch(std::shared_ptr<Event> e)
	{
		CHECK_EVENT_NULLPTR(e);
		EventDispatcher::GetEngineDispatcher()->dispatch(e->GetType(), *e);
		EventDispatcher::GetEngineQueue()->enqueue(e->GetType(), e);
	}

	/**
	 * @brief	Dispaches a blocking event to the blocking dispatcher only.
	 * 
	 *	This should only be used where performance is critical, and where the event necessarily must be processed immediately. Otherwise, the generic
	 *	event_dispatch function should be used to ensure that the event is propagated to all blocking and non-blocking listeners.
	 * 
	 * @param e	The event to dispatch.
	 */
	void event_dispatch_b(Event& e)
	{
		EventDispatcher::GetEngineDispatcher()->dispatch(e.GetType(), e);
	}

	/**
	 * @brief	Dispatches a non-blocking event to the non-blocking dispatcher only. This function should only be used where immediate processing of the
	 * 			event could lead to unexpected behaviour. In the vast majority of cases, the generic event_dispatch function should be used instead.
	 * 
	 * @param e	The event to dispatch.
	 * 
	 * @throw std::runtime_error	Thrown if the provided event pointer is null.
	 */
	void event_dispatch_nb(std::shared_ptr<Event> e)
	{
		CHECK_EVENT_NULLPTR(e);
		EventDispatcher::GetEngineQueue()->enqueue(e->GetType(), e);
	}

	/**
	 * @brief	Adds a blocking event listener to the event dispatcher. This function adds a blocking event listener to the global engine event dispatcher.
	 * 			Use this for functions that must be processed immediately after an event is triggered. Specialization of the event_listener_add_b
	 * 			template function.
	 * 
	 * @param type	The type of event to listen for.
	 * @param cb_fn	The callback function to call when the event is dispatched.
	 * 
	 * @return	The unique identifier of the event listener.
	 */
	listener_id_t event_listener_add_b(EventType type, event_cb_b_fn cb_fn)
	{
		const handle_b_t handle = EventDispatcher::GetEngineDispatcher()->appendListener(type, cb_fn);
		const trac::listener_id_t id = add_listener_to_tracker_b(type, handle);
		return id;
	}
	
	/**
	 * @brief	Adds a non-blocking event listener to the event dispatcher. This function adds a non-blocking event listener to the global engine event dispatcher.
	 * 			Specialization of the event_listener_add_nb template function.
	 * 
	 * @param type	The type of event to listen for.
	 * @param cb_fn	The callback function to call when the event is triggered.
	 * @return listener_id_t	The unique identifier of the event listener.
	 */
	listener_id_t event_listener_add_nb(EventType type, event_cb_nb_fn cb_fn)
	{
		const handle_nb_t handle = EventDispatcher::GetEngineQueue()->appendListener(type, cb_fn);
		const trac::listener_id_t id = add_listener_to_tracker_nb(type, handle);
		return id;
	}

	/**
	 * @brief	Removes a blocking event listener from the blocking event dispatcher.
	 * 
	 * @param id	The id of the event listener to remove.
	 */
	void event_listener_remove_b(const listener_id_t id)
	{
		const auto it = listeners_b.find(id);
		if (it != listeners_b.end())
		{
			EventDispatcher::GetEngineDispatcher()->removeListener(it->second.type, it->second.handle);
			listener_tracker.RemoveListener(it->second.type);
			listeners_b.erase(it);
		}
		else
		{
			log_engine_warn("Failed to remove blocking event listener with id [%u]. No registered listener with that id exists.", id);
		}
	}

	/**
	 * @brief	Removes a non-blocking event listener from the non-blocking event dispatcher.
	 * 
	 * @param id	The id of the event listener to remove.
	 */
	void event_listener_remove_nb(const listener_id_t id)
	{
		const auto it = listeners_nb.find(id);
		if (it != listeners_nb.end())
		{
			EventDispatcher::GetEngineQueue()->removeListener(it->second.type, it->second.handle);
			listener_tracker.RemoveListener(it->second.type);
			listeners_nb.erase(it);
		}
		else
		{
			log_engine_warn("Failed to remove non-blocking event listener with id [%u]. No registered listener with that id exists.", id);
		}
	}

	
	/// @brief	Removes all blocking event listeners from the blocking event dispatcher.
	void event_listener_remove_all_b()
	{
		for (auto& listener : listeners_b)
		{
			EventDispatcher::GetEngineDispatcher()->removeListener(listener.second.type, listener.second.handle);
			listener_tracker.RemoveListener(listener.second.type);
		}
		listeners_b.clear();
	}

	/// @brief	Removes all non-blocking event listeners from the non-blocking event dispatcher.
	void event_listener_remove_all_nb()
	{
		for (auto& listener : listeners_nb)
		{
			EventDispatcher::GetEngineQueue()->removeListener(listener.second.type, listener.second.handle);
			listener_tracker.RemoveListener(listener.second.type);
		}
		listeners_nb.clear();
	}

	/// @brief	Removes all event listeners from both the blocking and non-blocking event dispatchers.
	void event_listener_remove_all()
	{
		event_listener_remove_all_b();
		event_listener_remove_all_nb();
	}

	/**
	 * @brief	Returns the event type for the for a given event reference.
	 * 
	 * @param e	The event to get the type for.
	 * @return EventType	The event type for the provided event.
	 */
	EventType EventPolicyB::GetEventType(const Event& e)
	{
		return e.GetType();
	}

	/**
	 * @brief	Get the event type for the provided event pointer.
	 * 
	 * @param e	The event to get the type for.
	 * @return EventType	The event type for the provided event.
	 */
	EventType EventPolicyNb::GetEventType(const std::shared_ptr<Event>& e)
	{
		CHECK_EVENT_NULLPTR(e);
		return e->GetType();
	}

	/// @brief	Initialize the event dispatcher. This function must be called before the event dispatcher can be used.
	void EventDispatcher::Initialize()
	{
		if(engine_dispatcher_s_ == nullptr)
			engine_dispatcher_s_ = std::make_shared<event_dispatcher_t>();
		else
			event_listener_remove_all_b();
		
		if(engine_queue_s_ == nullptr)
			engine_queue_s_ = std::make_shared<event_queue_t>();
		else
			event_listener_remove_all_nb();
	}

	/**
	 * @brief	Get the global engine event dispatcher. This function returns a reference to the global engine event dispatcher.
	 * 
	 * @return std::shared_ptr<event_dispatcher_t>& The global engine event dispatcher.
	 */
	std::shared_ptr<event_dispatcher_t>& EventDispatcher::GetEngineDispatcher()
	{
		return engine_dispatcher_s_;
	}

	/**
	 * @brief	Get the global engine event queue. This function returns a reference to the global engine event queue.
	 * 
	 * @return std::shared_ptr<event_queue_t>&	
	 */
	std::shared_ptr<event_queue_t>& EventDispatcher::GetEngineQueue()
	{
		return engine_queue_s_;
	}

} // namespace trac
