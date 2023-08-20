/**
 * @file	event_gesture.hpp
 * @brief	Gesture event header file. All events related to gestures are defined here.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 * 
*/

#ifndef EVENT_GESTURE_HPP_
#define EVENT_GESTURE_HPP_

// Related header include
#include "event.hpp"

// External libraries header includes
#include <SDL_gesture.h>
#include <SDL_touch.h>

namespace trac
{
	/// Type definition for gesture IDs.
	typedef SDL_GestureID gesture_id_t;
	/// Type definition for touch IDs.
	typedef SDL_TouchID touch_id_t;

	/// @brief Struct containing gesture data.
	struct GestureData
	{
		GestureData(
			gesture_id_t gesture_id,
			touch_id_t touch_id,
			uint32_t num_fingers,
			float x,
			float y
		);

		/// The timestamp of the gesture.
		timestamp_t timestamp_ms;
		/// The gesture ID.
		gesture_id_t gesture_id;
		/// The touch ID.
		touch_id_t touch_id;
		/// The number of fingers used in the gesture.
		uint32_t num_fingers;
		/// The x-position of the gesture.
		float x;
		/// The y-position of the gesture.
		float y;
	};

	/// @brief Abstract base class for all gesture events.
	class EventGesture : public Event
	{
	public:
		// Constructors and destructors
	
		EventGesture(const GestureData &data);
		/// @brief Virtual default destructor.
		virtual ~EventGesture() = default;

		/// @brief Explicitly defined default copy constructor.
		EventGesture(const EventGesture&) = default;
		/// @brief Explicitly defined default move constructor.
		EventGesture(EventGesture&&) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventGesture& operator=(const EventGesture&) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventGesture& operator=(EventGesture&&) = default;

		//Public functions
	
		event_category_t GetCategoryFlags() const override;
		timestamp_t GetTimestampMs() const override;
		virtual std::string ToString() const override;

		gesture_id_t GetGestureId() const;
		touch_id_t GetTouchId() const;
		uint32_t GetNumFingers() const;
		float GetX() const;
		float GetY() const;

	private:
		/// The gesture data.
		const GestureData data_;
	};

	/// @brief	An event that is triggered when a gesture is recorded.
	class EventDollarGesture : public EventGesture
	{
	public:
		// Constructors and destructors
	
		EventDollarGesture(const GestureData &data, float error);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	
		float GetError() const;

	private:
		/// The error value of the gesture.
		const float error_;
	};

	/// @brief	An event that is triggered when a gesture is recorded.
	class EventDollarRecord : public EventGesture
	{
	public:
		// Constructors and destructors
	
		EventDollarRecord(const GestureData &data, float error);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;

		float GetError() const;

	private:
		/// The error value of the gesture.
		const float error_;
	};

	/// @brief	Multi gesture event class.
	class EventMultiGesture : public EventGesture
	{
	public:
		// Constructors and destructors
	
		EventMultiGesture(const GestureData &data, float d_theta, float d_distance);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		std::string ToString() const override;
	
		float GetDTheta() const;
		float GetDDistance() const;

	private:
		/// The change in angle.
		const float d_theta_;
		/// The change in distance.
		const float d_distance_;
	};

} // Namespace trac

#endif // EVENT_GESTURE_HPP_ 