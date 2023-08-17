/**
 * @file	event_mouse.cpp
 * @brief	Source file for mouse button events. See event_mouse.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	26.07.2023
 * 
*/

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "events/event_mouse.hpp"

namespace trac
{
	/**
	 * @brief	Construct a mouse movement event.
	 * 
	 * @param x	The x position of the mouse cursor.
	 * @param y	The y position of the mouse cursor.
	 */
	EventMouseMovement::EventMouseMovement(const float x, const float y) :
		Event(),
		 x_	{x},
		 y_	{y}
	{}

	/**
	 * @brief	Get the name of the event.
	 * 
	 * @return const char*	The name of the event.
	 */
	const char* EventMouseMovement::GetName() const
	{
		return "EventMouseMovement";
	};

	/**
	 * @brief	Get the type of the event.
	 * 
	 * @return const EventType	The type of the event.
	 */
	const EventType EventMouseMovement::GetType() const
	{
		return EventType::kMouseMotion;
	}

	/**
	 * @brief	Get the category flags of the event.
	 * 
	 * @return event_category_t	The category flags of the event.
	 */
	event_category_t EventMouseMovement::GetCategoryFlags() const
	{
		return (EventCategory::kMouse) | (EventCategory::kInput);
	}

	/**
	 * @brief	Create a string representation of the event.
	 * 
	 * @return std::string	A string representation of the event.
	 */
	std::string EventMouseMovement::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << x_ << ", " << y_ << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the x position of the mouse cursor.
	 * 
	 * @return float	The x position of the mouse cursor.
	 */
	float EventMouseMovement::GetX() const
	{
		return x_;
	}

	/**
	 * @brief	Get the y position of the mouse cursor.
	 * 
	 * @return float	The y position of the mouse cursor.
	 */
	float EventMouseMovement::GetY() const
	{
		return y_;
	}

	/**
	 * @brief	Construct a new mouse scrolled event.
	 * 
	 * @param offset_x	The x offset of the mouse scrolled event.
	 * @param offset_y	The y offset of the mouse scrolled event.
	 */
	EventMouseScrolled::EventMouseScrolled(const float offset_x, const float offset_y) :
		Event(),
		offset_x_	{ offset_x },
		offset_y_	{ offset_y }
	{}

	/**
	 * @brief	Get the name of the event.
	 * 
	 * @return const char*	The name of the event.
	 */
	const char* EventMouseScrolled::GetName() const
	{
		return "EventMouseScrolled";
	}
	
	/**
	 * @brief	Get the type of the event.
	 * 
	 * @return const EventType	The type of the event.
	 */
	const EventType EventMouseScrolled::GetType() const
	{
		return EventType::kMouseWheel;
	}
	
	/**
	 * @brief	Get the category flags of the event.
	 * 
	 * @return event_category_t	The category flags of the event.
	 */
	event_category_t EventMouseScrolled::GetCategoryFlags() const
	{
		return (EventCategory::kMouse) | (EventCategory::kInput);
	}
	
	/**
	 * @brief	Create a string representation of the event.
	 * 
	 * @return std::string	A string representation of the event.
	 */
	std::string EventMouseScrolled::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << offset_x_ << ", " << offset_y_ << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the x offset of the mouse scroll wheel.
	 * 
	 * @return float	The x offset of the mouse scroll wheel.
	 */
	float EventMouseScrolled::GetOffsetX() const
	{
		return offset_x_;
	}

	/**
	 * @brief	Get the y offset of the mouse scroll wheel.
	 * 
	 * @return float	The y offset of the mouse scroll wheel.
	 */
	float EventMouseScrolled::GetOffsetY() const
	{
		return offset_y_;
	}

	/**
	 * @brief	Get the category flags of the event.
	 * 
	 * @return event_category_t	The category flags of the event.
	 */
	event_category_t EventMouseButton::GetCategoryFlags() const
	{
		return (EventCategory::kMouse) | (EventCategory::kInput) | EventCategory::kMouseButton;
	}
	
	/**
	 * @brief	Create a string representation of the event.
	 * 
	 * @return std::string	The string representation of the event.
	 */
	std::string EventMouseButton::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": " << (uint16_t)button_;
		return ss.str();
	}

	/**
	 * @brief	Get the mouse button that triggered the event.
	 * 
	 * @return MouseCode	The mouse button that triggered the event.
	 */
	MouseCode EventMouseButton::GetButton() const
	{
		return button_;
	}

	/**
	 * @brief	Construct a new mouse button event.
	 * 
	 * @param button	The mouse button that triggered the event.
	 */
	EventMouseButton::EventMouseButton(const MouseCode button) :
		Event(),
		button_	{ button }
	{}

	/**
	 * @brief	Construct a new mouse button pressed event.
	 * 
	 * @param button	The mouse button that triggered the event.
	 */
	EventMouseButtonPress::EventMouseButtonPress(const MouseCode button) :
		EventMouseButton(button)
	{}

	/**
	 * @brief	Get the name of the event.
	 * 
	 * @return const char*	The name of the event.
	 */
	const char* EventMouseButtonPress::GetName() const
	{
		return "EventMouseButtonPress";
	}
	
	/**
	 * @brief	Get the type of the event.
	 * 
	 * @return const EventType	The type of the event.
	 */
	const EventType EventMouseButtonPress::GetType() const
	{
		return EventType::kMouseButtonUp;
	}

	/**
	 * @brief	Construct a new mouse button released event.
	 * 
	 * @param button	The mouse button that triggered the event.
	 */
	EventMouseButtonRelease::EventMouseButtonRelease(const MouseCode button) :
		EventMouseButton(button)
	{}

	/**
	 * @brief	Get the name of the event.
	 * 
	 * @return const char*	The name of the event.
	 */
	const char* EventMouseButtonRelease::GetName() const
	{
		return "EventMouseButtonRelease";
	}
	
	/**
	 * @brief	Get the type of the event.
	 * 
	 * @return const EventType	The type of the event.
	 */
	const EventType EventMouseButtonRelease::GetType() const
	{
		return EventType::kMouseButtonDown;
	}
} // Namespace trac