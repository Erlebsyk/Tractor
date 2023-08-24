/**
 * @file	event_controller.cpp
 * @brief	Source file for controller input events. See event_controller.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 * 
*/

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "events/event_controller.hpp"

// External libraries header includes
#include <SDL_timer.h> // To get the timestamp of the event

namespace trac
{
	/**
	 * @brief	Creates a new controller event.
	 * 
	 * @param controller_id	The id of the controller that triggered the event.
	 */
	EventController::EventController(const controller_id_t controller_id) :
		Event(),
		timestamp_ms_	{ SDL_GetTicks64()	},
		controller_id_	{ controller_id		}
	{}

	/**
	 * @brief	Get the timestamp of the event in milliseconds.
	 * 
	 * @return timestamp_t	The timestamp of the event in milliseconds.
	 */
	timestamp_t EventController::GetTimestampMs() const
	{
		return timestamp_ms_;
	}

	/**
	 * @brief	Get a string representation of the event.
	 * 
	 * @return std::string	A string representation of the event.
	 */
	std::string EventController::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << GetControllerId() << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the controller id of the controller that triggered the event.
	 * 
	 * @return controller_id_t	The controller id of the controller that triggered the event.
	 */
	controller_id_t EventController::GetControllerId() const
	{
		return controller_id_;
	}

	/**
	 * @brief	Constructs a new ControllerAxisMotion event.
	 * 
	 * @param id	The id of the controller that triggered the event.
	 * @param axis	The axis that was moved.
	 * @param value	The value of the axis.
	 */
	EventControllerAxisMotion::EventControllerAxisMotion(const controller_id_t id, const uint16_t axis, const int16_t value) :
		EventController(id),
		axis_	{ axis	},
		value_	{ value	}
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventControllerAxisMotion::GetName() const
	{
		return "EventControllerAxisMotion";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventControllerAxisMotion::GetType() const
	{
		return EventType::kControllerAxisMotion;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventControllerAxisMotion::GetCategoryFlags() const
	{
		return EventCategory::kController | EventCategory::kInput | EventCategory::kAxis;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventControllerAxisMotion::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << GetControllerId() << ", " << GetAxis() << ", " << GetValue() << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the axis that was moved.
	 * 
	 * @return uint16_t	The axis that was moved.
	 */
	uint16_t EventControllerAxisMotion::GetAxis() const
	{
		return axis_;
	}

	/**
	 * @brief	Get the value of the axis.
	 * 
	 * @return int16_t	The value of the axis.
	 */
	int16_t EventControllerAxisMotion::GetValue() const
	{
		return value_;
	}


	/**
	 * @brief	Creates a new controller button event.
	 * 
	 * @param id	The id of the controller that triggered the event.
	 * @param button	The button that triggered the event.
	 * @param button_state	The state of the button that triggered the event (i.e. pressed/released).
	 */
	EventControllerButton::EventControllerButton(const controller_id_t id, const controller_button_t button, const controller_button_state_t button_state) : 
		EventController(id),
		button_			{ button		},
		button_state_	{ button_state	}
	{}

	/**
	 * @brief	Get the category flags of the event.
	 * 
	 * @return event_category_t	The category flags of the event.
	 */
	event_category_t EventControllerButton::GetCategoryFlags() const
	{
		return EventCategory::kController | EventCategory::kInput | EventCategory::kButton;
	}
	
	/**
	 * @brief	Get the button that triggered the event.
	 * 
	 * @return controller_button_t	The button that triggered the event.
	 */
	controller_button_t EventControllerButton::GetButton() const
	{
		return button_;
	}

	/**
	 * @brief	Get the state of the button that triggered the event (i.e. pressed/released).
	 * 
	 * @return controller_button_state_t	The state of the button that triggered the event.
	 */
	controller_button_state_t EventControllerButton::GetButtonState() const
	{
		return button_state_;
	}
	
	/**
	 * @brief	Constructs a new ControllerButtonDown event.
	 * 
	 * @param id	The id of the controller that triggered the event.
	 * @param button	The button that was pressed.
	 * 
	 */
	EventControllerButtonDown::EventControllerButtonDown(const controller_id_t id, const controller_button_t button) :
		EventControllerButton(id, button, SDL_PRESSED)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventControllerButtonDown::GetName() const
	{
		return "EventControllerButtonDown";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventControllerButtonDown::GetType() const
	{
		return EventType::kControllerButtonDown;
	}

	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventControllerButtonDown::ToString() const
	{
		std::stringstream ss;
		ss << GetName();
		ss << ": [" << GetControllerId() << ", " << GetButton() << "]";
		return ss.str();
	}

	/**
	 * @brief	Constructs a new ControllerButtonUp event.
	 * 
	 * @param id	The id of the controller that triggered the event.
	 * @param button	The button that was released.
	 */
	EventControllerButtonUp::EventControllerButtonUp(const controller_id_t id, const controller_button_t button) :
		EventControllerButton(id, button, SDL_RELEASED)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventControllerButtonUp::GetName() const
	{
		return "EventControllerButtonUp";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventControllerButtonUp::GetType() const
	{
		return EventType::kControllerButtonUp;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventControllerButtonUp::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << GetControllerId() << ", " << GetButton() << "]";
		return ss.str();
	}

	/**
	 * @brief	Constructs a new ControllerDevice event.
	 * 
	 * @param id	The id of the controller that triggered the event.
	 */
	EventControllerDevice::EventControllerDevice(const controller_id_t id) :
		EventController(id)
	{}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventControllerDevice::GetCategoryFlags() const
	{
		return EventCategory::kController | EventCategory::kDevice;
	}
	
	/**
	 * @brief	Creates a new controller device added event.
	 * 
	 * @param id	The id of the controller that triggered the event.
	 */
	EventControllerDeviceAdded::EventControllerDeviceAdded(const controller_id_t id) :
		EventControllerDevice(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventControllerDeviceAdded::GetName() const
	{
		return "EventControllerDeviceAdded";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventControllerDeviceAdded::GetType() const
	{
		return EventType::kControllerDeviceAdded;
	}

	/**
	 * @brief	Creates a new controller device removed event.
	 * 
	 * @param id	The id of the controller that triggered the event.
	 */
	EventControllerDeviceRemoved::EventControllerDeviceRemoved(const controller_id_t id) :
		EventControllerDevice(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventControllerDeviceRemoved::GetName() const
	{
		return "EventControllerDeviceRemoved";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventControllerDeviceRemoved::GetType() const
	{
		return EventType::kControllerDeviceRemoved;
	}
	
	/// @brief Constructs a new ControllerDeviceRemapped event.
	EventControllerDeviceRemapped::EventControllerDeviceRemapped(const controller_id_t id) :
		EventControllerDevice(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventControllerDeviceRemapped::GetName() const
	{
		return "EventControllerDeviceRemapped";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventControllerDeviceRemapped::GetType() const
	{
		return EventType::kControllerDeviceRemapped;
	}

	/**
	 * @brief	Creates a new controller touchpad event.
	 * 
	 * @param id	The id of the controller that triggered the event.
	 * @param touchpad_index	The index of the touchpad that triggered the event.
	 * @param touchpad_finger_index	The index of the finger that triggered the event.
	 */
	EventControllerTouchpad::EventControllerTouchpad(
			const controller_id_t id,
			const controller_touchpad_t touchpad_index,
			const controller_touchpad_finger_t touchpad_finger_index
		) : 
			EventController(id),
			touchpad_index_			{ touchpad_index			},
			touchpad_finger_index_	{ touchpad_finger_index		}
	{}

	/**
	 * @brief	Get the category flags of the event.
	 * 
	 * @return controller_touchpad_t	The category flags of the event.
	 */
	controller_touchpad_t EventControllerTouchpad::GetTouchpadIndex() const
	{
		return touchpad_index_;
	}

	/**
	 * @brief	Get the finger index of the event.
	 * 
	 * @return controller_touchpad_finger_t	The finger index of the event.
	 */
	controller_touchpad_finger_t EventControllerTouchpad::GetTouchpadFingerIndex() const
	{
		return touchpad_finger_index_;
	}

	/**
	 * @brief	Creates a new controller touchpad motion event.
	 * 
	 * @param id	The id of the controller that triggered the event.
	 * @param touchpad_index	The index of the touchpad that triggered the event.
	 * @param touchpad_finger_index	The index of the finger that triggered the event.
	 * @param pos_x	The x position of the finger on the touchpad.
	 * @param pos_y	The y position of the finger on the touchpad.
	 */
	EventControllerTouchpadMotion::EventControllerTouchpadMotion(
			const controller_id_t id,
			const controller_touchpad_t touchpad_index,
			const controller_touchpad_finger_t touchpad_finger_index,
			const pos_rel_t pos_x,
			const pos_rel_t pos_y
		) :
			EventControllerTouchpad(id, touchpad_index, touchpad_finger_index),
			pos_x_	{ pos_x },
			pos_y_	{ pos_y }
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventControllerTouchpadMotion::GetName() const
	{
		return "EventControllerTouchpadMotion";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventControllerTouchpadMotion::GetType() const
	{
		return EventType::kControllerTouchpadMotion;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventControllerTouchpadMotion::GetCategoryFlags() const
	{
		return EventCategory::kController | EventCategory::kInput | EventCategory::kTouch;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventControllerTouchpadMotion::ToString() const
	{
		std::stringstream ss;
		ss << GetName();
		ss << ": [" << GetControllerId();
		ss << ", " << GetTouchpadIndex();
		ss << ", " << GetTouchpadFingerIndex();
		ss << ", " << GetX() << ", " << GetY() << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the x position of the touchpad.
	 * 
	 * @return pos_rel_t	The x position of the touchpad.
	 */
	float EventControllerTouchpadMotion::GetX() const
	{
		return pos_x_;
	}
	
	/**
	 * @brief	Get the y position of the touchpad.
	 * 
	 * @return pos_rel_t	The y position of the touchpad.
	 */
	float EventControllerTouchpadMotion::GetY() const
	{
		return pos_y_;
	}

	/**
	 * @brief	Constructs a new ControllerTouchpadPressure event.
	 * 
	 * @param id	The id of the controller that triggered the event.
	 * @param touchpad_index	The index of the touchpad that triggered the event.
	 * @param touchpad_finger_index	The index of the finger that triggered the event.
	 * @param pressure	The pressure of the finger on the touchpad.
	 */
	EventControllerTouchpadPressure::EventControllerTouchpadPressure(
			const controller_id_t id,
			const controller_touchpad_t touchpad_index,
			const controller_touchpad_finger_t touchpad_finger_index,
			const float pressure
		) :
			EventControllerTouchpad(id, touchpad_index, touchpad_finger_index),
			pressure_	{ pressure }
	{}	
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventControllerTouchpadPressure::GetCategoryFlags() const
	{
		return EventCategory::kController | EventCategory::kInput | EventCategory::kTouch;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventControllerTouchpadPressure::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << GetControllerId() << ", " << GetTouchpadIndex() << ", " << GetTouchpadFingerIndex() << ", " << GetPressure() << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the pressure of the finger on the touchpad.
	 * 
	 * @return float	The pressure of the finger on the touchpad.
	 */
	float EventControllerTouchpadPressure::GetPressure() const
	{
		return pressure_;
	}

	/**
	 * @brief	Constructs a new ControllerTouchpadDown event.
	 * 
	 * @param id	The id of the controller that triggered the event.
	 * @param touchpad_index	The index of the touchpad that triggered the event.
	 * @param touchpad_finger_index	The index of the finger that triggered the event.
	 * @param pressure	The pressure of the finger on the touchpad.
	 */
	EventControllerTouchpadDown::EventControllerTouchpadDown(
			const controller_id_t id,
			const controller_touchpad_t touchpad_index,
			const controller_touchpad_finger_t touchpad_finger_index,
			const float pressure
		) :
			EventControllerTouchpadPressure(id, touchpad_index, touchpad_finger_index, pressure)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventControllerTouchpadDown::GetName() const
	{
		return "EventControllerTouchpadDown";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventControllerTouchpadDown::GetType() const
	{
		return EventType::kControllerTouchpadDown;
	}

	/**
	 * @brief	Constructs a new ControllerTouchpadUp event.
	 * 
	 * @param id	The id of the controller that triggered the event.
	 * @param touchpad_index	The index of the touchpad that triggered the event.
	 * @param touchpad_finger_index	The index of the finger that triggered the event.
	 * @param pressure	The pressure of the finger on the touchpad.
	 */
	EventControllerTouchpadUp::EventControllerTouchpadUp(
			const controller_id_t id,
			const controller_touchpad_t touchpad_index,
			const controller_touchpad_finger_t touchpad_finger_index,
			const float pressure
		) :
			EventControllerTouchpadPressure(id, touchpad_index, touchpad_finger_index, pressure)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventControllerTouchpadUp::GetName() const
	{
		return "EventControllerTouchpadUp";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventControllerTouchpadUp::GetType() const
	{
		return EventType::kControllerTouchpadUp;
	}

	/**
	 * @brief	Constructs a new ControllerSensorUpdate event.
	 * 
	 * @param id	The id of the controller that triggered the event.
	 * @param sensor_id	The id of the sensor that triggered the event.
	 * @param data_x	The x data of the sensor.
	 * @param data_y	The y data of the sensor.
	 * @param data_z	The z data of the sensor.
	 */
	EventControllerSensorUpdate::EventControllerSensorUpdate(
		const controller_id_t id,
		const controller_sensor_id_t sensor_id,
		const float data_x,
		const float data_y,
		const float data_z
	) :
		EventController(id),
		sensor_id_	{ sensor_id					},
		data_		{ data_x, data_y, data_z	}
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventControllerSensorUpdate::GetName() const
	{
		return "EventControllerSensorUpdate";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventControllerSensorUpdate::GetType() const
	{
		return EventType::kControllerSensorUpdate;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventControllerSensorUpdate::GetCategoryFlags() const
	{
		return EventCategory::kController | EventCategory::kInput | EventCategory::kSensor;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventControllerSensorUpdate::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << GetControllerId() << ", " << GetSensorId() << ", " << GetDataX() << ", " << GetDataY() << ", " << GetDataZ() << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the id of the sensor that triggered the event.
	 * 
	 * @return controller_sensor_id_t	The id of the sensor that triggered the event.
	 * 
	 */
	controller_sensor_id_t EventControllerSensorUpdate::GetSensorId() const
	{
		return sensor_id_;
	}

	/**
	 * @brief	Get the x data of the sensor.
	 * 
	 * @return float	The x data of the sensor.
	 */
	float EventControllerSensorUpdate::GetDataX() const
	{
		return data_[0];
	}

	/**
	 * @brief	Get the y data of the sensor.
	 * 
	 * @return float	The y data of the sensor.
	 */
	float EventControllerSensorUpdate::GetDataY() const
	{
		return data_[1];
	}

	/**
	 * @brief	Get the z data of the sensor.
	 * 
	 * @return float	The z data of the sensor.
	 */
	float EventControllerSensorUpdate::GetDataZ() const
	{
		return data_[2];
	}
} // Namespace trac