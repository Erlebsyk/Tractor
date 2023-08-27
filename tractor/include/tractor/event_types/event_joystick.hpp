/**
 * @file	event_joystick.hpp
 * @brief	Joystick input event header file. All events related to joystick input are defined here.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 * 
*/

#ifndef EVENT_JOYSTICK_HPP_
#define EVENT_JOYSTICK_HPP_

// Related header include
#include "event_base.hpp"

// External libraries header includes
#include <SDL_joystick.h>

namespace trac
{
	/// Type definition for joystick IDs.
	typedef SDL_JoystickID joystick_id_t;
	/// Type definition for joystick axis indices.
	typedef uint16_t index_t;
	/// Type definition for joystick axis move values.
	typedef int16_t move_value_t;

	/// @brief	Enumeration of the possible joystick hat positions.
	enum class JoystickHatPosition
	{
		kCentered = SDL_HAT_CENTERED,
		kUp = SDL_HAT_UP,
		kRight = SDL_HAT_RIGHT,
		kDown = SDL_HAT_DOWN,
		kLeft = SDL_HAT_LEFT,
		kRightUp = SDL_HAT_RIGHTUP,
		kRightDown = SDL_HAT_RIGHTDOWN,
		kLeftUp = SDL_HAT_LEFTUP,
		kLeftDown = SDL_HAT_LEFTDOWN
	};

	/// @brief	Enumeration of the defined joystick battery levels.
	enum class JoystickBatteryLevel
	{
		kUnknown = SDL_JOYSTICK_POWER_UNKNOWN,
		kEmpty = SDL_JOYSTICK_POWER_EMPTY,
		kLow = SDL_JOYSTICK_POWER_LOW,
		kMedium = SDL_JOYSTICK_POWER_MEDIUM,
		kFull = SDL_JOYSTICK_POWER_FULL,
		kWired = SDL_JOYSTICK_POWER_WIRED
	};

	/// @brief	Abstract base class for joystick events.
	class EventJoystick : public Event
	{
	public:
		// Constructors and destructors
	
		EventJoystick(joystick_id_t id);
		/// @brief Virtual default destructor.
		virtual ~EventJoystick() = default;

		/// @brief Explicitly defined default copy constructor.
		EventJoystick(const EventJoystick&) = default;
		/// @brief Explicitly defined default move constructor.
		EventJoystick(EventJoystick&&) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventJoystick& operator=(const EventJoystick&) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventJoystick& operator=(EventJoystick&&) = default;
	
		//Public functions
	
		timestamp_t GetTimestampMs() const override;

		joystick_id_t GetJoystickId() const;

	private:
		/// The timestamp of the event.
		timestamp_t timestamp_ms_;
		/// The joystick ID.
		joystick_id_t joystick_id_;
	};

	/// @brief	Event for joystick axis motion.
	class EventJoystickAxisMotion : public EventJoystick
	{
	public:
		// Constructors and destructors
	
		EventJoystickAxisMotion(joystick_id_t id, index_t axis_index, move_value_t axis_value);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;
	
		index_t GetAxisIndex() const;
		move_value_t GetAxisValue() const;

	private:
		/// The axis index.
		index_t axis_index_;
		/// The axis value.
		move_value_t axis_value_;
	};

	/// @brief	Event for joystick trackball motion.
	class EventJoystickBallMotion : public EventJoystick
	{
	public:
		// Constructors and destructors
	
		EventJoystickBallMotion(joystick_id_t id, index_t ball_index, move_value_t x_rel, move_value_t y_rel);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;
	
		index_t GetBallIndex() const;
		move_value_t GetXRel() const;
		move_value_t GetYRel() const;

	private:
		/// The index of the trackball that was moved.
		index_t ball_index_;
		/// The relative motion in the x-direction.
		move_value_t x_rel_;
		/// The relative motion in the y-direction.
		move_value_t y_rel_;
	};

	/// @brief	Event for joystick hat position change.
	class EventJoystickHatMotion : public EventJoystick
	{
	public:
		// Constructors and destructors
	
		EventJoystickHatMotion(joystick_id_t id, index_t hat_index, JoystickHatPosition position);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;
	
		index_t GetIndex() const;
		JoystickHatPosition GetPosition() const;

	private:
		/// The index of the hat that was moved.
		index_t hat_index_;
		/// The new hat position.
		JoystickHatPosition position_;
	};

	/// @brief	Abstract base class for joystick button events.
	class EventJoystickButton : public EventJoystick
	{
	public:
		// Constructors and destructors
	
		EventJoystickButton(joystick_id_t id, index_t button);
		/// @brief Virtual default destructor.
		virtual ~EventJoystickButton() = default;

		/// @brief Explicitly defined default copy constructor.
		EventJoystickButton(const EventJoystickButton&) = default;
		/// @brief Explicitly defined default move constructor.
		EventJoystickButton(EventJoystickButton&&) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventJoystickButton& operator=(const EventJoystickButton&) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventJoystickButton& operator=(EventJoystickButton&&) = default;
	
		//Public functions

		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;

		index_t GetButton() const;
	
	private:
		/// The index of the button that was pressed or released.
		index_t button_;
	};

	/// @brief	Event for joystick button press.
	class EventJoystickButtonDown : public EventJoystickButton
	{
	public:
		// Constructors and destructors
	
		EventJoystickButtonDown(joystick_id_t id, index_t button);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Event for joystick button release.
	class EventJoystickButtonUp : public EventJoystickButton
	{
	public:
		// Constructors and destructors
	
		EventJoystickButtonUp(joystick_id_t id, index_t button);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief Abstract base class for joystick device events.
	class EventJoystickDevice : public EventJoystick
	{
	public:
		// Constructors and destructors
	
		EventJoystickDevice(joystick_id_t id);
		/// @brief Virtual default destructor.
		virtual ~EventJoystickDevice() = default;

		/// @brief Explicitly defined default copy constructor.
		EventJoystickDevice(const EventJoystickDevice&) = default;
		/// @brief Explicitly defined default move constructor.
		EventJoystickDevice(EventJoystickDevice&&) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventJoystickDevice& operator=(const EventJoystickDevice&) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventJoystickDevice& operator=(EventJoystickDevice&&) = default;
	
		//Public functions
	
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;
	};

	/// @brief	Event triggered when a new joystick is added.
	class EventJoystickDeviceAdded : public EventJoystickDevice
	{
	public:
		// Constructors and destructors
	
		EventJoystickDeviceAdded(joystick_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Event triggered when a joystick is removed.
	class EventJoystickDeviceRemoved : public EventJoystickDevice
	{
	public:
		// Constructors and destructors
	
		EventJoystickDeviceRemoved(joystick_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Joystick battery update event.
	class EventJoystickBatteryUpdated : public EventJoystick
	{
	public:
		// Constructors and destructors
	
		EventJoystickBatteryUpdated(joystick_id_t id, JoystickBatteryLevel battery_level);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;
	
		JoystickBatteryLevel GetLevel() const;

	private:
		/// The new battery level.
		JoystickBatteryLevel battery_level_;
	};
} // Namespace trac

#endif // EVENT_JOYSTICK_HPP_ 