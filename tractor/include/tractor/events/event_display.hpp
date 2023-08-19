/**
 * @file	event_display.hpp
 * @brief	Display event header file. All events related to the display are defined here.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 * 
*/

#ifndef EVENT_DISPLAY_HPP_
#define EVENT_DISPLAY_HPP_

// Related header include
#include "event.hpp"

// External library includes
#include <SDL_video.h>

namespace trac
{
	/// @brief Defines the possible display orientations.
	enum class DisplayOrientation
	{
		kUnknown			= SDL_ORIENTATION_UNKNOWN,
		kLandscape			= SDL_ORIENTATION_LANDSCAPE,
		kPortrait			= SDL_ORIENTATION_PORTRAIT,
		kLandscapeFlipped	= SDL_ORIENTATION_LANDSCAPE_FLIPPED,
		kPortraitFlipped	= SDL_ORIENTATION_PORTRAIT_FLIPPED
	};

	/// Defines a display index type used to identify a display.
	typedef uint32_t display_index_t;

	/// @brief Abstract base class for display events.
	class EventDisplay : public Event
	{
	public:
		// Constructors and destructors
	
		EventDisplay(display_index_t display_index);
		/// @brief Virtual default destructor.
		virtual ~EventDisplay() = default;

		/// @brief Explicitly defined default copy constructor.
		EventDisplay(const EventDisplay& other) = default;
		/// @brief Explicitly defined default move constructor.
		EventDisplay(EventDisplay&& other) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventDisplay& operator=(const EventDisplay& other) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventDisplay& operator=(EventDisplay&& other) = default;

		//Public functions
	
		event_category_t GetCategoryFlags() const override;
		uint64_t GetTimestampMs() const override;

		virtual std::string ToString() const override;

		display_index_t GetDisplayIndex() const;
	
	private:
		/// The index of the display.
		const display_index_t display_index_;
		/// The timestamp of the event in milliseconds.
		const uint64_t timestamp_ms_;
	};

	/// @brief Event for whenever the display orientation changes.
	class EventDisplayOrientation : public EventDisplay
	{
	public:
		// Constructors and destructors
	
		EventDisplayOrientation(display_index_t display_index, DisplayOrientation orientation);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		std::string ToString() const override;
	
		DisplayOrientation GetOrientationData() const;

	private:
		/// The orientation of the display.
		const DisplayOrientation orientation_;
	};

	/// @brief	Event triggered whenever a display is connected.
	class EventDisplayConnected : public EventDisplay
	{
	public:
		// Constructors and destructors
	
		EventDisplayConnected(display_index_t display_index);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Event triggered whenever a display is disconnected.
	class EventDisplayDisconnected : public EventDisplay
	{
	public:
		// Constructors and destructors
	
		EventDisplayDisconnected(display_index_t display_index);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};
} // Namespace trac

#endif // EVENT_DISPLAY_HPP_ 