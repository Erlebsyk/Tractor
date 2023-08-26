/**
 * @file	event_window.hpp
 * @brief	Window event header file. All events related to the window are defined here.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 * 
*/

#ifndef EVENT_WINDOW_HPP_
#define EVENT_WINDOW_HPP_

// Related header include
#include "event.hpp"

// External libraries header includes
#include <SDL_video.h>

// Project header includes
#include "event_display.hpp"

namespace trac
{
	/// Type definition for window ID that is used to differentiate between different windows.
	typedef uint32_t window_id_t;

	/// @brief Abstract base class for all window events.
	class EventWindow : public Event
	{
	public:
		// Constructors and destructors
	
		EventWindow(window_id_t window_id);
		/// @brief Virtual default destructor.
		virtual ~EventWindow() = default;

		/// @brief Explicitly defined default copy constructor.
		EventWindow(const EventWindow&) = default;
		/// @brief Explicitly defined default move constructor.
		EventWindow(EventWindow&&) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventWindow& operator=(const EventWindow&) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventWindow& operator=(EventWindow&&) = default;
	
		//Public functions
	
		event_category_t GetCategoryFlags() const override;
		timestamp_t GetTimestampMs() const override;
		virtual std::string ToString() const override;

		window_id_t GetWindowID() const;

	private:
		/// The timestamp of the event, in milliseconds.
		const timestamp_t timestamp_ms_;
		/// The ID of the window that generated the event.
		const window_id_t window_id_;
	};
	
	/// @brief	Event that is generated when a window is shown.
	class EventWindowShown : public EventWindow
	{
	public:
		// Constructors and destructors
	
		EventWindowShown(window_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Event that is generated when a window is hidden.
	class EventWindowHidden : public EventWindow
	{
	public:
		// Constructors and destructors
	
		EventWindowHidden(window_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Event that is generated when a window is exposed.
	class EventWindowExposed : public EventWindow
	{
	public:
		// Constructors and destructors
	
		EventWindowExposed(window_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Event that is generated when a window is moved.
	class EventWindowMoved : public EventWindow
	{
	public:
		// Constructors and destructors
	
		EventWindowMoved(window_id_t id, pos_pixel_t pos_x, pos_pixel_t pos_y);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		std::string ToString() const override;

		pos_pixel_t GetPosX() const;
		pos_pixel_t GetPosY() const;

	private:
		/// The new x-position of the window, in pixels, from the left of the screen.
		const pos_pixel_t pos_x_;
		/// The new y-position of the window, in pixels, from the top of the screen.
		const pos_pixel_t pos_y_;
	};
	
	/// @brief	Event that is generated when a window is resized.
	class EventWindowResized : public EventWindow
	{
	public:
		// Constructors and destructors
	
		EventWindowResized(window_id_t id, size_pixel_t width, size_pixel_t height);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		std::string ToString() const override;

		size_pixel_t GetWidth() const;
		size_pixel_t GetHeight() const;

	private:
		/// The new width of the window, in pixels.
		const size_pixel_t width_;
		/// The new height of the window, in pixels.
		const size_pixel_t height_;
	};

	/**
	 * @brief	Event that is generated when the window size has changed, either as a result of an API call or through the system or user changing the window
	 * 			size.
	 */
	class EventWindowSizeChanged : public EventWindow
	{
	public:
		// Constructors and destructors
	
		EventWindowSizeChanged(window_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Event that is generated when a window is minimized.
	class EventWindowMinimized : public EventWindow
	{
	public:
		// Constructors and destructors
	
		EventWindowMinimized(window_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Event that is generated when a window is maximized.
	class EventWindowMaximized : public EventWindow
	{
	public:
		// Constructors and destructors
	
		EventWindowMaximized(window_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Event that is generated when a window is restored to its normal size and position.
	class EventWindowRestored : public EventWindow
	{
	public:
		// Constructors and destructors
	
		EventWindowRestored(window_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Event that is generated when a window gains mouse focus.
	class EventWindowEnter : public EventWindow
	{
	public:
		// Constructors and destructors
	
		EventWindowEnter(window_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Event that is generated when a window loses mouse focus.
	class EventWindowLeave : public EventWindow
	{
	public:
		// Constructors and destructors
	
		EventWindowLeave(window_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Event that is generated when a window gains keyboard focus.
	class EventWindowFocusGained : public EventWindow
	{
	public:
		// Constructors and destructors
	
		EventWindowFocusGained(window_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Event that is generated when a window loses keyboard focus.
	class EventWindowFocusLost : public EventWindow
	{
	public:
		// Constructors and destructors
	
		EventWindowFocusLost(window_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Event that is generated when the window is being offered to take input focus.
	class EventWindowTakeFocus : public EventWindow
	{
	public:
		// Constructors and destructors
	
		EventWindowTakeFocus(window_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Event that is generated when the window had a hit test that wasn't SDL_HITTEST_NORMAL.
	class EventWindowHitTest : public EventWindow
	{
	public:
		// Constructors and destructors
	
		EventWindowHitTest(window_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Event that is generated when the ICC profile of the window changes.
	class EventWindowIccProfileChanged : public EventWindow
	{
	public:
		// Constructors and destructors
	
		EventWindowIccProfileChanged(window_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Event that is generated when the window is about to be destroyed.
	class EventWindowDisplayChanged : public EventWindow
	{
	public:
		// Constructors and destructors
	
		EventWindowDisplayChanged(window_id_t id, display_index_t index);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		std::string ToString() const override;

		display_index_t GetDisplayIndex() const;

	private:
		/// The window has been moved to display with the given index.
		const display_index_t index_;
	};

	/// @brief	Event that is generated when the window is closed.
	class EventWindowClosed : public EventWindow
	{
	public:
		// Constructors and destructors
	
		EventWindowClosed(window_id_t id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

} // Namespace trac

#endif // EVENT_WINDOW_HPP_ 