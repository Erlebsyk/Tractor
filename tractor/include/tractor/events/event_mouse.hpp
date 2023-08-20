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
#include "event.hpp"

// External libraries header includes
#include <SDL_mouse.h>

// Project header includes
#include "event_window.hpp"

namespace trac
{
	/// Type definition for mouse ID that is used to differentiate between different mice.
	typedef uint32_t mouse_id_t;
	/// Type definition for mouse positions, both absolute and relative.
	typedef int32_t mouse_pos_t;
	/// Type definition for mouse button states bitmask.
	typedef uint32_t mouse_button_state_t;

	/// @brief Enumerator defining the different mouse buttons.
	enum class MouseButton
	{
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

	/// @brief	Abstract base class for mouse events.
	class EventMouse : public Event
	{
	public:
		// Constructors and destructors
	
		EventMouse(
			mouse_id_t mouse_id,
			window_id_t window_id,
			mouse_pos_t pos_x,
			mouse_pos_t pos_y
		);
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

		mouse_id_t GetMouseID() const;
		window_id_t GetWindowID() const;
		mouse_pos_t GetPosX() const;
		mouse_pos_t GetPosY() const;

	private:
		/// The timestamp of the event in milliseconds.
		const timestamp_t timestamp_ms_;
		/// The ID of the mouse that the event occurred on.
		const mouse_id_t mouse_id_;
		/// The ID of the window that the event occurred in.
		const window_id_t window_id_;
		/// The x-position of the mouse in the window.
		const mouse_pos_t pos_x_;
		/// The y-position of the mouse in the window.
		const mouse_pos_t pos_y_;
	};

	/// @brief	Mouse movement event.
	class EventMouseMotion : public EventMouse
	{
	public:
		// Constructors and destructors
	
		EventMouseMotion(
			mouse_id_t mouse_id,
			window_id_t window_id,
			mouse_pos_t pos_x,
			mouse_pos_t pos_y,
			mouse_button_state_t button_state,
			mouse_pos_t rel_x,
			mouse_pos_t rel_y
		);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;

		mouse_button_state_t GetButtonState() const;
		bool IsButtonPressed(MouseButton button) const;
		bool AreButtonsPressed(mouse_button_state_t button_bitmask) const;
		mouse_pos_t GetRelX() const;
		mouse_pos_t GetRelY() const;

	private:
		/// The current state of the mouse buttons.
		mouse_button_state_t button_state_;
		/// The relative motion of the mouse in x-direction.
		const mouse_pos_t rel_x_;
		/// The relative motion of the mouse in y-direction.
		const mouse_pos_t rel_y_;
	};

	/// @brief Abstract base class for mouse button events.
	class EventMouseButton : public EventMouse
	{
	public:
		// Constructors and destructors
	
		EventMouseButton(
			mouse_id_t mouse_id,
			window_id_t window_id,
			mouse_pos_t pos_x,
			mouse_pos_t pos_y,
			MouseButton button
		);
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
	
		EventMouseButtonDown(
			mouse_id_t mouse_id,
			window_id_t window_id,
			mouse_pos_t pos_x,
			mouse_pos_t pos_y,
			MouseButton button
		);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Mouse button release event.
	class EventMouseButtonUp : public EventMouseButton
	{
	public:
		// Constructors and destructors
	
		EventMouseButtonUp(
			mouse_id_t mouse_id,
			window_id_t window_id,
			mouse_pos_t pos_x,
			mouse_pos_t pos_y,
			MouseButton button
		);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Mouse button click event that supports double-clicks, triple-clicks, etc.
	class EventMouseButtonClicked : public EventMouseButton
	{
	public:
		// Constructors and destructors
	
		EventMouseButtonClicked(
			mouse_id_t mouse_id,
			window_id_t window_id,
			mouse_pos_t pos_x,
			mouse_pos_t pos_y,
			MouseButton button,
			uint32_t clicks
		);
	
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
	
		EventMouseWheel(
			mouse_id_t mouse_id,
			window_id_t window_id,
			mouse_pos_t pos_x,
			mouse_pos_t pos_y,
			mouse_pos_t scroll_x,
			mouse_pos_t scroll_y,
			bool flipped = false
		);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;

		mouse_pos_t GetScrollX(bool account_for_flip = false) const;
		mouse_pos_t GetScrollY(bool account_for_flip = false) const;
		bool IsFlipped() const;

	private:
		/// The amount of scrolling in the horizontal direction. Positive values indicate scrolling to the right.
		const mouse_pos_t scroll_x_;
		/// The amount of scrolling in the vertical direction. Positive values away from the user, negative values towards the user.
		const mouse_pos_t scroll_y_;
		/// Whether or not the scroll direction is flipped.
		const bool flipped_;
	};

} // Namespace trac

#endif // EVENT_MOUSE_HPP_ 