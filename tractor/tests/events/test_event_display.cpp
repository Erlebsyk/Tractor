// Google Test Framework
#include <gtest/gtest.h>

// Related header include
#include <tractor.hpp>

// Add test event data
#include "test_event_data.hpp"

namespace test
{
	static void event_display_cb(std::shared_ptr<trac::Event> e);
	static void event_display_orientation_cb(std::shared_ptr<trac::Event> e);

	class EventDisplayData : public EventBaseData
	{
	public:
		EventDisplayData() : 
			EventBaseData(),
			display_index_(0),
			orientation_(trac::DisplayOrientation::kUnknown)
		{}

		void Set(std::shared_ptr<trac::Event> e) override
		{
			EventBaseData::Set(e);

			auto event_display = std::static_pointer_cast<trac::EventDisplay>(e);
			display_index_ = event_display->GetDisplayIndex();
		}

		void SetOrientationData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_orientation = std::static_pointer_cast<trac::EventDisplayOrientation>(e);
			orientation_ = event_orientation->GetOrientation();
		}

		trac::display_index_t GetDisplayIndex() const { return display_index_; }
		trac::DisplayOrientation GetOrientation() const { return orientation_; }
		
	private:
		trac::display_index_t display_index_;
		trac::DisplayOrientation orientation_;
	};

	static EventDisplayData data_g = EventDisplayData();

	void event_display_cb(std::shared_ptr<trac::Event> e) { data_g.Set(e); }
	void event_display_orientation_cb(std::shared_ptr<trac::Event> e) { data_g.SetOrientationData(e); }

	GTEST_TEST(tractor, event_display)
	{
		trac::event_listener_remove_all();

		// Initial values should be blank / zero
		data_g = EventDisplayData();
		EXPECT_STREQ("", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kNone, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kNone, data_g.GetCategoryFlags());
		EXPECT_EQ(0, data_g.GetTimestampMs());
		EXPECT_STREQ("", data_g.GetString().c_str());
		EXPECT_EQ(nullptr, data_g.GetEvent());
		EXPECT_EQ(0, data_g.GetDisplayIndex());
		EXPECT_EQ(trac::DisplayOrientation::kUnknown, data_g.GetOrientation());

		// Register all event listeners
		trac::event_listener_add_nb(trac::EventType::kDisplayConnected, event_display_cb);
		trac::event_listener_add_nb(trac::EventType::kDisplayDisconnected, event_display_cb);
		trac::event_listener_add_nb(trac::EventType::kDisplayOrientation, event_display_orientation_cb);

		// Create a shared pointer to an event
		std::shared_ptr<trac::Event> e;
		trac::timestamp_t timestamp_ms = 0;

		// Dispatch each event type one by one
		data_g = EventDisplayData();
		e = std::make_shared<trac::EventDisplayConnected>(1);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventDisplayConnected", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kDisplayConnected, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kDisplay | trac::EventCategory::kDevice), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventDisplayConnected: [1]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(1, data_g.GetDisplayIndex());

		data_g = EventDisplayData();
		e = std::make_shared<trac::EventDisplayDisconnected>(2);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventDisplayDisconnected", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kDisplayDisconnected, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kDisplay | trac::EventCategory::kDevice), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventDisplayDisconnected: [2]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(2, data_g.GetDisplayIndex());

		data_g = EventDisplayData();
		e = std::make_shared<trac::EventDisplayOrientation>(3, trac::DisplayOrientation::kLandscape);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventDisplayOrientation", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kDisplayOrientation, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kDisplay, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventDisplayOrientation: [3, landscape]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(3, data_g.GetDisplayIndex());
		EXPECT_EQ(trac::DisplayOrientation::kLandscape, data_g.GetOrientation());
	}

} // namespace test