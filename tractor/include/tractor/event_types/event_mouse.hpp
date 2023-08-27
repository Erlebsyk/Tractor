/**
 * @file	event_mouse.hpp
 * @brief	Mouse event header file. All events related to mouse input are defined here.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 * 
*/

#ifndef EVENT_MOUSE_HPP_
#define EVENT_MOUSE_HPP_

// Related header include
#include "event_base.hpp"

// External libraries header includes
#include <SDL_mouse.h>

// Project header includes
#include "event_window.hpp"

namespace trac
{
	/// Type definition for mouse ID that is used to differentiate between different mice.
	typedef uint32_t mouse_id_t;
	/// Type definition for mouse button states bitmask.
	typedef uint32_t mouse_button_state_t;

	/// @brief Enumerator defining the different mouse buttons.
	enum class MouseButton
	{
		kUnknown = 0,
		kLeft = SDL_BUTTON_LEFT,
		kMiddle = SDL_BUTTON_MIDDLE,
		kRight = SDL_BUTTON_RIGHT,
		kX1 = SDL_BUTTON_X1,
		kX2 = SDL_BUTTON_X2
	};

	/// @brief Enumerator defining the different mouse button bitmasks.
	enum class MouseButtonBitmask
	{
		kLeft = SDL_BUTTON_LMASK,
		kMiddle = SDL_BUTTON_MMASK,
		kRight = SDL_BUTTON_RMASK,
		kX1 = SDL_BUTTON_X1MASK,
		kX2 = SDL_BUTTON_X2MASK
	};

	/// @brief Structure for common mouse data.
	struct MouseData
	{
		MouseData();
		MouseData(mouse_id_t mouse_id, window_id_t window_id, pos_pixel_t pos_x, pos_pixel_t pos_y);

		/// The ID of the mouse that generated the event.
		mouse_id_t mouse_id;
		/// The ID of the window that generated the event.
		window_id_t window_id;
		/// The x-position of the mouse cursor in the window.
		pos_pixel_t pos_x;
		/// The y-position of the mouse cursor in the window.
		pos_pixel_t pos_y;
	};

	/// @brief	Abstract base class for mouse events.
	class EventMouse : public Event
	{
	public:
		// Constructors and destructors
	
		EventMouse(const MouseData& mouse_data);
		/// @brief Virtual default destructor.
		virtual ~EventMouse() = default;

		/// @brief Explicitly defined default copy constructor.
		EventMouse(const EventMouse& other) = default;
		/// @brief Explicitly defined default move constructor.
		EventMouse(EventMouse&& other) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventMouse& operator=(const EventMouse& other) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventMouse& operator=(EventMouse&& other) = default;
	
		//Public functions
	
		timestamp_t GetTimestampMs() const override;
		virtual std::string ToString() const override;

		mouse_id_t GetMouseID() const;
		window_id_t GetWindowID() const;
		pos_pixel_t GetPosX() const;
		pos_pixel_t GetPosY() const;

	private:
		/// The timestamp of the event in milliseconds.
		const timestamp_t timestamp_ms_;
		/// Common mouse data
		const MouseData mouse_data_;
	};

	/// @brief	Mouse movement event.
	class EventMouseMotion : public EventMouse
	{
	public:
		// Constructors and destructors
	
		EventMouseMotion(const MouseData& mouse_data, mouse_button_state_t button_state, pos_pixel_t rel_x, pos_pixel_t rel_y);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;

		mouse_button_state_t GetButtonState() const;
		bool IsButtonPressed(MouseButton button) const;
		bool AreButtonsPressed(mouse_button_state_t button_bitmask) const;
		pos_pixel_t GetRelX() const;
		pos_pixel_t GetRelY() const;

	private:
		/// The current state of the mouse buttons.
		mouse_button_state_t button_state_;
		/// The relative motion of the mouse in x-direction.
		const pos_pixel_t dx_;
		/// The relative motion of the mouse in y-direction.
		const pos_pixel_t dy_;
	};

	/// @brief Abstract base class for mouse button events.
	class EventMouseButton : public EventMouse
	{
	public:
		// Constructors and destructors
	
		EventMouseButton(const MouseData& mouse_data, MouseButton button);
		/// @brief Virtual default destructor.
		virtual ~EventMouseButton() = default;

		/// @brief Explicitly defined default copy constructor.
		EventMouseButton(const EventMouseButton& other) = default;
		/// @brief Explicitly defined default move constructor.
		EventMouseButton(EventMouseButton&& other) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventMouseButton& operator=(const EventMouseButton& other) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventMouseButton& operator=(EventMouseButton&& other) = default;
	
		//Public functions
	
		event_category_t GetCategoryFlags() const override;
		virtual std::string ToString() const override;

		MouseButton GetButton() const;

	private:
		/// The button that triggered the event.
		const MouseButton button_;
	};

	/// @brief	Mouse button press event.
	class EventMouseButtonDown : public EventMouseButton
	{
	public:
		// Constructors and destructors
	
		EventMouseButtonDown(const MouseData& mouse_data, MouseButton button);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Mouse button release event.
	class EventMouseButtonUp : public EventMouseButton
	{
	public:
		// Constructors and destructors
	
		EventMouseButtonUp(const MouseData& mouse_data, MouseButton button);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Mouse button click event that supports double-clicks, triple-clicks, etc.
	class EventMouseButtonClicked : public EventMouseButton
	{
	public:
		// Constructors and destructors
	
		EventMouseButtonClicked(const MouseData& mouse_data, MouseButton button, uint32_t clicks);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		std::string ToString() const override;

		uint32_t GetClicks() const;

	private:
		/// The number of clicks that triggered the event.
		const uint32_t clicks_;	
	};

	/// @brief	Mouse wheel scroll event.
	class EventMouseWheel : public EventMouse
	{
	public:
		// Constructors and destructors
	
		EventMouseWheel(const MouseData& mouse_data, pos_pixel_t scroll_x, pos_pixel_t scroll_y, bool flipped = false);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;

		pos_pixel_t GetScrollX(bool account_for_flip = false) const;
		pos_pixel_t GetScrollY(bool account_for_flip = false) const;
		bool IsFlipped() const;

	private:
		/// The amount of scrolling in the horizontal direction. Positive values indicate scrolling to the right.
		const pos_pixel_t scroll_x_;
		/// The amount of scrolling in the vertical direction. Positive values away from the user, negative values towards the user.
		const pos_pixel_t scroll_y_;
		/// Whether or not the scroll direction is flipped.
		const bool flipped_;
	};

} // Namespace trac

#endif // EVENT_MOUSE_HPP_ 