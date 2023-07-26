/**
 * @file	event.cpp
 * @brief	Main source file for the event module. See event.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	26.07.2023
 * 
*/

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "events/event.hpp"

// Standard library header includes
#include <cstdint>


namespace trac
{
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
	 */
	void event_add_listener_b(const EventType type, event_cb_b_fn callback)
	{
		EventDispatcher::GetEngineDispatcher()->appendListener(type, callback);
	}

	/**
	 * @brief	Adds a non-blocking event listener to the event dispatcher. This function adds a non-blocking event listener to the global engine event
	 * 			dispatcher that will be processed in the next event queue processing step. Use this for functions that does not need to be processed
	 * 			immediately.
	 * 
	 * @param type	The type of event to listen for.
	 * @param callback	The callback function to call when the event is triggered.
	 */
	void event_add_listener_nb(const EventType type, event_cb_nb_fn callback)
	{
		EventDispatcher::GetEngineQueue()->appendListener(type, callback);
	}

	/**
	 * @brief	Inserter operator for the Event class. This function is used to insert an event into an output stream (i.e. to print event data).
	 * 
	 * @param os	The output stream to insert the event into.
	 * @param e	The event to insert into the output stream.
	 * @return std::ostream&	The output stream with the event inserted.
	 */
	std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

	/**
	 * @brief	Converts the event to a string representation. This function is used to print the event data to the console.
	 * 
	 * @return std::string	The string representation of the event.
	 */
	std::string Event::ToString() const
	{
		return GetName();
	}

	/**
	 * @brief	Returns whether the event is in the provided category or not.
	 * 
	 * @param category	The category to check.
	 * @return bool	True if the event is in the provided category, false otherwise.
	 * @retval True	The event is in the provided category.
	 * @retval False	The event is not in the provided category.
	 */
	bool Event::IsInCategory(EventCategory category) const
	{
		return GetCategoryFlags() & category;
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
		engine_dispatcher_s_ = std::make_shared<event_dispatcher_t>();
		engine_queue_s_ = std::make_shared<event_queue_t>();
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
} // Namespace trac