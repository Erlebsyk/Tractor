/**
 * @file	event_base.cpp
 * @brief	Source file for the base event class. Contains the implementation of the base event class. See event_base.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	26.07.2023
 * 
*/

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "event_types/event_base.hpp"

namespace trac
{
	/**
	 * @brief	Inserter operator for the Event class. This function is used to insert an event into an output stream (i.e. to print event data).
	 * 
	 * @param os	The output stream to insert the event into.
	 * @param e	The event to insert into the output stream.
	 * @return std::ostream&	The output stream with the event inserted.
	 */
	std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

	/**
	 * @brief	Inserter operator for pointers to the Event class. This function is used to insert an event into an output stream (i.e. to print event data).
	 * 
	 * @param os	The output stream to insert the event into.
	 * @param e	The event to insert into the output stream.
	 * @return std::ostream&	The output stream with the event inserted.
	 */
	std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Event> e)
	{
		return os << e->ToString();
	}

	/**
	 * @brief	Converts the event to a string representation. This function is used to print the event data to the console.
	 * 
	 * @return std::string	The string representation of the event.
	 */
	std::string Event::ToString() const
	{
		return GetName();
	}

	/**
	 * @brief	Returns whether the event is in the provided category or not.
	 * 
	 * @param category	The category to check.
	 * @return bool	True if the event is in the provided category, false otherwise.
	 * @retval True	The event is in the provided category.
	 * @retval False	The event is not in the provided category.
	 */
	bool Event::IsInCategory(EventCategory category) const
	{
		return GetCategoryFlags() & category;
	}
} // Namespace trac