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
	/// @brief Simple "static" class containing event data that is obtainable from all event types.
	class EventTestData
	{
	private:
		/// @brief Prevent instantiation of this class.
		EventTestData() {}

	protected:
		static std::string name_;
		static trac::EventType type_;
		static trac::event_category_t category_flags_;
		static trac::timestamp_t timestamp_ms_;
		static std::string string_representation_;
		static std::shared_ptr<trac::Event> event_;

		static void SetBaseData(std::shared_ptr<trac::Event> e)
		{
			name_ = e->GetName();
			type_ = e->GetType();
			category_flags_ = e->GetCategoryFlags();
			timestamp_ms_ = e->GetTimestampMs();
			string_representation_ = e->ToString();
			event_ = e;
		}

	public:
		static std::string GetName() { return name_; }
		static trac::EventType GetType() { return type_; }
		static trac::event_category_t GetCategoryFlags() { return category_flags_; }
		static trac::timestamp_t GetTimestampMs() { return timestamp_ms_; }
		static std::string GetString() { return string_representation_; }
		static std::shared_ptr<trac::Event> GetEvent() { return event_; }

		static void Reset()
		{
			name_ = "";
			type_ = trac::EventType::kNone;
			category_flags_ = trac::EventCategory::kNone;
			timestamp_ms_ = 0;
			string_representation_ = "";
			event_ = nullptr;
		}

		static void base_cb(std::shared_ptr<trac::Event> e) { SetBaseData(e); }
	};
}

#endif // TEST_EVENT_DATA_HPP_