/**
 * @file	event_touch.cpp
 * @brief	Source file for touch events. See event_touch.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 */

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "events/event_touch.hpp"

// External libraries header includes
#include <SDL_touch.h>
#include <SDL_timer.h>

namespace trac
{
	
	/// @brief	Default constructor for the TouchPoint struct. All values are initialized to 0.
	TouchPoint::TouchPoint() : 
		finger_id	{ 0 },
		pos_x		{ 0.0f },
		pos_y		{ 0.0f },
		dx			{ 0.0f },
		dy			{ 0.0f },
		pressure	{ 0.0f }
	{}

	/**
	 * @brief	Construct a new TouchPoint object, containing information about a touch point. This constructor expects all inputs to be properly normalized
	 * 			beforehand, and do not perform any "sanity" or bounds checking.
	 * 
	 * @param finger_id	The ID of the finger that produced the event.
	 * @param pos_x	The x-position of the touch event, normalized to the range 0.0 to 1.0.
	 * @param pos_y	The y-position of the touch event, normalized to the range 0.0 to 1.0.
	 * @param dx	The change in x-direction, normalized to the range -1.0 to 1.0.
	 * @param dy	The change in y-direction, normalized to the range -1.0 to 1.0.
	 * @param pressure	The pressure of the touch event, normalized to the range 0.0 to 1.0.
	 */
	TouchPoint::TouchPoint(
			const finger_id_t finger_id,
			const pos_rel_t pos_x,
			const pos_rel_t pos_y,
			const pos_rel_t dx,
			const pos_rel_t dy,
			const float pressure
		) : 
			finger_id	{ finger_id },
			pos_x		{ pos_x },
			pos_y		{ pos_y },
			dx			{ dx },
			dy			{ dy },
			pressure	{ pressure }
	{}

	/**
	 * @brief	Construct a new EventTouch event.
	 * 
	 * @param window_id	The ID of the window that generated the touch event.
	 * @param touch_id	The ID of the touch device that generated the touch event.
	 * @param touch_point	The touch point containing the data of the touch event.
	 */
	EventTouch::EventTouch(const window_id_t window_id, const touch_id_t touch_id, const TouchPoint& touch_point) :
		Event(),
		timestamp_ms_	{ SDL_GetTicks64()	},
		window_id_		{ window_id			},
		touch_id_		{ touch_id			},
		touch_point_	{ touch_point		}
	{}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventTouch::GetCategoryFlags() const
	{
		return EventCategory::kTouch | EventCategory::kInput;
	}
	
	/**
	 * @brief Get the timestamp of the event in milliseconds.
	 * 
	 * @return timestamp_t The timestamp of the event in milliseconds.
	 */
	timestamp_t EventTouch::GetTimestampMs() const
	{
		return timestamp_ms_;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventTouch::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << GetWindowID() << ", " << GetTouchID() << ", ";
		ss << GetFingerID() << ", (" << GetPosX() << ", " << GetPosY() << "), (" << GetDX() << ", " << GetDY() << "), " << GetPressure();
		ss << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the ID of the window that the event occurred in.
	 * 
	 * @return window_id_t	The ID of the window that the event occurred in.
	 */
	window_id_t EventTouch::GetWindowID() const
	{
		return window_id_;
	}

	/**
	 * @brief	Get the ID of the touch device that the event occurred on.
	 * 
	 * @return touch_id_t	The ID of the touch device that the event occurred on.
	 */
	touch_id_t EventTouch::GetTouchID() const
	{
		return touch_id_;
	}

	/**
	 * @brief	Get the touch point data for the event.
	 * 
	 * @return TouchPoint	The touch point data for the event.
	 */
	TouchPoint EventTouch::GetTouchPoint() const
	{
		return touch_point_;
	}

	/**
	 * @brief	Get the ID of the finger that produced the event.
	 * 
	 * @return finger_id_t	The ID of the finger that produced the event.
	 */
	finger_id_t EventTouch::GetFingerID() const
	{
		return touch_point_.finger_id;
	}

	/**
	 * @brief	Get the x-position of the touch event, normalized to the range 0.0 to 1.0.
	 * 
	 * @return pos_rel_t	The x-position of the touch event, normalized to the range 0.0 to 1.0.
	 */
	pos_rel_t EventTouch::GetPosX() const
	{
		return touch_point_.pos_x;
	}

	/**
	 * @brief	Get the y-position of the touch event, normalized to the range 0.0 to 1.0.
	 * 
	 * @return pos_rel_t	The y-position of the touch event, normalized to the range 0.0 to 1.0.
	 */
	pos_rel_t EventTouch::GetPosY() const
	{
		return touch_point_.pos_y;
	}

	/**
	 * @brief	Get the change in x-direction, normalized to the range -1.0 to 1.0.
	 * 
	 * @return pos_rel_t	The change in x-direction, normalized to the range -1.0 to 1.0.
	 */
	pos_rel_t EventTouch::GetDX() const
	{
		return touch_point_.dx;
	}

	/**
	 * @brief	Get the change in y-direction, normalized to the range -1.0 to 1.0.
	 * 
	 * @return pos_rel_t	The change in y-direction, normalized to the range -1.0 to 1.0.
	 */
	pos_rel_t EventTouch::GetDY() const
	{
		return touch_point_.dy;
	}

	/**
	 * @brief	Get the pressure of the touch event, normalized to the range 0.0 to 1.0.
	 * 
	 * @return float	The pressure of the touch event, normalized to the range 0.0 to 1.0.
	 */
	float EventTouch::GetPressure() const
	{
		return touch_point_.pressure;
	}

	/**
	 * @brief	Construct a new EventFingerDown event.
	 * 
	 * @param window_id	The ID of the window that generated the touch event.
	 * @param touch_id	The ID of the touch device that generated the touch event.
	 * @param touch_point	The touch point containing the data of the touch event.
	 */
	EventFingerDown::EventFingerDown(const window_id_t window_id, const touch_id_t touch_id, const TouchPoint& touch_point) :
		EventTouch(window_id, touch_id, touch_point)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventFingerDown::GetName() const
	{
		return "EventFingerDown";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventFingerDown::GetType() const
	{
		return EventType::kFingerDown;
	}

	/**
	 * @brief	Construct a new EventFingerUp event.
	 * 
	 * @param window_id	The ID of the window that generated the touch event.
	 * @param touch_id	The ID of the touch device that generated the touch event.
	 * @param touch_point	The touch point containing the data of the touch event.
	 */
	EventFingerUp::EventFingerUp(const window_id_t window_id, const touch_id_t touch_id, const TouchPoint& touch_point) :
		EventTouch(window_id, touch_id, touch_point)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventFingerUp::GetName() const
	{
		return "EventFingerUp";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventFingerUp::GetType() const
	{
		return EventType::kFingerUp;
	}

	/**
	 * @brief	Construct a new EventFingerMotion event.
	 * 
	 * @param window_id	The ID of the window that generated the touch event.
	 * @param touch_id	The ID of the touch device that generated the touch event.
	 * @param touch_point	The touch point containing the data of the touch event.
	 */
	EventFingerMotion::EventFingerMotion(const window_id_t window_id, const touch_id_t touch_id, const TouchPoint& touch_point) :
		EventTouch(window_id, touch_id, touch_point)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventFingerMotion::GetName() const
	{
		return "EventFingerMotion";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventFingerMotion::GetType() const
	{
		return EventType::kFingerMotion;
	}
} // namespace trac
