/**
 * @file	test_event_data.cpp
 * @brief	Source file for test event data. See test_event_data.hpp for details.
 * 
 * @author	Erlend Elias Isachsen
 * @date	23.08.2023
 */

// Include the header file
#include "test_event_data.hpp"

namespace test
{
	/// @brief Construct event base data for testing with default values.
	EventBaseData::EventBaseData() : 
		name_ { "" },
		type_ { trac::EventType::kNone },
		category_flags_ { trac::EventCategory::kNone },
		timestamp_ms_ { 0 },
		string_representation_ { "" },
		event_ { nullptr }
	{}

	/**
	 * @brief	Set the internal data from an event.
	 * 
	 * @param e	Event to set data from.
	 */
	void EventBaseData::Set(std::shared_ptr<trac::Event> e)
	{
		name_ = e->GetName();
		type_ = e->GetType();
		category_flags_ = e->GetCategoryFlags();
		timestamp_ms_ = e->GetTimestampMs();
		string_representation_ = e->ToString();
		event_ = e;
	}

	/**
	 * @brief	Get the name of the event.
	 * 
	 * @return	Name of the event.
	 */
	std::string EventBaseData::GetName() const
	{
		return name_;
	}

	/**
	 * @brief	Get the type of the event.
	 * 
	 * @return	Type of the event.
	 */
	trac::EventType EventBaseData::GetType() const
	{
		return type_;
	}

	/**
	 * @brief	Get the category flags of the event.
	 * 
	 * @return	Category flags of the event.
	 */
	trac::event_category_t EventBaseData::GetCategoryFlags() const
	{
		return category_flags_;
	}

	/**
	 * @brief	Get the timestamp of the event.
	 * 
	 * @return	Timestamp of the event.
	 */
	trac::timestamp_t EventBaseData::GetTimestampMs() const
	{
		return timestamp_ms_;
	}

	/**
	 * @brief	Get the string representation of the event.
	 * 
	 * @return	String representation of the event.
	 */
	std::string EventBaseData::GetString() const
	{
		return string_representation_;
	}

	/**
	 * @brief	Get the event.
	 * 
	 * @return	Event.
	 */
	std::shared_ptr<trac::Event> EventBaseData::GetEvent() const
	{
		return event_;
	}
};