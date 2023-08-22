/**
 * @file	event_controller.hpp
 * @brief	Controller input event header file. All events related to controller input are defined here.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 * 
*/

#ifndef EVENT_CONTROLLER_HPP_
#define EVENT_CONTROLLER_HPP_

// Related header include
#include "event.hpp"

// External libraries header includes
#include <SDL_events.h>
#include <SDL_gamecontroller.h>
#include <SDL_sensor.h>

namespace trac
{
	/// Defines a controller id type to distinguish between multiple controllers.
	typedef SDL_JoystickID controller_id_t;
	/// Defines a controller button type to distinguish between different buttons on a controller.
	typedef SDL_GameControllerButton controller_button_t;
	/// Defines controller button state
	typedef uint8_t controller_button_state_t;
	/// Defines a type for the controller touchpad index.
	typedef int32_t controller_touchpad_t;
	/// Defines a type for the controller touchpad finger index.
	typedef int32_t controller_touchpad_finger_t;
	/// Defines a type for the controller sensor id.
	typedef SDL_SensorID controller_sensor_id_t;
	/// Defines a type for the controller sensor data.
	typedef float controller_sensor_data_t[3];

	/// @brief Abstract base class for controller events.
	class EventController : public Event
	{
	public:
		// Constructors and destructors
	
		EventController(controller_id_t controller_id);
		/// @brief Virtual default destructor.
		virtual ~EventController() = default;

		/// @brief Explicitly defined default copy constructor.
		EventController(const EventController& other) = default;
		/// @brief Explicitly defined default move constructor.
		EventController(EventController&& other) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventController& operator=(const EventController& other) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventController& operator=(EventController&& other) = default;

		//Public functions

		timestamp_t GetTimestampMs() const override;

		controller_id_t GetControllerId() const;
	
	private:
		/// The timestamp of the event in milliseconds.
		const timestamp_t timestamp_ms_;
		/// The id of the controller that triggered the event.
		const controller_id_t controller_id_;
	};

	/// @brief	Controller axis motion event class. The class contains data about the axis that was moved and the value of the axis.
	class EventControllerAxisMotion : public EventController
	{
	public:
		// Constructors and destructors
	
		EventControllerAxisMotion(controller_id_t id, uint8_t axis, int16_t value);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;

		uint8_t GetAxis() const;
		int16_t GetValue() const;
	
	private:
		/// The axis that was moved.
		const uint8_t axis_;
		/// The value of the axis.
		const int16_t value_;
	};

	/// @brief	Virtual base class for controller button events.
	class EventControllerButton : public EventController
	{
	public:
		// Constructors and destructors
	
		EventControllerButton(controller_id_t id, controller_button_t button, controller_button_state_t button_state);
		/// @brief Virtual default destructor.
		virtual ~EventControllerButton() = default;

		/// @brief Explicitly defined default copy constructor.
		EventControllerButton(const EventControllerButton& other) = default;
		/// @brief Explicitly defined default move constructor.
		EventControllerButton(EventControllerButton&& other) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventControllerButton& operator=(const EventControllerButton& other) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventControllerButton& operator=(EventControllerButton&& other) = default;

		//Public functions

		event_category_t GetCategoryFlags() const override;

		controller_button_t GetButton() const;
		controller_button_state_t GetButtonState() const;

	private:
		/// The button that was pressed.
		const controller_button_t button_;
		/// The state of the button.
		const controller_button_state_t button_state_;
	};

	/// @brief	Controller button pressed event class.
	class EventControllerButtonDown : public EventControllerButton
	{
	public:
		// Constructors and destructors
	
		EventControllerButtonDown(controller_id_t id, controller_button_t button);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		std::string ToString() const override;
	};

	/// @brief	Controller button released event class.
	class EventControllerButtonUp : public EventControllerButton
	{
	public:
		// Constructors and destructors
	
		EventControllerButtonUp(controller_id_t id, controller_button_t button);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		std::string ToString() const override;
	};

	/// @brief	Abstract base class for controller device events.
	class EventControllerDevice : public EventController
	{
	public:
		// Constructors and destructors
	
		EventControllerDevice(controller_id_t id);
		/// @brief Virtual default destructor.
		virtual ~EventControllerDevice() = default;

		/// @brief Explicitly defined default copy constructor.
		EventControllerDevice(const EventControllerDevice& other) = default;
		/// @brief Explicitly defined default move constructor.
		EventControllerDevice(EventControllerDevice&& other) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventControllerDevice& operator=(const EventControllerDevice& other) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventControllerDevice& operator=(EventControllerDevice&& other) = default;
	
		//Public functions
	
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;
	};

	/// @brief	Controller device removed event class.
	class EventControllerDeviceAdded : public EventControllerDevice
	{
	public:
		// Constructors and destructors
	
		EventControllerDeviceAdded(controller_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Controller device removed event class.
	class EventControllerDeviceRemoved : public EventControllerDevice
	{
	public:
		// Constructors and destructors
	
		EventControllerDeviceRemoved(controller_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Controller device remapped event class.
	class EventControllerDeviceRemapped : public EventControllerDevice
	{
	public:
		// Constructors and destructors
	
		EventControllerDeviceRemapped(controller_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Abstract base class for controller touchpad events.
	class EventControllerTouchpad : public EventController
	{
	public:
		// Constructors and destructors
	
		EventControllerTouchpad(controller_id_t id, controller_touchpad_t touchpad_index, controller_touchpad_finger_t touchpad_finger_index);
		/// @brief Virtual default destructor.
		virtual ~EventControllerTouchpad() = default;

		/// @brief Explicitly defined default copy constructor.
		EventControllerTouchpad(const EventControllerTouchpad& other) = default;
		/// @brief Explicitly defined default move constructor.
		EventControllerTouchpad(EventControllerTouchpad&& other) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventControllerTouchpad& operator=(const EventControllerTouchpad& other) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventControllerTouchpad& operator=(EventControllerTouchpad&& other) = default;
	
		//Public functions

		controller_touchpad_t GetTouchpadIndex() const;
		controller_touchpad_finger_t GetTouchpadFingerIndex() const;

	private:
		/// The index of the touchpad that triggered the event.
		const controller_touchpad_t touchpad_index_;
		/// The index of the finger that triggered the event.
		const controller_touchpad_finger_t touchpad_finger_index_;
	};

	/// @brief	Controller touchpad moved event class.
	class EventControllerTouchpadMotion : public EventControllerTouchpad
	{
	public:
		// Constructors and destructors
	
		EventControllerTouchpadMotion(
			controller_id_t id,
			controller_touchpad_t touchpad_index,
			controller_touchpad_finger_t touchpad_finger_index,
			pos_rel_t pos_x,
			pos_rel_t pos_y
		);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;

		pos_rel_t GetX() const;
		pos_rel_t GetY() const;
	
	private:
		/// The relative x position of the touchpad.
		const pos_rel_t pos_x_;
		/// The relative y position of the touchpad.
		const pos_rel_t pos_y_;
	};

	/// @brief	Abstract base class for controller touchpad pressure events.
	class EventControllerTouchpadPressure : public EventControllerTouchpad
	{
	public:
		// Constructors and destructors
	
		EventControllerTouchpadPressure(
			controller_id_t id,
			controller_touchpad_t touchpad_index,
			controller_touchpad_finger_t touchpad_finger_index,
			float pressure
		);
		/// @brief Virtual default destructor.
		virtual ~EventControllerTouchpadPressure() = default;

		/// @brief Explicitly defined default copy constructor.
		EventControllerTouchpadPressure(const EventControllerTouchpadPressure& other) = default;
		/// @brief Explicitly defined default move constructor.
		EventControllerTouchpadPressure(EventControllerTouchpadPressure&& other) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventControllerTouchpadPressure& operator=(const EventControllerTouchpadPressure& other) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventControllerTouchpadPressure& operator=(EventControllerTouchpadPressure&& other) = default;

		//Public functions
	
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;
	
		float GetPressure() const;

	private:
		/// The pressure applied to the touchpad.
		const float pressure_;
	};

	/// @brief	Controller touchpad down event class.
	class EventControllerTouchpadDown : public EventControllerTouchpadPressure
	{
	public:
		// Constructors and destructors
	
		EventControllerTouchpadDown(
			controller_id_t id,
			controller_touchpad_t touchpad_index,
			controller_touchpad_finger_t touchpad_finger_index,
			float pressure
		);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Controller touchpad up event class.
	class EventControllerTouchpadUp : public EventControllerTouchpadPressure
	{
	public:
		// Constructors and destructors
	
		EventControllerTouchpadUp(
			controller_id_t id,
			controller_touchpad_t touchpad_index,
			controller_touchpad_finger_t touchpad_finger_index,
			float pressure
		);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Controller sensor update event class.
	class EventControllerSensorUpdate : public EventController
	{
	public:
		// Constructors and destructors
	
		EventControllerSensorUpdate(
			controller_id_t id,
			controller_sensor_id_t sensor_id,
			float data_x,
			float data_y = 0,
			float data_z = 0
		);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;
	
		controller_sensor_id_t GetSensorId() const;
		float GetDataX() const;
		float GetDataY() const;
		float GetDataZ() const;

	private:
		/// The id of the sensor that triggered the event.
		controller_sensor_id_t sensor_id_;
		/// The data from the sensor.
		controller_sensor_data_t data_;

	};

} // Namespace trac

#endif // EVENT_CONTROLLER_HPP_ 