/**
 * @file	event_application.cpp
 * @brief	Source file for application events. See event_application.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 * 
*/

// Precompiled header include
#include "tractor_pch.hpp"

// External libraries header includes
#include "SDL_timer.h" // Used to get the timestamp of the event

// Related header include
#include "event_types/event_application.hpp"

namespace trac
{
	/// @brief Constructs a new App event.
	EventApp::EventApp() : 
		Event(),
		timestamp_ms_{ SDL_GetTicks64() }
	{}

	/**
	 * @brief	Get the timestamp of the event in milliseconds.
	 * 
	 * @return timestamp_t	The timestamp of the event in milliseconds.
	 */
	timestamp_t EventApp::GetTimestampMs() const
	{
		return timestamp_ms_;
	}

	/// @brief Constructs a new AppTerminating event.
	EventAppTerminating::EventAppTerminating() : 
		EventApp()
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventAppTerminating::GetName() const
	{
		return "EventAppTerminating";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventAppTerminating::GetType() const
	{
		return EventType::kAppTerminating;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventAppTerminating::GetCategoryFlags() const
	{
		return EventCategory::kApplication;
	}

	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventAppTerminating::ToString() const
	{
		std::stringstream ss;
		ss << GetName();
		return ss.str();
	}

	/// @brief Constructs a new AppLowMemory event.
	EventAppLowMemory::EventAppLowMemory() :
		EventApp()
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventAppLowMemory::GetName() const
	{
		return "EventAppLowMemory";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventAppLowMemory::GetType() const
	{
		return EventType::kAppLowMemory;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventAppLowMemory::GetCategoryFlags() const
	{
		return EventCategory::kApplication;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventAppLowMemory::ToString() const
	{
		std::stringstream ss;
		ss << GetName();
		return ss.str();
	}

	/// @brief Constructs a new AppEnteringBackground event.
	EventAppEnteringBackground::EventAppEnteringBackground() :
		EventApp()
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventAppEnteringBackground::GetName() const
	{
		return "EventAppEnteringBackground";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventAppEnteringBackground::GetType() const
	{
		return EventType::kAppEnteringBackground;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventAppEnteringBackground::GetCategoryFlags() const
	{
		return EventCategory::kApplication;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventAppEnteringBackground::ToString() const
	{
		std::stringstream ss;
		ss << GetName();
		return ss.str();
	}

	/// @brief Constructs a new AppEnteredBackground event.
	EventAppEnteredBackground::EventAppEnteredBackground() :
		EventApp()
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventAppEnteredBackground::GetName() const
	{
		return "EventAppEnteredBackground";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventAppEnteredBackground::GetType() const
	{
		return EventType::kAppEnteredBackground;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventAppEnteredBackground::GetCategoryFlags() const
	{
		return EventCategory::kApplication;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventAppEnteredBackground::ToString() const
	{
		std::stringstream ss;
		ss << GetName();
		return ss.str();
	}

	/// @brief Constructs a new AppEnteringForeground event.
	EventAppEnteringForeground::EventAppEnteringForeground() :
		EventApp()
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventAppEnteringForeground::GetName() const
	{
		return "EventAppEnteringForeground";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventAppEnteringForeground::GetType() const
	{
		return EventType::kAppEnteringForeground;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventAppEnteringForeground::GetCategoryFlags() const
	{
		return EventCategory::kApplication;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventAppEnteringForeground::ToString() const
	{
		std::stringstream ss;
		ss << GetName();
		return ss.str();
	}

	/// @brief Constructs a new AppEnteredForeground event.
	EventAppEnteredForeground::EventAppEnteredForeground() :
		EventApp()
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventAppEnteredForeground::GetName() const
	{
		return "EventAppEnteredForeground";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventAppEnteredForeground::GetType() const
	{
		return EventType::kAppEnteredForeground;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventAppEnteredForeground::GetCategoryFlags() const
	{
		return EventCategory::kApplication;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventAppEnteredForeground::ToString() const
	{
		std::stringstream ss;
		ss << GetName();
		return ss.str();
	}

	/// @brief Constructs a new AppTick event.
	EventAppTick::EventAppTick() :
		EventApp()
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventAppTick::GetName() const
	{
		return "EventAppTick";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventAppTick::GetType() const
	{
		return EventType::kAppTick;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventAppTick::GetCategoryFlags() const
	{
		return EventCategory::kApplication;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventAppTick::ToString() const
	{
		std::stringstream ss;
		ss << GetName();
		return ss.str();
	}

	/// @brief Constructs a new AppUpdated event.
	EventAppUpdated::EventAppUpdated() :
		EventApp()
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventAppUpdated::GetName() const
	{
		return "EventAppUpdated";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventAppUpdated::GetType() const
	{
		return EventType::kAppUpdated;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventAppUpdated::GetCategoryFlags() const
	{
		return EventCategory::kApplication;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventAppUpdated::ToString() const
	{
		std::stringstream ss;
		ss << GetName();
		return ss.str();
	}

	/// @brief Constructs a new AppRendered event.
	EventAppRendered::EventAppRendered() :
		EventApp()
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventAppRendered::GetName() const
	{
		return "EventAppRendered";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventAppRendered::GetType() const
	{
		return EventType::kAppRendered;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventAppRendered::GetCategoryFlags() const
	{
		return EventCategory::kApplication | EventCategory::kDisplay;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventAppRendered::ToString() const
	{
		std::stringstream ss;
		ss << GetName();
		return ss.str();
	}
} // Namespace trac