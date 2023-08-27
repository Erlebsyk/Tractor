/**
 * @file	event_system.hpp
 * @brief	System event header file. All events related to the system are defined here.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 * 
*/

#ifndef EVENT_SYSTEM_HPP_
#define EVENT_SYSTEM_HPP_

// Related header include
#include "event_base.hpp"

// Standard library header includes
#include <string>

// Project header includes
#include "event_window.hpp"

namespace trac
{

	/// @brief Abstract base class for system events.
	class EventSystem : public Event
	{
	public:
		// Constructors and destructors
	
		EventSystem();
		/// @brief Virtual default destructor.
		virtual ~EventSystem() = default;

		/// @brief Explicitly defined default copy constructor.
		EventSystem(const EventSystem&) = default;
		/// @brief Explicitly defined default move constructor.
		EventSystem(EventSystem&&) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventSystem& operator=(const EventSystem&) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventSystem& operator=(EventSystem&&) = default;
	
		//Public functions
	
		virtual event_category_t GetCategoryFlags() const override;
		timestamp_t GetTimestampMs() const override;

	private:
		/// Timestamp of the event in milliseconds.
		const timestamp_t timestamp_ms_;
	};

	/// @brief User has requested to quit the application.
	class EventQuit : public EventSystem
	{
	public:
		// Constructors and destructors
	
		EventQuit();
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	The system locale has changed.
	class EventLocaleChanged : public EventSystem
	{
	public:
		// Constructors and destructors
	
		EventLocaleChanged();
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief The clipboard contents of the primary selection have changed.
	class EventClipboardUpdate : public EventSystem
	{
	public:
		// Constructors and destructors
	
		EventClipboardUpdate();
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief Abstract base class for drop events.
	class EventDrop : public EventSystem
	{
	public:
		// Constructors and destructors
	
		EventDrop(std::string drop, window_id_t window_id);
		/// @brief Virtual default destructor.
		virtual ~EventDrop() = default;

		/// @brief Explicitly defined default copy constructor.
		EventDrop(const EventDrop&) = default;
		/// @brief Explicitly defined default move constructor.
		EventDrop(EventDrop&&) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventDrop& operator=(const EventDrop&) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventDrop& operator=(EventDrop&&) = default;

		//Public functions
	
		event_category_t GetCategoryFlags() const override;
		virtual std::string ToString() const override;

		std::string GetDrop() const;
		window_id_t GetWindowId() const;

	private:
		/// The name of the file or text that was dropped.
		const std::string drop_;
		/// The id of the window that received the drop event.
		const window_id_t window_id_;
	};

	/// @brief	The user has dropped a file onto the window.
	class EventDropFile : public EventDrop
	{
	public:
		// Constructors and destructors
	
		EventDropFile(std::string file_name, window_id_t window_id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	The user has dropped text onto the window.
	class EventDropText : public EventDrop
	{
	public:
		// Constructors and destructors
	
		EventDropText(std::string text, window_id_t window_id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief A drop with multiple items has begun. The filename/drop is null/blank on the begin and complete events.
	class EventDropBegin : public EventDrop
	{
	public:
		// Constructors and destructors
	
		EventDropBegin(window_id_t window_id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		std::string ToString() const override;
	};

	/// @brief	A drop with multiple items has completed. The filename/drop is null/blank on the begin and complete events.
	class EventDropComplete : public EventDrop
	{
	public:
		// Constructors and destructors
	
		EventDropComplete(window_id_t window_id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		std::string ToString() const override;
	};
} // Namespace trac

#endif // EVENT_SYSTEM_HPP_ 