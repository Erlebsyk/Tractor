// Google Test Framework
#include <gtest/gtest.h>

// Standard library header includes
#include <memory>

// Related header include
#include <tractor.hpp>

// include test event data
#include "test_event_data.hpp"

namespace test
{
	GTEST_TEST(tractor, event_application)
	{
		trac::event_listener_remove_all();

		// Initial values should be blank
		EventTestData::Reset();
		EXPECT_STREQ("", EventTestData::GetName().c_str());
		EXPECT_EQ(trac::EventType::kNone, EventTestData::GetType());
		EXPECT_EQ(trac::EventCategory::kNone, EventTestData::GetCategoryFlags());
		EXPECT_EQ(0, EventTestData::GetTimestampMs());
		EXPECT_STREQ("", EventTestData::GetString().c_str());
		EXPECT_EQ(nullptr, EventTestData::GetEvent());

		// Register all event listeners
		trac::event_listener_add_nb(trac::EventType::kAppTerminating, EventTestData::base_cb);
		trac::event_listener_add_nb(trac::EventType::kAppLowMemory, EventTestData::base_cb);
		trac::event_listener_add_nb(trac::EventType::kAppEnteringBackground, EventTestData::base_cb);
		trac::event_listener_add_nb(trac::EventType::kAppEnteredBackground, EventTestData::base_cb);
		trac::event_listener_add_nb(trac::EventType::kAppEnteringForeground, EventTestData::base_cb);
		trac::event_listener_add_nb(trac::EventType::kAppEnteredForeground, EventTestData::base_cb);
		trac::event_listener_add_nb(trac::EventType::kAppTick, EventTestData::base_cb);
		trac::event_listener_add_nb(trac::EventType::kAppUpdated, EventTestData::base_cb);
		trac::event_listener_add_nb(trac::EventType::kAppRendered, EventTestData::base_cb);

		// Create a shared pointer to an event
		std::shared_ptr<trac::Event> e;
		trac::timestamp_t timestamp_ms = 0;
		
		// Dispatch each event type one by one
		e = std::make_shared<trac::EventAppTerminating>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAppTerminating", EventTestData::GetName().c_str());
		EXPECT_EQ(trac::EventType::kAppTerminating, EventTestData::GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, EventTestData::GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, EventTestData::GetTimestampMs());
		EXPECT_STREQ("EventAppTerminating", EventTestData::GetString().c_str());
		EXPECT_EQ(e, EventTestData::GetEvent());

		e = std::make_shared<trac::EventAppLowMemory>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAppLowMemory", EventTestData::GetName().c_str());
		EXPECT_EQ(trac::EventType::kAppLowMemory, EventTestData::GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, EventTestData::GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, EventTestData::GetTimestampMs());
		EXPECT_STREQ("EventAppLowMemory", EventTestData::GetString().c_str());
		EXPECT_EQ(e, EventTestData::GetEvent());

		e = std::make_shared<trac::EventAppEnteringBackground>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAppEnteringBackground", EventTestData::GetName().c_str());
		EXPECT_EQ(trac::EventType::kAppEnteringBackground, EventTestData::GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, EventTestData::GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, EventTestData::GetTimestampMs());
		EXPECT_STREQ("EventAppEnteringBackground", EventTestData::GetString().c_str());
		EXPECT_EQ(e, EventTestData::GetEvent());

		e = std::make_shared<trac::EventAppEnteredBackground>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAppEnteredBackground", EventTestData::GetName().c_str());
		EXPECT_EQ(trac::EventType::kAppEnteredBackground, EventTestData::GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, EventTestData::GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, EventTestData::GetTimestampMs());
		EXPECT_STREQ("EventAppEnteredBackground", EventTestData::GetString().c_str());
		EXPECT_EQ(e, EventTestData::GetEvent());

		e = std::make_shared<trac::EventAppEnteringForeground>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAppEnteringForeground", EventTestData::GetName().c_str());
		EXPECT_EQ(trac::EventType::kAppEnteringForeground, EventTestData::GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, EventTestData::GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, EventTestData::GetTimestampMs());
		EXPECT_STREQ("EventAppEnteringForeground", EventTestData::GetString().c_str());
		EXPECT_EQ(e, EventTestData::GetEvent());

		e = std::make_shared<trac::EventAppEnteredForeground>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAppEnteredForeground", EventTestData::GetName().c_str());
		EXPECT_EQ(trac::EventType::kAppEnteredForeground, EventTestData::GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, EventTestData::GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, EventTestData::GetTimestampMs());
		EXPECT_STREQ("EventAppEnteredForeground", EventTestData::GetString().c_str());
		EXPECT_EQ(e, EventTestData::GetEvent());

		e = std::make_shared<trac::EventAppTick>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAppTick", EventTestData::GetName().c_str());
		EXPECT_EQ(trac::EventType::kAppTick, EventTestData::GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, EventTestData::GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, EventTestData::GetTimestampMs());
		EXPECT_STREQ("EventAppTick", EventTestData::GetString().c_str());
		EXPECT_EQ(e, EventTestData::GetEvent());

		e = std::make_shared<trac::EventAppUpdated>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAppUpdated", EventTestData::GetName().c_str());
		EXPECT_EQ(trac::EventType::kAppUpdated, EventTestData::GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, EventTestData::GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, EventTestData::GetTimestampMs());
		EXPECT_STREQ("EventAppUpdated", EventTestData::GetString().c_str());
		EXPECT_EQ(e, EventTestData::GetEvent());

		e = std::make_shared<trac::EventAppRendered>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAppRendered", EventTestData::GetName().c_str());
		EXPECT_EQ(trac::EventType::kAppRendered, EventTestData::GetType());
		EXPECT_EQ((trac::EventCategory::kApplication | trac::EventCategory::kDisplay), EventTestData::GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, EventTestData::GetTimestampMs());
		EXPECT_STREQ("EventAppRendered", EventTestData::GetString().c_str());
		EXPECT_EQ(e, EventTestData::GetEvent());
	}
} // namespace test