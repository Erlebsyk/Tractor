/**
 * @file	event_gesture.cpp
 * @brief	Source file for gesture events. See event_gesture.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 */

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "events/event_gesture.hpp"

// External libraries header includes
#include <SDL_timer.h>

namespace trac
{
	/**
	 * @brief	Constructs new gesture event data.
	 * 
	 * @param gesture_id	The ID of the gesture.
	 * @param touch_id	The touch ID.
	 * @param num_fingers	The number of fingers used in the gesture.
	 * @param x	The x-position of the gesture.
	 * @param y	The y-position of the gesture.
	 */
	GestureData::GestureData(
			const gesture_id_t gesture_id,
			const touch_id_t touch_id,
			const uint32_t num_fingers,
			const float x,
			const float y
		) : 
			timestamp_ms	{ SDL_GetTicks64()	},
			gesture_id		{ gesture_id		},
			touch_id		{ touch_id			},
			num_fingers		{ num_fingers		},
			x				{ x					},
			y				{ y					}
	{}

	/**
	 * @brief	Constructs a new gesture event.
	 * 
	 * @param data	The gesture data.
	 */
	EventGesture::EventGesture(const GestureData &data) :
		Event(),
		data_ { data }
	{}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventGesture::GetCategoryFlags() const
	{
		return EventCategory::kInput;
	}
	
	/**
	 * @brief Get the timestamp of the event in milliseconds.
	 * 
	 * @return timestamp_t The timestamp of the event in milliseconds.
	 */
	timestamp_t EventGesture::GetTimestampMs() const
	{
		return data_.timestamp_ms;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventGesture::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << data_.gesture_id << " " << data_.touch_id << " " << data_.num_fingers << " " << data_.x << " " << data_.y;
		return ss.str();
	}

	/**
	 * @brief	Get the gesture ID.
	 * 
	 * @return gesture_id_t	The gesture ID.
	 */
	gesture_id_t EventGesture::GetGestureId() const
	{
		return data_.gesture_id;
	}

	/**
	 * @brief	Get the touch ID.
	 * 
	 * @return touch_id_t	The touch ID.
	 */
	touch_id_t EventGesture::GetTouchId() const
	{
		return data_.touch_id;
	}

	/**
	 * @brief	Get the number of fingers used in the gesture.
	 * 
	 * @return uint32_t	The number of fingers used in the gesture.
	 */
	uint32_t EventGesture::GetNumFingers() const
	{
		return data_.num_fingers;
	}

	/**
	 * @brief	Get the x-position of the gesture.
	 * 
	 * @return float	The x-position of the gesture.
	 */
	float EventGesture::GetX() const
	{
		return data_.x;
	}

	/**
	 * @brief	Get the y-position of the gesture.
	 * 
	 * @return float	The y-position of the gesture.
	 */
	float EventGesture::GetY() const
	{
		return data_.y;
	}

	/**
	 * @brief	Construct a new event dollar gesture object.
	 * 
	 * @param data	The gesture data.
	 * @param error	The error value of the gesture.
	 */
	EventDollarGesture::EventDollarGesture(const GestureData &data, const float error) :
		EventGesture(data),
		error_ { error }
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventDollarGesture::GetName() const
	{
		return "EventDollarGesture";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventDollarGesture::GetType() const
	{
		return EventType::kDollarGesture;
	}

	/**
	 * @brief	Get the error value of the gesture.
	 * 
	 * @return float	The error value of the gesture.
	 */
	float EventDollarGesture::GetError() const
	{
		return error_;
	}

	/**
	 * @brief	Construct a new event dollar record object.
	 * 
	 * @param data	The gesture data.
	 * @param error	The error value of the gesture.
	 */
	EventDollarRecord::EventDollarRecord(const GestureData &data, const float error) :
		EventGesture(data),
		error_ { error }
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventDollarRecord::GetName() const
	{
		return "EventDollarRecord";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventDollarRecord::GetType() const
	{
		return EventType::kDollarRecord;
	}
	
	/**
	 * @brief	Get the error value of the gesture.
	 * 
	 * @return float	The error value of the gesture.
	 */
	float EventDollarRecord::GetError() const
	{
		return error_;
	}

	/**
	 * @brief	Construct a new event multi gesture object.
	 * 
	 * @param data	The gesture data.
	 * @param d_theta	The change in angle of the gesture.
	 * @param d_distance	The change in distance of the gesture.
	 */
	EventMultiGesture::EventMultiGesture(const GestureData &data, const float d_theta, const float d_distance) :
		EventGesture(data),
		d_theta_	{ d_theta		},
		d_distance_	{ d_distance	}
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventMultiGesture::GetName() const
	{
		return "EventMultiGesture";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventMultiGesture::GetType() const
	{
		return EventType::kMultiGesture;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventMultiGesture::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << GetGestureId() << " " << GetTouchId() << " " << GetNumFingers() << " " << GetX() << " " << GetY();
		ss << " " << GetDTheta() << " " << GetDDistance();
		return ss.str();
	}

	/**
	 * @brief	Get the change in angle of the gesture.
	 * 
	 * @return float	The change in angle of the gesture.
	 */
	float EventMultiGesture::GetDTheta() const
	{
		return d_theta_;
	}

	/**
	 * @brief	Get the change in distance of the gesture.
	 * 
	 * @return float	The change in distance of the gesture.
	 */
	float EventMultiGesture::GetDDistance() const
	{
		return d_distance_;
	}
} // namespace trac