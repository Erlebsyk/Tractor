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
#include "logger.hpp"

namespace trac
{
	/// Defines the type for blocking event handle, used for registering and unregistering blocking event listeners.
	typedef eventpp::internal_::EventDispatcherBase<trac::EventType, trac::event_cb_b_fn, trac::EventPolicyB, void>::Handle handle_b_t;
	/// Defines the type for non-blocking event handle, used for registering and unregistering non-blocking event listeners.
	typedef eventpp::internal_::EventQueueBase<trac::EventType, trac::event_cb_nb_fn, trac::EventPolicyNb>::Handle handle_nb_t;

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

	/// The global engine event dispatcher.
	std::shared_ptr<event_dispatcher_t> EventDispatcher::engine_dispatcher_s_ = nullptr;
	/// The global engine event queue.
	std::shared_ptr<event_queue_t> EventDispatcher::engine_queue_s_ = nullptr;
	
	/// @brief	Processes all queued events submitted through the non-blocking event dispatcher (i.e event_dispatch or event_dispatch_nb).
	void event_queue_process()
	{
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
	 */
	void event_dispatch_nb(std::shared_ptr<Event> e)
	{
		EventDispatcher::GetEngineQueue()->enqueue(e->GetType(), e);
	}

	/**
	 * @brief	Adds a blocking event listener to the event dispatcher. This function adds a blocking event listener to the global engine event dispatcher.
	 * 			Use this for functions that must be processed immediately after an event is triggered.
	 * 
	 * @param type	The type of event to listen for.
	 * @param callback	The callback function to call when the event is triggered.
	 * 
	 * @return	The id of the event listener.
	 */
	listener_id_t event_listener_add_b(const EventType type, event_cb_b_fn callback)
	{
		const handle_b_t handle = EventDispatcher::GetEngineDispatcher()->appendListener(type, callback);
		event_id_b++;
		listeners_b.emplace(event_id_b, ListenerDataB{type, handle});
		return event_id_b;
	}

	/**
	 * @brief	Adds a non-blocking event listener to the event dispatcher. This function adds a non-blocking event listener to the global engine event
	 * 			dispatcher that will be processed in the next event queue processing step. Use this for functions that does not need to be processed
	 * 			immediately.
	 * 
	 * @param type	The type of event to listen for.
	 * @param callback	The callback function to call when the event is triggered.
	 * 
	 * @return	The id of the event listener.
	 */
	listener_id_t event_listener_add_nb(const EventType type, event_cb_nb_fn callback)
	{
		const handle_nb_t handle = EventDispatcher::GetEngineQueue()->appendListener(type, callback);
		event_id_nb++;
		listeners_nb.emplace(event_id_nb, ListenerDataNb{type, handle});
		return event_id_nb;
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
		}
		listeners_b.clear();
	}

	/// @brief	Removes all non-blocking event listeners from the non-blocking event dispatcher.
	void event_listener_remove_all_nb()
	{
		for (auto& listener : listeners_nb)
		{
			EventDispatcher::GetEngineQueue()->removeListener(listener.second.type, listener.second.handle);
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
