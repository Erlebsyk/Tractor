/**
 * @file	test_event_data.hpp
 * @brief	Contains a simple "static" class containing event data.
 * 
 * @author	Erlend Elias Isachsen
 * @date	23.08.2023
 */

#ifndef TEST_EVENT_DATA_HPP_
#define TEST_EVENT_DATA_HPP_

// Include the tractor header file
#include <tractor.hpp>

// Standard library header includes
#include <string>
#include <memory>

namespace test
{
	/**
	 * @brief	Simple class containing event data.
	 * 
	 * This class is used to store event data from an event callback function. The data can then be used to verify that the event callback function was called
	 * with the correct data. The event data can only be set through the Set() function, and will be set to default values when the class is created.
	 */
	class EventBaseData
	{
	public:
		EventBaseData();

		virtual void Set(std::shared_ptr<trac::Event> e);

		std::string GetName() const;
		trac::EventType GetType() const;
		trac::event_category_t GetCategoryFlags() const;
		trac::timestamp_t GetTimestampMs() const;
		std::string GetString() const;
		std::shared_ptr<trac::Event> GetEvent() const;

	private:
		std::string name_;
		trac::EventType type_;
		trac::event_category_t category_flags_;
		trac::timestamp_t timestamp_ms_;
		std::string string_representation_;
		std::shared_ptr<trac::Event> event_;
	};
}

#endif // TEST_EVENT_DATA_HPP_