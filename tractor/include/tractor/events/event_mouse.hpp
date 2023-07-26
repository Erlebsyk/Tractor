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

// Standard library header includes
#include <cstdint>

// External libraries header includes
#include <SDL_mouse.h>

// Project header includes
#include "event.hpp"

namespace trac
{
	/**
	 * @brief	Enumeration of mouse buttons, imported from SDL.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	enum class MouseCode : uint16_t
	{
		kLeft = SDL_BUTTON_LEFT,
		kMiddle = SDL_BUTTON_MIDDLE,
		kRight = SDL_BUTTON_RIGHT,
		kX1 = SDL_BUTTON_X1,
		kX2 = SDL_BUTTON_X2,
		kCount = SDL_BUTTON_X2 + 1
	};

	/**
	 * @brief	Mouse movement event class. The class stores information about the mouse's position when the event was triggered.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	class EventMouseMovement : public Event
	{
	public:
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

	/**
	 * @brief	Mouse scroll event class. The class stores information about the mouse's scroll wheel when the event was triggered.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
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

	/**
	 * @brief	Mouse button event class. The class stores information about the mouse button that triggered the event.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	class EventMouseButton : public Event
	{
	public:
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;

		MouseCode GetButton() const;

	protected:
		EventMouseButton(MouseCode button);
	
	private:
		/// The mouse button that triggered the event.
		const MouseCode button_;
	};

	/**
	 * @brief	Mouse button pressed event class. The class stores information about the mouse button that triggered the event.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	class EventMouseButtonPress : public EventMouseButton
	{
	public:
		// Constructors and destructors
		EventMouseButtonPress(MouseCode button);
	
		//Public functions
		const char* GetName() const override;
		const EventType GetType() const override;
	};

	/**
	 * @brief	Mouse button released event class. The class stores information about the mouse button that triggered the event.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
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