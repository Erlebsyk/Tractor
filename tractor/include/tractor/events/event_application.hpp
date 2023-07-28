/**
 * @file	event_application.hpp
 * @brief	Application event header file. All events related to the application are defined here.
 * 
 * @author	Erlend Elias Isachsen
 * @date	26.07.2023
 *
 * @todo	Implement window focus, lost focus and moved events.
*/

#ifndef EVENT_APPLICATION_HPP_
#define EVENT_APPLICATION_HPP_

// Project header includes
#include "event.hpp"

namespace trac
{

	
	/// @brief	Window closed event class. This event is triggered when the window is closed.
	class EventWindowClose : public Event
	{
	public:
		const char* GetName() const override;
		const EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
	};

	/// @brief	Window resize event class. This event is triggered when the window is resized.
	class EventWindowResize : public Event
	{
	public:
		// Constructors and destructors

		EventWindowResize(uint32_t width, uint32_t height);
	
		//Public functions
	
		const char* GetName() const override;
		const EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

	private:
		/// The width of the window.
		const uint32_t width_;
		/// The height of the window.
		const uint32_t height_;
	};

	/// @brief	Window focus event.
	class EventWindowFocus : public Event
	{
	public:
		const char* GetName() const override;
		const EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
	};

	/// @brief	Window lost focus event.
	class EventWindowLostFocus : public Event
	{
	public:
		const char* GetName() const override;
		const EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
	};

	/// @brief	Window moved event.
	class EventWindowMoved : public Event
	{
	public:
		// Constructors and destructors
		
		EventWindowMoved(int32_t x, int32_t y);

		// Public functions

		const char* GetName() const override;
		const EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;

		uint32_t GetX() const;
		uint32_t GetY() const;

	private:
		/// The x position of the window.
		const int32_t x_;
		/// The y position of the window.
		const int32_t y_;
	};

	/// @brief	Application tick event class. This event is triggered every frame.
	class EventAppTick : public Event
	{
	public:
		const char* GetName() const override;
		const EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
	};

	/// @brief	Application update event class.
	class EventAppUpdate : public Event
	{
	public:
		const char* GetName() const override;
		const EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
	};

	/// @brief	Application render event class.
	class EventAppRender : public Event
	{
	public:
		const char* GetName() const override;
		const EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
	};
} // Namespace trac

#endif // EVENT_APPLICATION_HPP_ 