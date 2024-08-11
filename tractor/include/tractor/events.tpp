/**
 * @file	events.tpp
 * @brief   Template implementation file for the events module. This file contains the template implementations for the events module, which is used to create
 *          and dispatch events to event listeners. Please see 'events.hpp' for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	11.08.2024
 */


#ifndef EVENTS_HPP_
#error "Do not include this file directly. Include events.hpp instead, through which this file is included."
#endif // EVENTS_HPP_

#ifndef EVENTS_TPP_
#define EVENTS_TPP_

namespace trac
{
	/**
	 * @brief	Adds a blocking event listener to the event dispatcher. This function adds a blocking event listener to the global engine event dispatcher that
	 * 			will be processed immediately. Use this for functions that need to be processed immediately. The function returns the id of the event listener.
	 * @details Example:
	 * 			trac::event_listener_add_b(trac::EventType::kQuit, BIND_THIS_EVENT_FN(App::OnWindowClose));
	 * 			where App::OnWindowClose is a member function of the App class of the native type: void OnWindowClose(trac::Event& e);
	 * 
	 * @tparam T	The type of the callback function. This is typically a lambda function, such as a wrapper around a member function of the native type
	 * 				'event_cb_b_fn' (see example that uses the BIND_THIS_EVENT_FN macro to create a wrapper).
	 * @param type	The type of event to listen for.
	 * @param arg	The callback function to call when the event is triggered.
	 * @return listener_id_t	The id of the event listener.
	 */
	template<typename T>
	listener_id_t event_listener_add_b(const EventType type, T&& arg)
	{
		const handle_b_t handle = EventDispatcher::GetEngineDispatcher()->appendListener(type, std::forward<T>(arg));
		const trac::listener_id_t id = add_listener_to_tracker_b(type, handle);
		return id;
	}

	/**
	 * @brief	Adds a non-blocking event listener to the event dispatcher. This function adds a non-blocking event listener to the global engine event
	 * 			dispatcher that will be processed in the next event queue processing step. Use this for functions that does not need to be processed
	 * 			immediately.
	 * @details Example:
	 * 			trac::event_listener_add_nb(trac::EventType::kQuit, BIND_THIS_EVENT_FN(App::OnWindowClose));
	 * 			where App::OnWindowClose is a member function of the App class of the native type: void OnWindowClose(trac::Event& e);
	 * 
	 * @tparam T	The type of the callback function. This is typically a lambda function, such as a wrapper around a member function
	 * 				of the native type 'event_cb_nb_fn' (see example that uses the BIND_THIS_EVENT_FN macro to create a wrapper).
	 * @param type	The type of event to listen for.
	 * @param callback	The callback function to call when the event is triggered.
	 * 
	 * @return listener_id_t	The id of the event listener.
	 */
	template<typename T>
	listener_id_t event_listener_add_nb(const EventType type, T&& callback)
	{
		const handle_nb_t handle = EventDispatcher::GetEngineQueue()->appendListener(type, std::forward<T>(callback));
		const trac::listener_id_t id = add_listener_to_tracker_nb(type, handle);
		return id;
	}
}

#endif /* EVENTS_TPP_ */