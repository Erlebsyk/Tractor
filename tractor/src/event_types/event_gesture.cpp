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
#include "event_types/event_gesture.hpp"

// External libraries header includes
#include <SDL_timer.h>

namespace trac
{
	/// @brief Default constructor for gesture data.
	GestureData::GestureData() : 
		timestamp_ms	{ 0		},
		touch_id		{ 0		},
		num_fingers		{ 0		},
		pos_x			{ 0.0f	},
		pos_y			{ 0.0f	}
	{}

	/**
	 * @brief	Constructs new gesture event data.
	 * 
	 * @param touch_id	The touch ID.
	 * @param num_fingers	The number of fingers used in the gesture.
	 * @param pos_x	The x-position of the gesture.
	 * @param pos_y	The y-position of the gesture.
	 */
	GestureData::GestureData(
			const touch_id_t touch_id,
			const uint32_t num_fingers,
			const pos_rel_t pos_x,
			const pos_rel_t pos_y
		) : 
			timestamp_ms	{ SDL_GetTicks64()	},
			touch_id		{ touch_id			},
			num_fingers		{ num_fingers		},
			pos_x			{ pos_x				},
			pos_y			{ pos_y				}
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
		ss << GetName() << ": [" << GetTouchId() << ", " << GetNumFingers() << ", (" << GetPosX() << ", " << GetPosY() << ")]";
		return ss.str();
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
	 * @return pos_rel_t	The x-position of the gesture.
	 */
	pos_rel_t EventGesture::GetPosX() const
	{
		return data_.pos_x;
	}

	/**
	 * @brief	Get the y-position of the gesture.
	 * 
	 * @return pos_rel_t	The y-position of the gesture.
	 */
	pos_rel_t EventGesture::GetPosY() const
	{
		return data_.pos_y;
	}

	/**
	 * @brief	Construct a new event dollar gesture base object.
	 * 
	 * @param data	The gesture data.
	 * @param gesture_id	The ID of the gesture.
	 * @param error	The error value of the gesture.
	 */
	EventDollarGestureBase::EventDollarGestureBase(const GestureData &data, const gesture_id_t gesture_id, const float error) :
		EventGesture(data),
		gesture_id_	{ gesture_id	},
		error_		{ error			}
	{}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventDollarGestureBase::ToString() const
	{
		std::stringstream ss;
		ss << EventGesture::ToString();
		ss << ", [" << GetGestureId() << ", " << GetError() << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the gesture ID of the dollar gesture event.
	 * 
	 * @return gesture_id_t	The gesture ID of the event.
	 */
	gesture_id_t EventDollarGestureBase::GetGestureId() const
	{
		return gesture_id_;
	}

	/**
	 * @brief	Get the error value of the gesture dollar gesture event.
	 * 
	 * @return float	The error value of the gesture event.
	 */
	float EventDollarGestureBase::GetError() const
	{
		return error_;
	}

	/**
	 * @brief	Construct a new event dollar gesture object.
	 * 
	 * @param data	The gesture data.
	 * @param gesture_id	The ID of the gesture.
	 * @param error	The error value of the gesture.
	 */
	EventDollarGesture::EventDollarGesture(const GestureData &data, const gesture_id_t gesture_id, const float error) :
		EventDollarGestureBase(data, gesture_id, error)
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
	 * @brief	Construct a new event dollar record object.
	 * 
	 * @param data	The gesture data.
	 * @param gesture_id	The ID of the gesture.
	 * @param error	The error value of the gesture.
	 */
	EventDollarRecord::EventDollarRecord(const GestureData &data, const gesture_id_t gesture_id, const float error) :
		EventDollarGestureBase(data, gesture_id, error)
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
	 * @brief	Construct a new event multi gesture object.
	 * 
	 * @param data	The gesture data.
	 * @param d_theta	The change in angle of the gesture.
	 * @param d_distance	The change in distance of the gesture.
	 */
	EventMultiGesture::EventMultiGesture(const GestureData &data, const pos_rel_t d_theta, const pos_rel_t d_distance) :
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
		ss << EventGesture::ToString();
		ss << ", [" << GetDTheta() << ", " << GetDDistance() << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the change in angle of the gesture.
	 * 
	 * @return pos_rel_t	The change in angle of the gesture.
	 */
	pos_rel_t EventMultiGesture::GetDTheta() const
	{
		return d_theta_;
	}

	/**
	 * @brief	Get the change in distance of the gesture.
	 * 
	 * @return pos_rel_t	The change in distance of the gesture.
	 */
	pos_rel_t EventMultiGesture::GetDDistance() const
	{
		return d_distance_;
	}
} // namespace trac