/**
 * @file	event_application.cpp
 * @brief	Source file for application events. See event_application.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	26.07.2023
 * 
*/

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "events/event_application.hpp"

namespace trac
{

	/**
	 * @brief	Get the name of the event.
	 * 
	 * @return const char*	The name of the event.
	 */
	const char* EventWindowClose::GetName() const
	{
		return "EventWindowClose";
	}

	/**
	 * @brief	Get the type of the event.
	 * 
	 * @return const EventType	The type of the event.
	 */
	const EventType EventWindowClose::GetType() const
	{
		return EventType::kWindowClose;
	}

	/**
	 * @brief	Get the category flags of the event.
	 * 
	 * @return event_category_t	The category flags of the event.
	 */
	event_category_t EventWindowClose::GetCategoryFlags() const
	{
		return EventCategory::kApplication;
	}

	/**
	 * @brief	Construct a window resize event with a given width and height.
	 * 
	 * @param width	The new width of the window.
	 * @param height	The new height of the window.
	 */
	EventWindowResize::EventWindowResize(const uint32_t width, const uint32_t height) :
		Event(),
		width_	{ width		},
		height_	{ height	}
	{}

	/**
	 * @brief	Get the name of the event.
	 * 
	 * @return const char*	The name of the event.
	 */
	const char* EventWindowResize::GetName() const
	{
		return "EventWindowResize";
	}

	/**
	 * @brief	Get the type of the event.
	 * 
	 * @return const EventType	The type of the event.
	 */
	const EventType EventWindowResize::GetType() const
	{
		return EventType::kWindowResize;
	}

	/**
	 * @brief	Get the category flags of the event.
	 * 
	 * @return event_category_t	The category flags of the event.
	 */
	event_category_t EventWindowResize::GetCategoryFlags() const
	{
		return EventCategory::kApplication;
	}
	
	/**
	 * @brief	Get a string representation of the event, including the name and the width and height of the window.
	 * 
	 * @return std::string	The string representation of the event.
	 */
	std::string EventWindowResize::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << width_ << ", " << height_ << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the width of the window.
	 * 
	 * @return uint32_t	The width of the window.
	 */
	uint32_t EventWindowResize::GetWidth() const
	{
		return width_;
	}

	/**
	 * @brief	Get the height of the window.
	 * 
	 * @return uint32_t	The height of the window.
	 */
	uint32_t EventWindowResize::GetHeight() const
	{
		return height_;
	}

	/**
	 * @brief	Get the name of the event.
	 * 
	 * @return const char*	The name of the event.
	 */
	const char* EventWindowFocus::GetName() const
	{
		return "EventWindowFocus";
	}

	/**
	 * @brief	Get the type of the event.
	 * 
	 * @return const EventType	The type of the event.
	 */
	const EventType EventWindowFocus::GetType() const
	{
		return EventType::kWindowFocus;
	}

	/**
	 * @brief	Get the category flags of the event.
	 * 
	 * @return event_category_t	The category flags of the event.
	 */
	event_category_t EventWindowFocus::GetCategoryFlags() const
	{
		return EventCategory::kApplication;
	}
	
	/**
	 * @brief	Get the name of the event.
	 * 
	 * @return const char*	The name of the event.
	 */
	const char* EventWindowLostFocus::GetName() const
	{
		return "EventWindowLostFocus";
	}

	/**
	 * @brief	Get the type of the event.
	 * 
	 * @return const EventType	The type of the event.
	 */
	const EventType EventWindowLostFocus::GetType() const
	{
		return EventType::kWindowLostFocus;	
	}

	/**
	 * @brief	Get the category flags of the event.
	 * 
	 * @return event_category_t	The category flags of the event.
	 */
	event_category_t EventWindowLostFocus::GetCategoryFlags() const
	{
		return EventCategory::kApplication;
	}
	
	/**
	 * @brief	Construct a window moved event with a given x and y position.
	 * 
	 * @param x	The new horizontal position of the top left corner of the window.
	 * @param y	The new vertical position of the top left corner of the window.
	 * 
	 */
	EventWindowMoved::EventWindowMoved(const int32_t x, const int32_t y) : 
		Event(),
		x_	{ x },
		y_	{ y }
	{}

	/**
	 * @brief	Get the name of the event.
	 * 
	 * @return const char*	The name of the event.
	 * 
	 */
	const char* EventWindowMoved::GetName() const
	{
		return "EventWindowMoved";
	}

	/**
	 * @brief	Get the type of the event.
	 * 
	 * @return const EventType	The type of the event.
	 * 
	 */
	const EventType EventWindowMoved::GetType() const
	{
		return EventType::kWindowMoved;
	}

	/**
	 * @brief	Get the category flags of the event.
	 * 
	 * @return event_category_t	The category flags of the event.
	 */
	event_category_t EventWindowMoved::GetCategoryFlags() const
	{
		return EventCategory::kApplication;
	}

	/**
	 * @brief	Get a string representation of the event, including the name and the new x and y position of the window.
	 * 
	 * @return std::string	The string representation of the event.
	 */
	std::string EventWindowMoved::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << x_ << ", " << y_ << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the x position of the top left corner of the window.
	 * 
	 * @return uint32_t	The x position of the top left corner of the window.
	 */
	uint32_t EventWindowMoved::GetX() const
	{
		return x_;
	}

	/**
	 * @brief	Get the y position of the top left corner of the window.
	 * 
	 * @return uint32_t	The y position of the top left corner of the window.
	 */
	uint32_t EventWindowMoved::GetY() const
	{
		return y_;
	}


	/**
	 * @brief	Get the name of the event.
	 * 
	 * @return const char*	The name of the event.
	 */
	const char* EventAppTick::GetName() const
	{
		return "EventAppTick";
	}

	/**
	 * @brief	Get the type of the event.
	 * 
	 * @return const EventType	The type of the event.
	 */
	const EventType EventAppTick::GetType() const
	{
		return EventType::kAppTick;
	}

	/**
	 * @brief	Get the category flags of the event.
	 * 
	 * @return event_category_t	The category flags of the event.
	 */
	event_category_t EventAppTick::GetCategoryFlags() const
	{
		return EventCategory::kApplication;
	}

	/**
	 * @brief	Get the name of the event.
	 * 
	 * @return const char*	The name of the event.
	 */
	const char* EventAppUpdate::GetName() const
	{
		return "EventAppUpdate";
	}

	/**
	 * @brief	Get the type of the event.
	 * 
	 * @return const EventType	The type of the event.
	 */
	const EventType EventAppUpdate::GetType() const
	{
		return EventType::kAppUpdate;
	}

	/**
	 * @brief	Get the category flags of the event.
	 * 
	 * @return event_category_t	The category flags of the event.
	 */
	event_category_t EventAppUpdate::GetCategoryFlags() const
	{	
		return EventCategory::kApplication;
	}
	
	/**
	 * @brief	Get the name of the event.
	 * 
	 * @return const char*	The name of the event.
	 */
	const char* EventAppRender::GetName() const
	{
		return "EventAppRender";
	}

	/**
	 * @brief	Get the type of the event.
	 * 
	 * @return const EventType	The type of the event.
	 */
	const EventType EventAppRender::GetType() const
	{
		return EventType::kAppRender;
	}

	/**
	 * @brief	Get the category flags of the event.
	 * 
	 * @return event_category_t	The category flags of the event.
	 */
	event_category_t EventAppRender::GetCategoryFlags() const
	{
		return EventCategory::kApplication;
	}

} // Namespace trac