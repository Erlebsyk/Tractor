/**
 * @file	event.h
 * @brief	Main header file for the tractor event system. The event system is used to handle events in the tractor game engine library, such as keyboard
 * 			events, mouse events, window events, etc. This file defines the main events and event categories, and introduces the event base class.
 * 
 * 	Events and event types are introduced in this library, but the external library 'eventpp' is used to set up the event system. The eventpp library provides
 * 	all the mechanisms needed to set up the event system, such as event listeners, dispatchment, etc.
 * 
 * @author	Erlend Elias Isachsen
 * @date	23.07.2023
 * 
*/

#ifndef EVENT_H_
#define EVENT_H_

// Standard library header includes
#include <cstdint>
#include <string>
#include <vector>
#include <ostream>
#include <memory>

// External libraries header includes
#include "eventpp/eventdispatcher.h"
#include "eventpp/eventqueue.h"

// Project header includes


namespace trac
{
	// Defines/macros, enums and variables
	enum class EventType;
	enum EventCategory;

	class Event;
	struct EventPolicyB;
	struct EventPolicyNb;
	class EventDispatcher;

	/**
	 * @brief	The EventType enum defines the different types of events that can be handled by the tractor game engine library.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
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
	 * 
	 * @author	Erlend Elias Isachsen
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

	// Funciton declarations
	inline void event_queue_process();
	inline void event_dispatch(std::shared_ptr<Event> e);
	inline void event_dispatch_b(Event& e);
	inline void event_dispatch_nb(std::shared_ptr<Event> e);
	inline void event_add_listener_b(const EventType type, event_cb_b_fn callback);
	inline void event_add_listener_nb(const EventType type, event_cb_nb_fn callback);

	// Classes and structs
	/**
	 * @brief	The Event class is the base class for all events in the tractor game engine library. All events must be derived from this class.
	 * 
	 * 	The event class is an abstract base class, and must be overridden by the event by creating a derived event. The derived event class must implement the
	 * 	pure virtual functions GetName(), GetType() and GetCategoryFlags(). For better representation of the event data, the ToString() function can be
	 * 	overridden to provide a string representation of the event data, as the default implementation of the ToString() function only returns the name of
	 * 	event. S
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	class Event
	{
	public:
		// Constructors and destructors
		Event() = default;
		~Event() = default;
	
		//Public functions
		// Pure virtual functions that needs to be implemented by the derived event class
		
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
		 * 
		 * @author	Erlend Elias Isachsen
		 */
		virtual const EventType GetType() const = 0;

		/**
		 * @brief	Get the category flags for the event. This is a pure virtual function that must be implemented by the derived event class.
		 * 
		 * 	This is a purely virtual function to prevent the category flags from being stored as a variable in the event class, thus reducing the memory
		 * 	footprint of the event base class.
		 * 
		 * @return event_category_t	The category flags for the event.
		 * 
		 * @author	Erlend Elias Isachsen
		 */
		virtual event_category_t GetCategoryFlags() const = 0;


		// Generic functions that can be used by the derived event class.

		/**
		 * @brief	Converts the event to a string representation. This function is used to print the event data to the console.
		 * 
		 * @return std::string	The string representation of the event.
		 */
		virtual std::string ToString() const { return GetName(); }

		/**
		 * @brief	Returns whether the event is in the provided category or not.
		 * 
		 * @param category	The category to check.
		 * @return bool	True if the event is in the provided category, false otherwise.
		 * @retval True	The event is in the provided category.
		 * @retval False	The event is not in the provided category.
		 * 
		 */
		bool IsInCategory(EventCategory category) const { return GetCategoryFlags() & category; }

		//Public variables
	
	private:
		//Private functions
	
		//Private variables
	};

	/**
	 * @brief	Defines a policy for the blocking event dispatcher. This policy is used to get the event type from the event, allowing events to be dispatched
	 * 			directly without having to explicitly specify the event type.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	struct EventPolicyB
	{
		/**
		 * @brief	Returns the event type for the for a given event reference.
		 * 
		 * @param e	The event to get the type for.
		 * @return EventType	The event type for the provided event.
		 * 
		 */
		static EventType GetEventType(const Event& e) { return e.GetType();}
	};
	
	/**
	 * @brief	Defines a policy for the non-blocking event dispatcher. This policy is used to get the event type from the event, allowing events to be
	 * 			dispatched directly without having to explicitly specify the event type.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	struct EventPolicyNb
	{
		/**
		 * @brief	Get the event type for the provided event pointer.
		 * 
		 * @param e	The event to get the type for.
		 * @return EventType	The event type for the provided event.
		 * 
		 */
		static EventType GetEventType(const std::shared_ptr<Event>& e) { return e->GetType();}
	};

	/**
	 * @brief	The EventDispatcher class is used to dispatch events to the event listeners.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	class EventDispatcher
	{
	public:
		/**
		 * @brief	Initialize the event dispatcher. This function must be called before the event dispatcher can be used.
		 * 
		 * @author	Erlend Elias Isachsen
		 */
		inline static void Initialize() {
			engine_dispatcher_s_ = std::make_shared<event_dispatcher_t>();
			engine_queue_s_ = std::make_shared<event_queue_t>();
		}

		// Constructors and destructors
		EventDispatcher() = default;
		~EventDispatcher() = default;
	
		//Public functions
	
		//Public variables
		/**
		 * @brief	Get the global engine event dispatcher. This function returns a reference to the global engine event dispatcher.
		 * 
		 * @return std::shared_ptr<event_dispatcher_t>& The global engine event dispatcher.
		 * 
		 * @author	Erlend Elias Isachsen
		 */
		inline static std::shared_ptr<event_dispatcher_t>& GetEngineDispatcher() { return engine_dispatcher_s_; }

		/**
		 * @brief	Get the global engine event queue. This function returns a reference to the global engine event queue.
		 * 
		 * @return std::shared_ptr<event_queue_t>&	
		 * 
		 * @author	Erlend Elias Isachsen
		 */
		inline static std::shared_ptr<event_queue_t>& GetEngineQueue() { return engine_queue_s_; }

	private:
		//Private functions
	
		//Private variables
		static inline std::shared_ptr<event_dispatcher_t> engine_dispatcher_s_ = nullptr;
		static inline std::shared_ptr<event_queue_t> engine_queue_s_ = nullptr;

	};

	// Implementation

	/**
	 * @brief	Processes all queued events submitted through the non-blocking event dispatcher (i.e event_dispatch or event_dispatch_nb).
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	void event_queue_process()
	{
		EventDispatcher::GetEngineQueue()->process();
	}

	/**
	 * @brief	Dispatches the provided event to the event listeners. This will dispatch the event to both the blocking and non-blocking event dispatchers.
	 * 
	 * @param e	The event to dispatch.
	 * 
	 * @author	Erlend Elias Isachsen
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
	 * 
	 * @author	Erlend Elias Isachsen
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
	 * @author	Erlend Elias Isachsen
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
	 * @author	Erlend Elias Isachsen
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
	 * 
	 * @author	Erlend Elias Isachsen
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
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

} // Namespace trac


#endif // EVENT_H_ 

/*
 * END OF FILE
 */