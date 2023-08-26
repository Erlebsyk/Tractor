/**
 * @file	event_joystick.cpp
 * @brief	Source file for joystick events. See event_joystick.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 * 
*/

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "events/event_joystick.hpp"

// External libraries header includes
#include <SDL_joystick.h>
#include <SDL_timer.h>

namespace trac
{
	/**
	 * @brief	Construct a new EventJoystick event.
	 * 
	 * @param id	The ID of the joystick that triggered the event.
	 */
	EventJoystick::EventJoystick(const joystick_id_t id) :
		Event(),
		timestamp_ms_	{ SDL_GetTicks64()	},
		joystick_id_	{ id				}
	{}
	
	/**
	 * @brief	Get the timestamp of the event in milliseconds.
	 * 
	 * @return timestamp_t	The timestamp of the event in milliseconds.
	 */
	timestamp_t EventJoystick::GetTimestampMs() const
	{
		return timestamp_ms_;
	}

	/**
	 * @brief	Get the ID of the joystick that triggered the event.
	 * 
	 * @return joystick_id_t	The ID of the joystick that triggered the event.
	 */
	joystick_id_t EventJoystick::GetJoystickId() const
	{
		return joystick_id_;
	}

	/**
	 * @brief	Construct a new EventJoystickAxisMotion event.
	 * 
	 * @param id	The ID of the joystick that triggered the event.
	 * @param axis_index	The index of the axis that was moved.
	 * @param axis_value	The value of the axis that was moved.
	 */
	EventJoystickAxisMotion::EventJoystickAxisMotion(const joystick_id_t id, const index_t axis_index, const move_value_t axis_value) :
		EventJoystick(id),
		axis_index_	{ axis_index	},
		axis_value_	{ axis_value	}
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventJoystickAxisMotion::GetName() const
	{
		return "EventJoystickAxisMotion";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventJoystickAxisMotion::GetType() const
	{
		return EventType::kJoyAxisMotion;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventJoystickAxisMotion::GetCategoryFlags() const
	{
		return EventCategory::kJoystick | EventCategory::kInput | EventCategory::kAxis;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventJoystickAxisMotion::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << GetJoystickId() << ", " << (uint32_t)axis_index_ << ", " << axis_value_ << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the index of the axis that was moved.
	 * 
	 * @return index_t	The index of the axis that was moved.
	 */
	index_t EventJoystickAxisMotion::GetAxisIndex() const
	{
		return axis_index_;
	}

	/**
	 * @brief	Get the value of the axis that was moved.
	 * 
	 * @return move_value_t	The value of the axis that was moved.
	 */
	move_value_t EventJoystickAxisMotion::GetAxisValue() const
	{
		return axis_value_;
	}

	/**
	 * @brief	Construct a new EventJoystickBallMotion event.
	 * 
	 * @param id	The ID of the joystick that triggered the event.
	 * @param ball_index	The index of the trackball that was moved.
	 * @param x_rel	The relative motion in the x-direction.
	 * @param y_rel	The relative motion in the y-direction.
	 */
	EventJoystickBallMotion::EventJoystickBallMotion(const joystick_id_t id, const index_t ball_index, const move_value_t x_rel, const move_value_t y_rel) :
		EventJoystick(id),
		ball_index_	{ ball_index	},
		x_rel_		{ x_rel			},
		y_rel_		{ y_rel			}
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventJoystickBallMotion::GetName() const
	{
		return "EventJoystickBallMotion";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventJoystickBallMotion::GetType() const
	{
		return EventType::kJoyBallMotion;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventJoystickBallMotion::GetCategoryFlags() const
	{
		return EventCategory::kJoystick | EventCategory::kInput | EventCategory::kBall;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventJoystickBallMotion::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << GetJoystickId() << ", " << (uint32_t)ball_index_ << ", " << x_rel_ << ", " << y_rel_ << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the index of the trackball that was moved.
	 * 
	 * @return index_t	The index of the trackball that was moved.
	 */
	index_t EventJoystickBallMotion::GetBallIndex() const
	{
		return ball_index_;
	}

	/**
	 * @brief	Get the relative motion in the x-direction.
	 * 
	 * @return move_value_t	The relative motion in the x-direction.
	 */
	move_value_t EventJoystickBallMotion::GetXRel() const
	{
		return x_rel_;
	}

	/**
	 * @brief	Get the relative motion in the y-direction.
	 * 
	 * @return move_value_t	The relative motion in the y-direction.
	 */
	move_value_t EventJoystickBallMotion::GetYRel() const
	{
		return y_rel_;
	}

	/**
	 * @brief	Construct a new EventJoystickHatMotion event.
	 * 
	 * @param id	The ID of the joystick that triggered the event.
	 * @param hat_index	The index of the hat that was moved.
	 * @param position	The new position of the hat.
	 */
	EventJoystickHatMotion::EventJoystickHatMotion(const joystick_id_t id, const index_t hat_index, const JoystickHatPosition position) :
		EventJoystick(id),
		hat_index_	{ hat_index	},
		position_	{ position	}
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventJoystickHatMotion::GetName() const
	{
		return "EventJoystickHatMotion";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventJoystickHatMotion::GetType() const
	{
		return EventType::kJoyHatMotion;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventJoystickHatMotion::GetCategoryFlags() const
	{
		return EventCategory::kJoystick | EventCategory::kInput | EventCategory::kHat;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventJoystickHatMotion::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << GetJoystickId() << ", " << GetIndex() << ", ";
		
		if(position_ == JoystickHatPosition::kCentered)
			ss << "centered";
		else if(position_ == JoystickHatPosition::kUp)
			ss << "up";
		else if(position_ == JoystickHatPosition::kRight)
			ss << "right";
		else if(position_ == JoystickHatPosition::kDown)
			ss << "down";
		else if(position_ == JoystickHatPosition::kLeft)
			ss << "left";
		else if(position_ == JoystickHatPosition::kRightUp)
			ss << "right-up";
		else if(position_ == JoystickHatPosition::kRightDown)
			ss << "right-down";
		else if(position_ == JoystickHatPosition::kLeftUp)
			ss << "left-up";
		else if(position_ == JoystickHatPosition::kLeftDown)
			ss << "left-down";
		else
			ss << "unknown";

		ss << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the index of the hat that was moved.
	 * 
	 * @return index_t	The index of the hat that was moved.
	 */
	index_t EventJoystickHatMotion::GetIndex() const
	{
		return hat_index_;
	}

	/**
	 * @brief	Get the new position of the hat.
	 * 
	 * @return JoystickHatPosition	The new position of the hat.
	 */
	JoystickHatPosition EventJoystickHatMotion::GetPosition() const
	{
		return position_;
	}

	/**
	 * @brief	Construct a new EventJoystickButton event.
	 * 
	 * @param id	The ID of the joystick that triggered the event.
	 * @param button	The index of the button that was pressed.
	 */
	EventJoystickButton::EventJoystickButton(const joystick_id_t id, const index_t button) :
		EventJoystick(id),
		button_	{ button	}
	{}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventJoystickButton::GetCategoryFlags() const
	{
		return EventCategory::kJoystick | EventCategory::kInput | EventCategory::kButton;
	}

	/**
	 * @brief	Get the index of the button that was pressed.
	 * 
	 * @return index_t	The index of the button that was pressed.
	 */
	index_t EventJoystickButton::GetButton() const
	{
		return button_;
	}

	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventJoystickButton::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << GetJoystickId() << ", " << GetButton() << "]";
		return ss.str();
	}

	/**
	 * @brief	Construct a new EventJoystickButtonUp event.
	 * 
	 * @param id	The ID of the joystick that triggered the event.
	 * @param button	The index of the button that was released.
	 */
	EventJoystickButtonDown::EventJoystickButtonDown(const joystick_id_t id, const index_t button) :
		EventJoystickButton(id, button)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventJoystickButtonDown::GetName() const
	{
		return "EventJoystickButtonDown";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventJoystickButtonDown::GetType() const
	{
		return EventType::kJoyButtonDown;
	}

	/**
	 * @brief	Construct a new EventJoystickButtonUp event.
	 * 
	 * @param id	The ID of the joystick that triggered the event.
	 * @param button	The index of the button that was released.
	 */
	EventJoystickButtonUp::EventJoystickButtonUp(const joystick_id_t id, const index_t button) :
		EventJoystickButton(id, button)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventJoystickButtonUp::GetName() const
	{
		return "EventJoystickButtonUp";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventJoystickButtonUp::GetType() const
	{
		return EventType::kJoyButtonUp;
	}

	/**
	 * @brief	Construct a new EventJoystickDevice event.
	 * 
	 * @param id	The ID of the joystick that triggered the event.
	 */
	EventJoystickDevice::EventJoystickDevice(const joystick_id_t id) :
		EventJoystick(id)
	{}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventJoystickDevice::GetCategoryFlags() const
	{
		return EventCategory::kJoystick | EventCategory::kDevice;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventJoystickDevice::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << GetJoystickId() << "]";
		return ss.str();
	}

	/**
	 * @brief	Construct a new EventJoystickDeviceRemoved event.
	 * 
	 * @param id	The ID of the joystick that triggered the event.
	 */
	EventJoystickDeviceAdded::EventJoystickDeviceAdded(const joystick_id_t id) :
		EventJoystickDevice(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventJoystickDeviceAdded::GetName() const
	{
		return "EventJoystickDeviceAdded";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventJoystickDeviceAdded::GetType() const
	{
		return EventType::kJoyDeviceAdded;
	}

	/**
	 * @brief	Construct a new EventJoystickDeviceRemoved event.
	 * 
	 * @param id	The ID of the joystick that triggered the event.
	 */
	EventJoystickDeviceRemoved::EventJoystickDeviceRemoved(const joystick_id_t id) :
		EventJoystickDevice(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventJoystickDeviceRemoved::GetName() const
	{
		return "EventJoystickDeviceRemoved";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventJoystickDeviceRemoved::GetType() const
	{
		return EventType::kJoyDeviceRemoved;
	}

	/**
	 * @brief	Construct a new EventJoystickBatteryUpdated event.
	 * 
	 * @param id	The ID of the joystick that triggered the event.
	 * @param battery_level	The new battery level.
	 */
	EventJoystickBatteryUpdated::EventJoystickBatteryUpdated(const joystick_id_t id, const JoystickBatteryLevel battery_level) :
		EventJoystick(id),
		battery_level_	{ battery_level	}
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventJoystickBatteryUpdated::GetName() const
	{
		return "EventJoystickBatteryUpdated";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventJoystickBatteryUpdated::GetType() const
	{
		return EventType::kJoyBatteryUpdated;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventJoystickBatteryUpdated::GetCategoryFlags() const
	{
		return EventCategory::kJoystick | EventCategory::kSensor;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventJoystickBatteryUpdated::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << GetJoystickId() << ", ";
		if(GetLevel() == JoystickBatteryLevel::kUnknown)
			ss << "unknown";
		else if(GetLevel() == JoystickBatteryLevel::kEmpty)
			ss << "empty";
		else if(GetLevel() == JoystickBatteryLevel::kLow)
			ss << "low";
		else if(GetLevel() == JoystickBatteryLevel::kMedium)
			ss << "medium";
		else if(GetLevel() == JoystickBatteryLevel::kFull)
			ss << "full";
		else if(GetLevel() == JoystickBatteryLevel::kWired)
			ss << "wired";
		else
			ss << "unknown";

		ss << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the new battery level.
	 * 
	 * @return JoystickBatteryLevel	The new battery level.
	 */
	JoystickBatteryLevel EventJoystickBatteryUpdated::GetLevel() const
	{
		return battery_level_;
	}

} // namespace trac
