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
		kNone = 0, // No event type. First event type equals 0.

		// System events
		kQuit, // User requested quit event.
		kLocaleChanged, // The user's locale preferences have changed.
		kClipboardUpdate, // The clipboard changed.
		kDropFile, // The system requests a file open.
		kDropText, // text/plain drag-and-drop event.
		kDropBegin, // A new set of drops is beginning (NULL filename).
		kDropComplete, // Current set of drops is now complete (NULL filename).

		// Audio hotplug events
		kAudioDeviceAdded, // A new audio device is available.
		kAudioDeviceRemoved, // An audio device has been removed.

		// Application events
		kAppTerminating, // The application is being terminated by the OS.
		kAppLowMemory, // The application is low on memory, free memory if possible.
		kAppEnteringBackground, // The application is about to enter the background.
		kAppEnteredBackground, // The application did enter the background and may not get CPU for some time.
		kAppEnteringForeground, // The application is about to enter the foreground.
		kAppEnteredForeground, // The application is now interactive.
		kAppTick, // Application tick event.
		kAppUpdated, // Application update event.
		kAppRendered, // Application render event.

		// Display events
		kDisplayOrientation, // Display orientation has changed.
		kDisplayConnected, // Display has been added to the system.
		kDisplayDisconnected, // Display has been removed from the system.

		// Window events
		kWindowShown, // Window has been shown.
		kWindowHidden, // Window has been hidden.
		kWindowExposed, // Window has been exposed and should be redrawn.
		kWindowMoved, // Window has been moved.
		kWindowResized, // Window has been resized.
		kWindowSizeChanged, // The window size has changed, either as a result of an API call or through the system or user changing the window size.
		kWindowMinimized, // Window has been minimized.
		kWindowMaximized, // Window has been maximized.
		kWindowRestored, // Window has been restored to normal size and position.
		kWindowEnter, // Window has gained mouse focus.
		kWindowLeave, // Window has lost mouse focus.
		kWindowFocusGained, // Window has gained keyboard focus.
		kWindowFocusLost, // Window has lost keyboard focus.
		kWindowTakeFocus, // Window is being offered a focus.
		kWindowHitTest, // Window had a hit test that wasn't SDL_HITTEST_NORMAL.
		kWindowIccProfileChanged, // Window has had its ICC profile changed.
		kWindowDisplayChanged, // Window display data has changed.
		kWindowClose, // The window manager requests that the window be closed.
		
		// Keyboard events
		kKeyDown, // Key pressed event.
		kKeyUp, // Key released event.
		kTextEditing, // Keyboard text editing event.
		kTextEditingExt, // Extended keyboard text editing event.
		kTextInput, // Keyboard text input event.
		kKeyMapChanged, // Keymap changed event (for instance language change).

		// Mouse events
		kMouseMotion, // Mouse moved event.
		kMouseButtonDown, // Mouse button pressed event.
		kMouseButtonUp, // Mouse button released event.
		kMouseWheel, // Mouse wheel event.

		// Joystick events
		kJoyAxisMotion, // Joystick axis motion event.
		kJoyBallMotion, // Joystick trackball motion event.
		kJoyHatMotion, // Joystick hat position change event.
		kJoyButtonDown, // Joystick button pressed event.
		kJoyButtonUp, // Joystick button released event.
		kJoyDeviceAdded, // A new joystick has been inserted into the system.
		kJoyDeviceRemoved, // An opened joystick has been removed.
		kJoyBatteryUpdated, // The state of a joystick battery has changed.

		// Controller events
		kControllerAxisMotion, // Game controller axis motion.
		kControllerButtonDown, // Game controller button pressed.
		kControllerButtonUp, // Game controller button released.
		kControllerDeviceAdded, // A new Game controller has been inserted into the system.
		kControllerDeviceRemoved, // An opened Game controller has been removed.
		kControllerDeviceRemapped, // The controller mapping was updated.
		kControllerTouchpadMotion, // Game controller touchpad moved.
		kControllerTouchpadDown, // Game controller touchpad button pressed.
		kControllerTouchpadUp, // Game controller touchpad button released.
		kControllerSensorUpdate, // Game controller sensor updated.

		// Touch events
		kFingerDown, // Finger touch down event.
		kFingerUp, // Finger touch up event.
		kFingerMotion, // Finger touch motion event.

		// Gesture events
		kDollarGesture, // Dollar gesture event.
		kDollarRecord, // Dollar gesture recording event.
		kMultiGesture, // Multi Finger Gesture data.

		// Render events
		kRenderTargetsReset, // The render targets have been reset and their contents need to be updated.
		kRenderDeviceReset, // The device has been reset and all textures need to be recreated.

		kEventTypeCount // The number of event types.
	};

	/**
	 * @brief	The EventCategory enum defines the different categories of events that can be handled by the tractor game engine library. Multiple categories
	 * 			can be used for a single event, hence the use of bit flags.
	 */
	enum EventCategory
	{
		kNone				= 0,
		kApplication		= (1 << 0),
		kInput				= (1 << 1),
		kKeyboard			= (1 << 2),
		kMouse				= (1 << 3),
		kMouseButton		= (1 << 4),
		kController			= (1 << 5),
		kControllerButton	= (1 << 6),
		kControllerAxis		= (1 << 7),
		kJoystick			= (1 << 8),
		kJoystickButton		= (1 << 9),
		kJoystickAxis		= (1 << 10),
		kWindow				= (1 << 11),
		kDisplay			= (1 << 12),
		kEngineFinal		= (1 << 13) // This is the last category in the engine. All categories with values below this are reserved for the engine.
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
		virtual EventType GetType() const = 0;

		/**
		 * @brief	Get the category flags for the event. This is a pure virtual function that must be implemented by the derived event class.
		 * 
		 * 	This is a purely virtual function to prevent the category flags from being stored as a variable in the event class, thus reducing the memory
		 * 	footprint of the event base class.
		 * 
		 * @return event_category_t	The category flags for the event.
		 */
		virtual event_category_t GetCategoryFlags() const = 0;

		/**
		 * @brief	Get the timestamp of the event in milliseconds.
		 * 
		 * @return uint64_t	The timestamp of the event in milliseconds.
		 */
		virtual uint64_t GetTimestampMs() const = 0;

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