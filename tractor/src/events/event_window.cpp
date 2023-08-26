/**
 * @file	event_window.cpp
 * @brief	Source file for window events. See event_window.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 */

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "events/event_window.hpp"

// External libraries header includes
#include <SDL_video.h>
#include <SDL_timer.h>

namespace trac
{
	/**
	 * @brief	Construct a new EventWindow event.
	 * 
	 * @param window_id	The ID of the window that generated the event.
	 */
	EventWindow::EventWindow(window_id_t window_id) :
		Event(),
		timestamp_ms_ { SDL_GetTicks64() },
		window_id_ { window_id }
	{}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventWindow::GetCategoryFlags() const
	{
		return EventCategory::kWindow;
	}
	
	/**
	 * @brief Get the timestamp of the event in milliseconds.
	 * 
	 * @return timestamp_t The timestamp of the event in milliseconds.
	 */
	timestamp_t EventWindow::GetTimestampMs() const
	{
		return timestamp_ms_;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventWindow::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << GetWindowID() << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the ID of the window that generated the event.
	 * 
	 * @return window_id_t	The ID of the window that generated the event.
	 */
	window_id_t EventWindow::GetWindowID() const
	{
		return window_id_;
	}

	/**
	 * @brief	Construct a new EventWindowShown event.
	 * 
	 * @param id	The ID of the window that was shown.
	 */
	EventWindowShown::EventWindowShown(const window_id_t id) :
		EventWindow(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventWindowShown::GetName() const
	{
		return "EventWindowShown";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventWindowShown::GetType() const
	{
		return EventType::kWindowShown;
	}

	/**
	 * @brief	Construct a new EventWindowHidden event.
	 * 
	 * @param id	The ID of the window that was hidden.
	 */
	EventWindowHidden::EventWindowHidden(const window_id_t id) :
		EventWindow(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventWindowHidden::GetName() const
	{
		return "EventWindowHidden";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventWindowHidden::GetType() const
	{
		return EventType::kWindowHidden;
	}
	
	/**
	 * @brief	Construct a new EventWindowExposed event.
	 * 
	 * @param id	The ID of the window that was exposed.
	 */
	EventWindowExposed::EventWindowExposed(const window_id_t id) :
		EventWindow(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventWindowExposed::GetName() const
	{
		return "EventWindowExposed";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventWindowExposed::GetType() const
	{
		return EventType::kWindowExposed;
	}
	
	/**
	 * @brief	Construct a new EventWindowMoved event.
	 * 
	 * @param id	The ID of the window that was moved.
	 * @param pos_x	The new x-position of the window.
	 * @param pos_y	The new y-position of the window.
	 */
	EventWindowMoved::EventWindowMoved(const window_id_t id, const pos_pixel_t pos_x, const pos_pixel_t pos_y) :
		EventWindow(id),
		pos_x_ { pos_x },
		pos_y_ { pos_y }
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventWindowMoved::GetName() const
	{
		return "EventWindowMoved";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventWindowMoved::GetType() const
	{
		return EventType::kWindowMoved;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventWindowMoved::ToString() const
	{
		std::stringstream ss;
		ss << EventWindow::ToString() << ", [";
		ss << GetPosX() << ", " << GetPosY()  << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the new x-position of the window.
	 * 
	 * @return pos_pixel_t	The new x-position of the window.
	 */
	pos_pixel_t EventWindowMoved::GetPosX() const
	{
		return pos_x_;
	}

	/**
	 * @brief	Get the new y-position of the window.
	 * 
	 * @return pos_pixel_t	The new y-position of the window.
	 */
	pos_pixel_t EventWindowMoved::GetPosY() const
	{
		return pos_y_;
	}

	/**
	 * @brief	Construct a new EventWindowResized event.
	 * 
	 * @param id	The ID of the window that was resized.
	 * @param width	The new width of the window.
	 * @param height	The new height of the window.
	 */
	EventWindowResized::EventWindowResized(const window_id_t id, const size_pixel_t width, const size_pixel_t height) :
		EventWindow(id),
		width_	{ width		},
		height_	{ height	}
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventWindowResized::GetName() const
	{
		return "EventWindowResized";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventWindowResized::GetType() const
	{
		return EventType::kWindowResized;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventWindowResized::ToString() const
	{
		std::stringstream ss;
		ss << EventWindow::ToString() << ", [";
		ss << GetWidth() << ", " << GetHeight() << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the new width of the window.
	 * 
	 * @return size_pixel_t	The new width of the window.
	 */
	size_pixel_t EventWindowResized::GetWidth() const
	{
		return width_;
	}

	/**
	 * @brief	Get the new height of the window.
	 * 
	 * @return size_pixel_t	The new height of the window.
	 */
	size_pixel_t EventWindowResized::GetHeight() const
	{
		return height_;
	}
	
	/**
	 * @brief	Construct a new EventWindowSizeChanged event.
	 * 
	 * @param id	The ID of the window that changed size.
	 */
	EventWindowSizeChanged::EventWindowSizeChanged(const window_id_t id) :
		EventWindow(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventWindowSizeChanged::GetName() const
	{
		return "EventWindowSizeChanged";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventWindowSizeChanged::GetType() const
	{
		return EventType::kWindowSizeChanged;
	}
	
	/**
	 * @brief	Construct a new EventWindowMinimized event.
	 * 
	 * @param id	The ID of the window that was minimized.
	 */
	EventWindowMinimized::EventWindowMinimized(const window_id_t id) :
		EventWindow(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventWindowMinimized::GetName() const
	{
		return "EventWindowMinimized";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventWindowMinimized::GetType() const
	{
		return EventType::kWindowMinimized;
	}
	
	/**
	 * @brief	Construct a new EventWindowMaximized event.
	 * 
	 * @param id	The ID of the window that was maximized.
	 */
	EventWindowMaximized::EventWindowMaximized(const window_id_t id) :
		EventWindow(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventWindowMaximized::GetName() const
	{
		return "EventWindowMaximized";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventWindowMaximized::GetType() const
	{
		return EventType::kWindowMaximized;
	}
	
	/**
	 * @brief	Construct a new EventWindowRestored event.
	 * 
	 * @param id	The ID of the window that was restored.
	 */
	EventWindowRestored::EventWindowRestored(const window_id_t id) :
		EventWindow(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventWindowRestored::GetName() const
	{
		return "EventWindowRestored";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventWindowRestored::GetType() const
	{
		return EventType::kWindowRestored;
	}
	
	/**
	 * @brief	Construct a new EventWindowEnter event.
	 * 
	 * @param id	The ID of the window that gained mouse focus.
	 */
	EventWindowEnter::EventWindowEnter(const window_id_t id) :
		EventWindow(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventWindowEnter::GetName() const
	{
		return "EventWindowEnter";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventWindowEnter::GetType() const
	{
		return EventType::kWindowEnter;
	}
	
	/**
	 * @brief	Construct a new EventWindowLeave event.
	 * 
	 * @param id	The ID of the window that lost mouse focus.
	 */
	EventWindowLeave::EventWindowLeave(const window_id_t id) :
		EventWindow(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventWindowLeave::GetName() const
	{
		return "EventWindowLeave";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventWindowLeave::GetType() const
	{
		return EventType::kWindowLeave;
	}
	
	/**
	 * @brief	Construct a new EventWindowFocusGained event.
	 * 
	 * @param id	The ID of the window that gained keyboard focus.
	 */
	EventWindowFocusGained::EventWindowFocusGained(const window_id_t id) :
		EventWindow(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventWindowFocusGained::GetName() const
	{
		return "EventWindowFocusGained";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventWindowFocusGained::GetType() const
	{
		return EventType::kWindowFocusGained;
	}
	
	/**
	 * @brief	Construct a new EventWindowFocusLost event.
	 * 
	 * @param id	The ID of the window that lost keyboard focus.
	 */
	EventWindowFocusLost::EventWindowFocusLost(const window_id_t id) :
		EventWindow(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventWindowFocusLost::GetName() const
	{
		return "EventWindowFocusLost";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventWindowFocusLost::GetType() const
	{
		return EventType::kWindowFocusLost;
	}
	
	/**
	 * @brief	Construct a new EventWindowTakeFocus event.
	 * 
	 * @param id	The ID of the window that is being offered to take input focus.
	 */
	EventWindowTakeFocus::EventWindowTakeFocus(const window_id_t id) :
		EventWindow(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventWindowTakeFocus::GetName() const
	{
		return "EventWindowTakeFocus";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventWindowTakeFocus::GetType() const
	{
		return EventType::kWindowTakeFocus;
	}
	
	/**
	 * @brief	Construct a new EventWindowHitTest event.
	 * 
	 * @param id	The ID of the window that received a hit test.
	 */
	EventWindowHitTest::EventWindowHitTest(const window_id_t id) :
		EventWindow(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventWindowHitTest::GetName() const
	{
		return "EventWindowHitTest";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventWindowHitTest::GetType() const
	{
		return EventType::kWindowHitTest;
	}
	
	/**
	 * @brief	Construct a new EventWindowIccProfileChanged event.
	 * 
	 * @param id	The ID of the window that changed ICC profile.
	 */
	EventWindowIccProfileChanged::EventWindowIccProfileChanged(const window_id_t id) :
		EventWindow(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventWindowIccProfileChanged::GetName() const
	{
		return "EventWindowIccProfileChanged";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventWindowIccProfileChanged::GetType() const
	{
		return EventType::kWindowIccProfileChanged;
	}
	
	/**
	 * @brief	Construct a new EventWindowDisplayChanged event.
	 * 
	 * @param id	The ID of the window that changed display.
	 * @param index	The index of the new display.
	 */
	EventWindowDisplayChanged::EventWindowDisplayChanged(const window_id_t id, const display_index_t index) :
		EventWindow(id),
		index_ { index }
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventWindowDisplayChanged::GetName() const
	{
		return "EventWindowDisplayChanged";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventWindowDisplayChanged::GetType() const
	{
		return EventType::kWindowDisplayChanged;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventWindowDisplayChanged::ToString() const
	{
		std::stringstream ss;
		ss << EventWindow::ToString() << ", [";
		ss << GetDisplayIndex() << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the index of the new display.
	 * 
	 * @return display_index_t	The index of the new display.
	 */
	display_index_t EventWindowDisplayChanged::GetDisplayIndex() const
	{
		return index_;
	}

	/**
	 * @brief	Construct a new EventWindowClosed event.
	 * 
	 * @param id	The ID of the window that was closed.
	 */
	EventWindowClosed::EventWindowClosed(const window_id_t id) :
		EventWindow(id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventWindowClosed::GetName() const
	{
		return "EventWindowClosed";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventWindowClosed::GetType() const
	{
		return EventType::kWindowClosed;
	}
} // namespace trac