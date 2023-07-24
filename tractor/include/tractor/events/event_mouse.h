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


// Project header includes
#include "event.h"

namespace trac
{
	// Defines/macros, enums and variables	


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
		 * 
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
		 * 
		 */
		float GetX() const { return x_; }

		/**
		 * @brief	Get the y position of the mouse cursor.
		 * 
		 * @return float	The y position of the mouse cursor.
		 * 
		 */
		float GetY() const { return y_; }

		//Public variables
	
	private:
		//Private functions
	
		//Private variables
		float x_;
		float y_;
	};

	// Implementation


} // Namespace trac


#endif // EVENT_MOUSE_H_ 

/*
 * END OF FILE
 */