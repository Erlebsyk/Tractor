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
	static void event_app_cb(std::shared_ptr<trac::Event> e);

	static EventBaseData data_g = EventBaseData();

	void event_app_cb(std::shared_ptr<trac::Event> e) { data_g.Set(e); }

	GTEST_TEST(tractor, event_application)
	{
		trac::event_listener_remove_all();

		// Initial values should be blank / zero
		data_g = EventBaseData();
		EXPECT_STREQ("", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kNone, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kNone, data_g.GetCategoryFlags());
		EXPECT_EQ(0, data_g.GetTimestampMs());
		EXPECT_STREQ("", data_g.GetString().c_str());
		EXPECT_EQ(nullptr, data_g.GetEvent());

		// Register all event listeners
		trac::event_listener_add_nb(trac::EventType::kAppTerminating, event_app_cb);
		trac::event_listener_add_nb(trac::EventType::kAppLowMemory, event_app_cb);
		trac::event_listener_add_nb(trac::EventType::kAppEnteringBackground, event_app_cb);
		trac::event_listener_add_nb(trac::EventType::kAppEnteredBackground, event_app_cb);
		trac::event_listener_add_nb(trac::EventType::kAppEnteringForeground, event_app_cb);
		trac::event_listener_add_nb(trac::EventType::kAppEnteredForeground, event_app_cb);
		trac::event_listener_add_nb(trac::EventType::kAppTick, event_app_cb);
		trac::event_listener_add_nb(trac::EventType::kAppUpdated, event_app_cb);
		trac::event_listener_add_nb(trac::EventType::kAppRendered, event_app_cb);

		// Create a shared pointer to an event
		std::shared_ptr<trac::Event> e;
		trac::timestamp_t timestamp_ms = 0;
		
		// Dispatch each event type one by one
		e = std::make_shared<trac::EventAppTerminating>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAppTerminating", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kAppTerminating, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventAppTerminating", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());

		e = std::make_shared<trac::EventAppLowMemory>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAppLowMemory", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kAppLowMemory, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventAppLowMemory", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());

		e = std::make_shared<trac::EventAppEnteringBackground>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAppEnteringBackground", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kAppEnteringBackground, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventAppEnteringBackground", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());

		e = std::make_shared<trac::EventAppEnteredBackground>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAppEnteredBackground", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kAppEnteredBackground, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventAppEnteredBackground", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());

		e = std::make_shared<trac::EventAppEnteringForeground>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAppEnteringForeground", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kAppEnteringForeground, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventAppEnteringForeground", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());

		e = std::make_shared<trac::EventAppEnteredForeground>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAppEnteredForeground", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kAppEnteredForeground, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventAppEnteredForeground", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());

		e = std::make_shared<trac::EventAppTick>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAppTick", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kAppTick, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventAppTick", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());

		e = std::make_shared<trac::EventAppUpdated>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAppUpdated", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kAppUpdated, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventAppUpdated", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());

		e = std::make_shared<trac::EventAppRendered>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAppRendered", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kAppRendered, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kApplication | trac::EventCategory::kDisplay), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventAppRendered", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
	}
} // namespace test