/**
 * @file	event_base.hpp
 * @brief	
 * 
 * @author	Erlend Elias Isachsen
 * @date	23.07.2023
 * 
*/

#ifndef EVENT_BASE_HPP_
#define EVENT_BASE_HPP_

// External libraries header includes
#include "eventpp/eventdispatcher.h"
#include "eventpp/eventqueue.h"
namespace trac
{
	/// Type definition for the timestamp type. The timestamp is in milliseconds.
	typedef uint64_t timestamp_t;
	/// Type definition for pixel positions.
	typedef int32_t pos_pixel_t;
	/// Type definition for pixel sizes.
	typedef int32_t size_pixel_t;
	/// Type definition for relative positions, normalized to the range 0.0 to 1.0 or -1.0 to 1.0.
	typedef float pos_rel_t;
	/// Type definition for relative sizes, normalized to the range 0.0 to 1.0.
	typedef float size_rel_t;
	/// Declares the base event class.
	class Event;

	/**
	 * @brief	The EventType enum defines the different types of events that can be handled by the tractor game engine library. Each event type has a
	 * 			corresponding event class that contains the relevant event data. Each event can also be categorized into one or more categories, which can be
	 * 			used to filter events and is defined in the EventCategory enum.
	 */
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
		kWindowClosed, // The window manager requests that the window be closed.

		// Layer events
		kLayerPushed, // A layer has been pushed onto the layer stack.
		kLayerPopped, // A layer has been popped from the layer stack.
		kLayerUpdated, // A layer has been updated.
		kLayerAttached, // A layer has been attached to the application.
		kLayerDetached, // A layer has been detached from the application.
		
		// Keyboard events
		kKeyDown, // Key pressed event.
		kKeyUp, // Key released event.
		kTextEditing, // Keyboard text editing event.
		kTextInput, // Keyboard text input event.
		kKeyMapChanged, // Keymap changed event (for instance language change).

		// Mouse events
		kMouseMotion, // Mouse moved event.
		kMouseButtonDown, // Mouse button pressed event.
		kMouseButtonUp, // Mouse button released event.
		kMouseButtonClicked, // Mouse button clicked event.
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
		kDevice				= (1 << 2),
		kWindow				= (1 << 3),
		kDisplay			= (1 << 4),
		kAudio				= (1 << 5),

		kKeyboard			= (1 << 6),
		kMouse				= (1 << 7),
		kController			= (1 << 8),
		kJoystick			= (1 << 9),

		kButton				= (1 << 10),
		kAxis				= (1 << 11),
		kTouch				= (1 << 12),
		kHat				= (1 << 13),
		kBall				= (1 << 14),
		kSensor				= (1 << 15),

		kEngineFinal		= (1 << 16) // This is the last category in the engine. All categories with values below this are reserved for the engine.
	};

	/// Defines the type for the event category bitfield.
	typedef uint32_t event_category_t;

	std::ostream& operator<<(std::ostream& os, const Event& e);
	std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Event> e);

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
		 * @return timestamp_t	The timestamp of the event in milliseconds.
		 */
		virtual timestamp_t GetTimestampMs() const = 0;

		virtual std::string ToString() const;
		bool IsInCategory(EventCategory category) const;
	};
} // Namespace trac

#endif // EVENT_BASE_HPP_ 