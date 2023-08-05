/**
 * @file	event_mouse.hpp
 * @brief	Header file for mouse events in the tractor game engine library.
 * 
 * @author	Erlend Elias Isachsen
 * @date	24.07.2023
 * 
*/

#ifndef EVENT_MOUSE_HPP_
#define EVENT_MOUSE_HPP_

// External libraries header includes
#include <SDL_mouse.h>

// Project header includes
#include "event.hpp"

namespace trac
{
	/// @brief	Enumeration of mouse buttons, imported from SDL.
	enum class MouseCode : uint16_t
	{
		kUnknown = 0,
		kLeft = SDL_BUTTON_LEFT,
		kMiddle = SDL_BUTTON_MIDDLE,
		kRight = SDL_BUTTON_RIGHT,
		kX1 = SDL_BUTTON_X1,
		kX2 = SDL_BUTTON_X2,
		kCount = SDL_BUTTON_X2 + 1
	};

	/// @brief	Mouse movement event class. The class stores information about the mouse's position when the event was triggered.
	class EventMouseMovement : public Event
	{
	public:
		// Constructors and destructors

		EventMouseMovement(float x, float y);
	
		// Public functions

		const char* GetName() const override;
		const EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;

		float GetX() const;
		float GetY() const;
	
	private:
		/// The x position of the mouse cursor.
		const float x_;
		/// The y position of the mouse cursor.
		const float y_;
	};

	/// @brief	Mouse scroll event class. The class stores information about the mouse's scroll wheel when the event was triggered.
	class EventMouseScrolled : public Event
	{
	public:
		EventMouseScrolled(float offset_x, float offset_y);
	
		//Public functions
		const char* GetName() const override;
		const EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;

		float GetOffsetX() const;
		float GetOffsetY() const;

	private:
		/// The x offset of the mouse scroll wheel.
		const float offset_x_;
		/// The y offset of the mouse scroll wheel.
		const float offset_y_;
	};

	/// @brief	Mouse button event class. The class stores information about the mouse button that triggered the event.
	class EventMouseButton : public Event
	{
	public:
		// Constructors and destructors

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

		// Public functions

		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;

		MouseCode GetButton() const;

	protected:
		EventMouseButton(MouseCode button);
	
	private:
		/// The mouse button that triggered the event.
		const MouseCode button_;
	};

	/// @brief	Mouse button pressed event class. The class stores information about the mouse button that triggered the event.
	class EventMouseButtonPress : public EventMouseButton
	{
	public:
		// Constructors and destructors

		EventMouseButtonPress(MouseCode button);
	
		//Public functions
		
		const char* GetName() const override;
		const EventType GetType() const override;
	};

	/// @brief	Mouse button released event class. The class stores information about the mouse button that triggered the event.
	class EventMouseButtonRelease : public EventMouseButton
	{
	public:
		// Constructors and destructors

		EventMouseButtonRelease(MouseCode button);
	
		//Public functions

		const char* GetName() const override;
		const EventType GetType() const override;
	};
} // Namespace trac

#endif // EVENT_MOUSE_HPP_ 