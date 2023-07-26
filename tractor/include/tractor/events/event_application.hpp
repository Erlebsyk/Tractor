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
	/**
	 * @brief	Window resize event class. This event is triggered when the window is resized.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
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
		uint32_t width_;
		/// The height of the window.
		uint32_t height_;
	};

	/**
	 * @brief	Window closed event class. This event is triggered when the window is closed.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	class EventWindowClose : public Event
	{
	public:
		const char* GetName() const override;
		const EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
	};

	/**
	 * @brief	Application tick event class. This event is triggered every frame.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	class EventAppTick : public Event
	{
	public:
		const char* GetName() const override;
		const EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
	};

	/**
	 * @brief	Application update event class.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	class EventAppUpdate : public Event
	{
	public:
		const char* GetName() const override;
		const EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
	};

	/**
	 * @brief	Application render event class.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	class EventAppRender : public Event
	{
	public:
		const char* GetName() const override;
		const EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
	};
} // Namespace trac

#endif // EVENT_APPLICATION_HPP_ 