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
	std::string EventTestData::name_ = "";
	trac::EventType EventTestData::type_ = trac::EventType::kNone;
	trac::event_category_t EventTestData::category_flags_ = trac::EventCategory::kNone;
	trac::timestamp_t EventTestData::timestamp_ms_ = 0;
	std::string EventTestData::string_representation_ = "";
	std::shared_ptr<trac::Event> EventTestData::event_ = nullptr;
};