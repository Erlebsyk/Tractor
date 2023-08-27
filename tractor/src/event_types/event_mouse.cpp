/**
 * @file	event_mouse.cpp
 * @brief	Source file for mouse events. See event_mouse.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 */

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "event_types/event_mouse.hpp"

// External libraries header includes
#include <SDL_mouse.h>
#include <SDL_timer.h>

namespace trac
{
	/**
	 * @brief	Construct a new mouse event.
	 * 
	 * @param mouse_id	The ID of the mouse that triggered the event.
	 * @param window_id	The ID of the window that the event occurred in.
	 * @param pos_x	The x-position of the mouse cursor in the window.
	 * @param pos_y	The y-position of the mouse cursor in the window.
	 */
	EventMouse::EventMouse(
			const mouse_id_t mouse_id,
			const window_id_t window_id,
			const pos_pixel_t pos_x,
			const pos_pixel_t pos_y
		) :
			Event(),
			timestamp_ms_	{ SDL_GetTicks64()	},
			mouse_id_		{ mouse_id			},
			window_id_		{ window_id			},
			pos_x_			{ pos_x				},
			pos_y_			{ pos_y				}
	{}
	
	/**
	 * @brief Get the timestamp of the event in milliseconds.
	 * 
	 * @return timestamp_t The timestamp of the event in milliseconds.
	 */
	timestamp_t EventMouse::GetTimestampMs() const
	{
		return timestamp_ms_;
	}

	/**
	 * @brief	Get a string representation of the event.
	 * 
	 * @return std::string	A string representation of the event.
	 */
	std::string EventMouse::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << GetMouseID() << ", " << GetWindowID() << ", " << GetPosX() << ", " << GetPosY() << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the mouse ID of the event.
	 * 
	 * @return mouse_id_t	The mouse ID of the event.
	 */
	mouse_id_t EventMouse::GetMouseID() const
	{
		return mouse_id_;
	}

	/**
	 * @brief	Get the window ID of the event.
	 * 
	 * @return window_id_t	The window ID of the event.
	 */
	window_id_t EventMouse::GetWindowID() const
	{
		return window_id_;
	}

	/**
	 * @brief	Get the x-position of the mouse in the window.
	 * 
	 * @return pos_pixel_t	The x-position of the mouse in the window.
	 */
	pos_pixel_t EventMouse::GetPosX() const
	{
		return pos_x_;
	}

	/**
	 * @brief	Get the y-position of the mouse in the window.
	 * 
	 * @return pos_pixel_t	The y-position of the mouse in the window.
	 */
	pos_pixel_t EventMouse::GetPosY() const
	{
		return pos_y_;
	}

	/**
	 * @brief	Construct a new mouse motion event.
	 * 
	 * @param mouse_id	The ID of the mouse that triggered the event.
	 * @param window_id	The ID of the window that the event occurred in.
	 * @param pos_x	The x-position of the mouse cursor in the window.
	 * @param pos_y	The y-position of the mouse cursor in the window.
	 * @param button_state	The current state of the mouse buttons.
	 * @param rel_x	The relative motion of the mouse in x-direction.
	 * @param rel_y	The relative motion of the mouse in y-direction.
	 */
	EventMouseMotion::EventMouseMotion(
		const mouse_id_t mouse_id,
		const window_id_t window_id,
		const pos_pixel_t pos_x,
		const pos_pixel_t pos_y,
		const mouse_button_state_t button_state,
		const pos_pixel_t rel_x,
		const pos_pixel_t rel_y
	) :
		EventMouse(mouse_id, window_id, pos_x, pos_y),
		button_state_	{ button_state	},
		dx_			{ rel_x			},
		dy_			{ rel_y			}
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventMouseMotion::GetName() const
	{
		return "EventMouseMotion";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventMouseMotion::GetType() const
	{
		return EventType::kMouseMotion;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventMouseMotion::GetCategoryFlags() const
	{
		return EventCategory::kMouse | EventCategory::kInput;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventMouseMotion::ToString() const
	{
		std::stringstream ss;
		ss << EventMouse::ToString();
		ss << ", [" << GetButtonState() << ", (" << GetRelX() << ", " << GetRelY() << ")]";
		return ss.str();
	}

	/**
	 * @brief	Get the current state of the mouse buttons as a bitmask.
	 * 
	 * @return mouse_button_state_t	The current state of the mouse buttons.
	 */
	mouse_button_state_t EventMouseMotion::GetButtonState() const
	{
		return button_state_;
	}

	/**
	 * @brief	Check if a specific mouse button is pressed.
	 * 
	 * @param button	The mouse button to check.
	 * @return bool	Whether the mouse button is pressed.
	 * @retval true	The mouse button is pressed.
	 * @retval false	The mouse button is not pressed.
	 */
	bool EventMouseMotion::IsButtonPressed(const MouseButton button) const
	{
		return (button_state_ & SDL_BUTTON((int)(button))) != 0;
	}

	/**
	 * @brief	Check if multiple mouse buttons are pressed.
	 * 
	 * @param button_bitmask	The bitmask of the mouse buttons to check.
	 * @return bool	Whether the mouse buttons are pressed.
	 * @retval true	All the mouse buttons are pressed.
	 * @retval false	Not all the mouse buttons are pressed.
	 */
	bool EventMouseMotion::AreButtonsPressed(const mouse_button_state_t button_bitmask) const
	{
		return (button_state_ & button_bitmask) != 0;
	}

	/**
	 * @brief	Get the relative motion of the mouse in x-direction.
	 * 
	 * @return pos_pixel_t	The relative motion of the mouse in x-direction.
	 */
	pos_pixel_t EventMouseMotion::GetRelX() const
	{
		return dx_;
	}

	/**
	 * @brief	Get the relative motion of the mouse in y-direction.
	 * 
	 * @return pos_pixel_t	The relative motion of the mouse in y-direction.
	 */
	pos_pixel_t EventMouseMotion::GetRelY() const
	{
		return dy_;
	}
	
	/**
	 * @brief	Construct a new mouse button event.
	 * 
	 * @param mouse_id	The ID of the mouse that triggered the event.
	 * @param window_id	The ID of the window that the event occurred in.
	 * @param pos_x	The x-position of the mouse cursor in the window.
	 * @param pos_y	The y-position of the mouse cursor in the window.
	 * @param button	The button that triggered the event.
	 * 
	 */
	EventMouseButton::EventMouseButton(
		const mouse_id_t mouse_id,
		const window_id_t window_id,
		const pos_pixel_t pos_x,
		const pos_pixel_t pos_y,
		const MouseButton button
	) :
		EventMouse(mouse_id, window_id, pos_x, pos_y),
		button_ { button }
	{}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventMouseButton::GetCategoryFlags() const
	{
		return EventCategory::kMouse | EventCategory::kInput | EventCategory::kButton;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventMouseButton::ToString() const
	{
		std::stringstream ss;
		ss << EventMouse::ToString();
		ss << ", [";
		if(GetButton() == MouseButton::kLeft)
			ss << "left";
		else if(GetButton() == MouseButton::kMiddle)
			ss << "middle";
		else if(GetButton() == MouseButton::kRight)
			ss << "right";
		else if(GetButton() == MouseButton::kX1)
			ss << "x1";
		else if(GetButton() == MouseButton::kX2)
			ss << "x2";
		else
			ss << "unknown";
		ss << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the mouse button that triggered the event.
	 * 
	 * @return MouseButton	The mouse button that triggered the event.
	 */
	MouseButton EventMouseButton::GetButton() const
	{
		return button_;
	}

	/**
	 * @brief	Construct a new mouse button release event.
	 * 
	 * @param mouse_id	The ID of the mouse that triggered the event.
	 * @param window_id	The ID of the window that the event occurred in.
	 * @param pos_x	The x-position of the mouse cursor in the window.
	 * @param pos_y	The y-position of the mouse cursor in the window.
	 * @param button	The button that triggered the event.
	 */
	EventMouseButtonDown::EventMouseButtonDown(
		const mouse_id_t mouse_id,
		const window_id_t window_id,
		const pos_pixel_t pos_x,
		const pos_pixel_t pos_y,
		const MouseButton button
	) :
		EventMouseButton(mouse_id, window_id, pos_x, pos_y, button)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventMouseButtonDown::GetName() const
	{
		return "EventMouseButtonDown";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventMouseButtonDown::GetType() const
	{
		return EventType::kMouseButtonDown;
	}

	/**
	 * @brief	Construct a new mouse button press event.
	 * 
	 * @param mouse_id	The ID of the mouse that triggered the event.
	 * @param window_id	The ID of the window that the event occurred in.
	 * @param pos_x	The x-position of the mouse cursor in the window.
	 * @param pos_y	The y-position of the mouse cursor in the window.
	 * @param button	The button that triggered the event.
	 */
	EventMouseButtonUp::EventMouseButtonUp(
		const mouse_id_t mouse_id,
		const window_id_t window_id,
		const pos_pixel_t pos_x,
		const pos_pixel_t pos_y,
		const MouseButton button
	) :
		EventMouseButton(mouse_id, window_id, pos_x, pos_y, button)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventMouseButtonUp::GetName() const
	{
		return "EventMouseButtonUp";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventMouseButtonUp::GetType() const
	{
		return EventType::kMouseButtonUp;
	}

	/**
	 * @brief	Construct a new mouse button click event.
	 * 
	 * @param mouse_id	The ID of the mouse that triggered the event.
	 * @param window_id	The ID of the window that the event occurred in.
	 * @param pos_x	The x-position of the mouse cursor in the window.
	 * @param pos_y	The y-position of the mouse cursor in the window.
	 * @param button	The button that triggered the event.
	 * @param clicks	The number of clicks that triggered the event.
	 */
	EventMouseButtonClicked::EventMouseButtonClicked(
		const mouse_id_t mouse_id,
		const window_id_t window_id,
		const pos_pixel_t pos_x,
		const pos_pixel_t pos_y,
		const MouseButton button,
		const uint32_t clicks
	) :
		EventMouseButton(mouse_id, window_id, pos_x, pos_y, button),
		clicks_ { clicks }
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventMouseButtonClicked::GetName() const
	{
		return "EventMouseButtonClicked";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventMouseButtonClicked::GetType() const
	{
		return EventType::kMouseButtonClicked;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventMouseButtonClicked::ToString() const
	{
		std::stringstream ss;
		ss << EventMouseButton::ToString();
		ss << ", [" << GetClicks() << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the number of clicks that triggered the event.
	 * 
	 * @return uint32_t	The number of clicks that triggered the event.
	 */
	uint32_t EventMouseButtonClicked::GetClicks() const
	{
		return clicks_;
	}

	/**
	 * @brief	Construct a new mouse wheel event.
	 * 
	 * @param mouse_id	The ID of the mouse that triggered the event.
	 * @param window_id	The ID of the window that the event occurred in.
	 * @param pos_x	The x-position of the mouse cursor in the window.
	 * @param pos_y	The y-position of the mouse cursor in the window.
	 * @param scroll_x	The horizontal scroll amount.
	 * @param scroll_y	The vertical scroll amount.
	 * @param flipped	Whether the scroll direction is flipped.
	 */
	EventMouseWheel::EventMouseWheel(
		const mouse_id_t mouse_id,
		const window_id_t window_id,
		const pos_pixel_t pos_x,
		const pos_pixel_t pos_y,
		const pos_pixel_t scroll_x,
		const pos_pixel_t scroll_y,
		const bool flipped
	) :
		EventMouse(mouse_id, window_id, pos_x, pos_y),
		scroll_x_	{ scroll_x	},
		scroll_y_	{ scroll_y	},
		flipped_	{ flipped	}
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventMouseWheel::GetName() const
	{
		return "EventMouseWheel";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventMouseWheel::GetType() const
	{
		return EventType::kMouseWheel;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventMouseWheel::GetCategoryFlags() const
	{
		return EventCategory::kMouse | EventCategory::kInput;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventMouseWheel::ToString() const
	{
		std::stringstream ss;
		ss << EventMouse::ToString();
		ss << ", [";

		if(IsFlipped())
			ss << "(" << -GetScrollX() << ", " << -GetScrollY() << "), " << "true";
		else
			ss << "(" << GetScrollX() << ", " << GetScrollY() << "), " << "false";

		ss << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the horizontal scroll amount.
	 * 
	 * @param account_for_flip	Whether or not to account for the scroll direction being flipped.
	 * @return pos_pixel_t	The horizontal scroll amount.
	 */
	pos_pixel_t EventMouseWheel::GetScrollX(const bool account_for_flip) const
	{
		const pos_pixel_t inversion_factor = (account_for_flip && IsFlipped()) ? -1 : 1;
		return scroll_x_ * inversion_factor;
	}

	/**
	 * @brief	Get the vertical scroll amount.
	 * 
	 * @param account_for_flip	Whether or not to account for the scroll direction being flipped.
	 * @return pos_pixel_t	The vertical scroll amount.
	 */
	pos_pixel_t EventMouseWheel::GetScrollY(const bool account_for_flip) const
	{
		const pos_pixel_t inversion_factor = (account_for_flip && IsFlipped()) ? -1 : 1;
		return scroll_y_ * inversion_factor;
	}

	/**
	 * @brief	Check if the scroll direction is flipped.
	 * 
	 * @return bool	Whether the scroll direction is flipped.
	 * @retval true	The scroll direction is flipped.
	 * @retval false	The scroll direction is not flipped.
	 */
	bool EventMouseWheel::IsFlipped() const
	{	
		return flipped_;
	}

} // namespace trac