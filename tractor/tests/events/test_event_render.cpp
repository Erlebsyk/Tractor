// Google Test Framework
#include <gtest/gtest.h>

// Related header include
#include <tractor.hpp>

// include test event data
#include "test_event_data.hpp"

namespace test
{
	static void event_render_cb(std::shared_ptr<trac::Event> e);

	static EventBaseData data_g = EventBaseData();

	void event_render_cb(std::shared_ptr<trac::Event> e) { data_g.Set(e); }

	GTEST_TEST(tractor, event_render)
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
		trac::event_listener_add_nb(trac::EventType::kRenderTargetsReset, event_render_cb);
		trac::event_listener_add_nb(trac::EventType::kRenderDeviceReset, event_render_cb);

		// Create a shared pointer to an event
		std::shared_ptr<trac::Event> e;
		trac::timestamp_t timestamp_ms = 0;

		// Dispatch each event type one by one
		e = std::make_shared<trac::EventRenderTargetsReset>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventRenderTargetsReset", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kRenderTargetsReset, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventRenderTargetsReset", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());

		e = std::make_shared<trac::EventRenderDeviceReset>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventRenderDeviceReset", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kRenderDeviceReset, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kDevice, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventRenderDeviceReset", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
	}
} // namespace test