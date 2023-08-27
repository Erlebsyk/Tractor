/**
 * @file	event_touch.hpp
 * @brief	Touch event header file. All events related to touch input are defined here.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 * 
*/

#ifndef EVENT_TOUCH_HPP_
#define EVENT_TOUCH_HPP_

// Related header include
#include "event_base.hpp"

// Project header includes
#include "event_window.hpp"

// External libraries header includes
#include <SDL_touch.h>

namespace trac
{
	/// Type definition for touch IDs.
	typedef SDL_TouchID touch_id_t;
	/// Type definition for finger IDs.
	typedef SDL_FingerID finger_id_t;

	/// @brief Structure containing information about a touch point.
	struct TouchPoint
	{
		TouchPoint();
		TouchPoint(
			finger_id_t finger_id,
			pos_rel_t pos_x,
			pos_rel_t pos_y,
			pos_rel_t dx,
			pos_rel_t dy,
			float pressure
		);

		/// The ID of the finger that produced the event.
		finger_id_t finger_id;
		/// The x-position of the touch event, normalized to the range 0.0 to 1.0.
		pos_rel_t pos_x;
		/// The y-position of the touch event, normalized to the range 0.0 to 1.0.
		pos_rel_t pos_y;
		/// The change in x-direction, normalized to the range -1.0 to 1.0.
		pos_rel_t dx;
		/// The change in y-direction, normalized to the range -1.0 to 1.0.
		pos_rel_t dy;
		/// The pressure of the touch event, normalized to the range 0.0 to 1.0.
		float pressure;
	};

	/// @brief	Abstract base class for touch events.
	class EventTouch : public Event
	{
	public:
		// Constructors and destructors
	
		EventTouch(window_id_t window_id, touch_id_t touch_id, const TouchPoint& touch_point);
		/// @brief Virtual default destructor.
		virtual ~EventTouch() = default;

		/// @brief Explicitly defined default copy constructor.
		EventTouch(const EventTouch&) = default;
		/// @brief Explicitly defined default move constructor.
		EventTouch(EventTouch&&) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventTouch& operator=(const EventTouch&) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventTouch& operator=(EventTouch&&) = default;
	
		//Public functions
	
		event_category_t GetCategoryFlags() const override;
		timestamp_t GetTimestampMs() const override;
		std::string ToString() const override;

		window_id_t GetWindowID() const;
		touch_id_t GetTouchID() const;
		TouchPoint GetTouchPoint() const;

		finger_id_t GetFingerID() const;
		pos_rel_t GetPosX() const;
		pos_rel_t GetPosY() const;
		pos_rel_t GetDX() const;
		pos_rel_t GetDY() const;
		float GetPressure() const;

	private:
		/// The timestamp of the event in milliseconds.
		const timestamp_t timestamp_ms_;
		/// The window ID of the event.
		const window_id_t window_id_;
		/// The id of the touch device that produced the event.
		const touch_id_t touch_id_;
		/// The touch point that produced the event.
		const TouchPoint touch_point_;

	};

	/// @brief	Finger down event.
	class EventFingerDown : public EventTouch
	{
	public:
		// Constructors and destructors
	
		EventFingerDown(window_id_t window_id, touch_id_t touch_id, const TouchPoint& touch_point);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Finger up event.
	class EventFingerUp : public EventTouch
	{
	public:
		// Constructors and destructors
	
		EventFingerUp(window_id_t window_id, touch_id_t touch_id, const TouchPoint& touch_point);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Finger motion event.
	class EventFingerMotion : public EventTouch
	{
	public:
		// Constructors and destructors
	
		EventFingerMotion(window_id_t window_id, touch_id_t touch_id, const TouchPoint& touch_point);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

} // Namespace trac

#endif // EVENT_TOUCH_HPP_ 