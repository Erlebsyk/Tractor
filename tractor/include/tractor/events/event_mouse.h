/**
 * @file	event_mouse.h
 * @brief	Header file for mouse events in the tractor game engine library.
 * 
 * @author	Erlend Elias Isachsen
 * @date	24.07.2023
 * 
*/

#ifndef EVENT_MOUSE_H_
#define EVENT_MOUSE_H_

// Standard library header includes
#include <cstdint>
#include <sstream>

// External libraries header includes
#include <SDL_mouse.h>

// Project header includes
#include "event.h"

namespace trac
{
	// Defines/macros, enums and variables	

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

	// Funciton declarations


	// Classes and structs

	/**
	 * @brief	Mouse movement event class. The class stores information about the mouse's position when the event was triggered.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	class EventMouseMovement : public Event
	{
	public:
		// Constructors and destructors
		/**
		 * @brief	Construct a mouse movement event.
		 * 
		 * @param x	The x position of the mouse cursor.
		 * @param y	The y position of the mouse cursor.
		 */
		EventMouseMovement(const float x, const float y) : Event(), x_(x), y_(y) {}
		~EventMouseMovement() = default;
	
		//Public functions
		const char* GetName() const	{ return "EventMouseMovement"; };
		const EventType GetType() const { return EventType::kMouseMoved; }
		event_category_t GetCategoryFlags() const { return (EventCategory::kMouse) | (EventCategory::kInput); }

		std::string ToString() const {
			std::stringstream ss;
			ss << GetName() << ": [" << x_ << ", " << y_ << "]";
			return ss.str();
		}

		/**
		 * @brief	Get the x position of the mouse cursor.
		 * 
		 * @return float	The x position of the mouse cursor.
		 */
		float GetX() const { return x_; }

		/**
		 * @brief	Get the y position of the mouse cursor.
		 * 
		 * @return float	The y position of the mouse cursor.
		 */
		float GetY() const { return y_; }

		//Public variables
	
	private:
		//Private functions
	
		//Private variables
		const float x_;
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
		// Constructors and destructors
		/**
		 * @brief	Construct a new mouse scrolled event.
		 * 
		 * @param offset_x	The x offset of the mouse scrolled event.
		 * @param offset_y	The y offset of the mouse scrolled event.
		 */
		EventMouseScrolled(const float offset_x, const float offset_y) : Event(), offset_x_{offset_x}, offset_y_{offset_y}{}
		~EventMouseScrolled() = default;
	
		//Public functions
		const char* GetName() const { return "EventMouseScrolled";}
		const EventType GetType() const { return EventType::kMouseScrolled; }
		event_category_t GetCategoryFlags() const { return (EventCategory::kMouse) | (EventCategory::kInput); }
		std::string ToString() const {
			std::stringstream ss;
			ss << GetName() << ": [" << offset_x_ << ", " << offset_y_ << "]";
			return ss.str();
		}

		/**
		 * @brief	Get the x offset of the mouse scroll wheel.
		 * 
		 * @return float	The x offset of the mouse scroll wheel.
		 */
		float GetOffsetX() const { return offset_x_; }

		/**
		 * @brief	Get the y offset of the mouse scroll wheel.
		 * 
		 * @return float	The y offset of the mouse scroll wheel.
		 */
		float GetOffsetY() const { return offset_y_; }


		//Public variables
	
	private:
		//Private functions
	
		//Private variables
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
		// Constructors and destructors
		~EventMouseButton() = default;
	
		//Public functions
		event_category_t GetCategoryFlags() const { return (EventCategory::kMouse) | (EventCategory::kInput) | EventCategory::kMouseButton; }

		std::string ToString() const {
			std::stringstream ss;
			ss << GetName() << ": " << (uint16_t)button_;
			return ss.str();
		}

		/**
		 * @brief	Get the mouse button that triggered the event.
		 * 
		 * @return MouseCode	The mouse button that triggered the event.
		 */
		MouseCode GetButton() const { return button_; }

		//Public variables
	
	protected:
		// Constructors and destructors

		/**
		 * @brief	Construct a new mouse button event.
		 * 
		 * @param button	The mouse button that triggered the event.
		 */
		EventMouseButton(const MouseCode button) : Event(), button_(button) {}
	
		//Protected functions
	
		//Protected variables
	
	private:
		//Private functions
	
		//Private variables
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
		/**
		 * @brief	Construct a new mouse button pressed event.
		 * 
		 * @param button	The mouse button that triggered the event.
		 */
		EventMouseButtonPress(const MouseCode button) : EventMouseButton(button) {};
		~EventMouseButtonPress() = default;
	
		//Public functions
		const char* GetName() const { return "EventMouseButtonPress"; }
		const EventType GetType() const { return EventType::kMouseButtonPressed; }
	
		//Public variables
	
	private:
		//Private functions
	
		//Private variables
	
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
		/**
		 * @brief	Construct a new mouse button released event.
		 * 
		 * @param button	The mouse button that triggered the event.
		 */
		EventMouseButtonRelease(const MouseCode button) : EventMouseButton(button) {};
		~EventMouseButtonRelease() = default;
	
		//Public functions
		const char* GetName() const { return "EventMouseButtonRelease"; }
		const EventType GetType() const { return EventType::kMouseButtonReleased; }

		//Public variables
	
	private:
		//Private functions
	
		//Private variables
	
	};

	// Implementation


} // Namespace trac


#endif // EVENT_MOUSE_H_ 

/*
 * END OF FILE
 */