/**
 * @file	event_application.hpp
 * @brief	Application event header file. All events related to the application are defined here.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 * 
*/

#ifndef EVENT_APPLICATION_HPP_
#define EVENT_APPLICATION_HPP_

// Related header include
#include "event.hpp"

namespace trac
{
	/// @brief	Abstract base class for application events.
	class EventApp : public Event
	{
	public:
		// Constructors and destructors
	
		EventApp();
		/// @brief Virtual default destructor.
		virtual ~EventApp() = default;

		/// @brief Explicitly defined default copy constructor.
		EventApp(const EventApp& other) = default;
		/// @brief Explicitly defined default move constructor.
		EventApp(EventApp&& other) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventApp& operator=(const EventApp& other) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventApp& operator=(EventApp&& other) = default;
	
		//Public functions
	
		timestamp_t GetTimestampMs() const override;
	
	private:
		/// The timestamp of the event in milliseconds.
		const timestamp_t timestamp_ms_;
	};

	/// @brief Event class for when the application is being terminated.
	class EventAppTerminating : public EventApp
	{
	public:
		// Constructors and destructors
	
		EventAppTerminating();
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;
	};

	/// @brief	Event class for when the application is starting to run low on memory.
	class EventAppLowMemory : public EventApp
	{
	public:
		// Constructors and destructors
	
		EventAppLowMemory();
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;
	};

	/// @brief	Event class for when the application is entering the background.
	class EventAppEnteringBackground : public EventApp
	{
	public:
		// Constructors and destructors
	
		EventAppEnteringBackground();
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;
	};

	/// @brief	Event class for when the application has entered the background.
	class EventAppEnteredBackground : public EventApp
	{
	public:
		// Constructors and destructors
	
		EventAppEnteredBackground();
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;
	};

	/// @brief	Event class for when the application is entering the foreground.
	class EventAppEnteringForeground : public EventApp
	{
	public:
		// Constructors and destructors
	
		EventAppEnteringForeground();
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;
	};

	/// @brief	Event class for when the application has entered the foreground.
	class EventAppEnteredForeground : public EventApp
	{
	public:
		// Constructors and destructors
	
		EventAppEnteredForeground();
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;
	};

	/// @brief	Event class for the event triggered each application tick.
	class EventAppTick : public EventApp
	{
	public:
		// Constructors and destructors
	
		EventAppTick();
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;
	};

	/// @brief	Application update event.
	class EventAppUpdated : public EventApp
	{
	public:
		// Constructors and destructors
	
		EventAppUpdated();
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;
	};

	/// @brief	Application render event.
	class EventAppRendered : public EventApp
	{
	public:
		// Constructors and destructors
	
		EventAppRendered();
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;
	};

} // Namespace trac

#endif // EVENT_APPLICATION_HPP_ 