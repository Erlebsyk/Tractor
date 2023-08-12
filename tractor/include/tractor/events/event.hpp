/**
 * @file	event.hpp
 * @brief	Main header file for the tractor event system. The event system is used to handle events in the tractor game engine library, such as keyboard
 * 			events, mouse events, window events, etc. This file defines the main events and event categories, and introduces the event base class.
 * 
 * 	Events and event types are introduced in this library, but the external library 'eventpp' is used to set up the event system. The eventpp library provides
 * 	all the mechanisms needed to set up the event system, such as event listeners, dispatchment, etc.
 * 
 * @author	Erlend Elias Isachsen
 * @date	23.07.2023
 * 
 * @todo	Implement tests for the event system.
 * 
*/

#ifndef EVENT_HPP_
#define EVENT_HPP_

// External libraries header includes
#include "eventpp/eventdispatcher.h"
#include "eventpp/eventqueue.h"
namespace trac
{
	class Event;
	struct EventPolicyB;
	struct EventPolicyNb;
	class EventDispatcher;

	/// @brief	The EventType enum defines the different types of events that can be handled by the tractor game engine library.
	enum class EventType
	{
		kNone = 0,
		kWindowClose, kWindowResize, kWindowFocus, kWindowLostFocus, kWindowMoved,
		kAppTick, kAppUpdate, kAppRender,
		kKeyPressed, kKeyReleased, kKeyTyped,
		kMouseButtonPressed, kMouseButtonReleased, kMouseMoved, kMouseScrolled,
		kEngineEventCount
	};

	/**
	 * @brief	The EventCategory enum defines the different categories of events that can be handled by the tractor game engine library. Multiple categories
	 * 			can be used for a single event, hence the use of bit flags.
	 */
	enum EventCategory
	{
		kNone			= 0,
		kApplication	= (1 << 0),
		kInput			= (1 << 1),
		kKeyboard		= (1 << 2),
		kMouse			= (1 << 3),
		kMouseButton	= (1 << 4),
		kEngineFinal	= (1 << 5) // This is the last category in the engine. All categories with values below this are reserved for the engine.
	};

	/// Defines the type for the event category bitfield.
	typedef uint8_t event_category_t;

	/// Defines the type for the blocking event dispatcher function. The blocking dispatcher can forward the event as a reference where performance is critical.
	typedef void (event_cb_b_fn)(Event& e);
	/// Defines the type for the non-blocking event dispatcher function. The non-blocking dispatcher must forward the event as a shared pointer.
	typedef void (event_cb_nb_fn)(std::shared_ptr<Event>& e);
	/// Defines the type for the event dispatcher.
	typedef eventpp::EventDispatcher<EventType, event_cb_b_fn, EventPolicyB> event_dispatcher_t;
	/// Defines the type for the event queue.
	typedef eventpp::EventQueue<EventType, event_cb_nb_fn, EventPolicyNb> event_queue_t;
	/// Defines the listener id type.
	typedef uint64_t listener_id_t;

	void event_queue_process();
	void event_queue_process_one();

	void event_dispatch(std::shared_ptr<Event> e);
	void event_dispatch_b(Event& e);
	void event_dispatch_nb(std::shared_ptr<Event> e);

	listener_id_t event_listener_add_b(const EventType type, event_cb_b_fn callback);
	listener_id_t event_listener_add_nb(const EventType type, event_cb_nb_fn callback);

	void event_listener_remove_b(listener_id_t id);
	void event_listener_remove_nb(listener_id_t id);
	void event_listener_remove_all_b();
	void event_listener_remove_all_nb();
	void event_listener_remove_all();

	std::ostream& operator<<(std::ostream& os, const Event& e);

	/**
	 * @brief	The Event class is the virtual base class for all events in the tractor game engine library. All events must be derived from this class.
	 * 
	 * 	The event class is an abstract base class, and must be overridden by the event by creating a derived event. The derived event class must implement the
	 * 	pure virtual functions GetName(), GetType() and GetCategoryFlags(). For better representation of the event data, the ToString() function can be
	 * 	overridden to provide a string representation of the event data, as the default implementation of the ToString() function only returns the name of
	 * 	event.
	 */
	class Event
	{
	public:
		// Constructors and destructors

		/// @brief Default constructor.
		Event() = default;
		/// @brief Virtual default destructor.
		virtual ~Event() = default;
	
		/// @brief Explicitly defined default copy constructor.
		Event(const Event& other) = default;
		/// @brief Explicitly defined default move constructor.
		Event(Event&& other) = default;
		/// @brief Explicitly defined default copy assignment operator.
		Event& operator=(const Event& other) = default;
		/// @brief Explicitly defined default move assignment operator.
		Event& operator=(Event&& other) = default;

		//Public functions
		
		/**
		 * @brief	Get the name of the event. This is a pure virtual function that must be implemented by the derived event class.
		 * 
		 * 	This is a purely virtual function to prevent the name from being stored as a variable in the event class, thus reducing the memory footprint of
		 * 	the event base class.
		 * 
		 * @return const char*	The name of the event.
		 */
		virtual const char* GetName() const = 0;

		/**
		 * @brief	Get the type of the event. This is a pure virtual function that must be implemented by the derived event class.
		 * 
		 * 	This is a purely virtual function to prevent the type from being stored as a variable in the event class, thus reducing the memory footprint of the
		 * 	event base class.
		 * 
		 * @return const EventType	The type of the event.
		 */
		virtual const EventType GetType() const = 0;

		/**
		 * @brief	Get the category flags for the event. This is a pure virtual function that must be implemented by the derived event class.
		 * 
		 * 	This is a purely virtual function to prevent the category flags from being stored as a variable in the event class, thus reducing the memory
		 * 	footprint of the event base class.
		 * 
		 * @return event_category_t	The category flags for the event.
		 */
		virtual event_category_t GetCategoryFlags() const = 0;

		virtual std::string ToString() const;
		bool IsInCategory(EventCategory category) const;
	};

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

#endif // EVENT_HPP_ 