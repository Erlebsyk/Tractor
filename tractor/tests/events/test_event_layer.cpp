// Google Test Framework
#include <gtest/gtest.h>

// Related header include
#include <tractor.hpp>

// include test event data
#include "test_event_data.hpp"

namespace test
{
	static void event_layer_cb(std::shared_ptr<trac::Event> e);

	static EventBaseData data_g = EventBaseData();

	void event_layer_cb(std::shared_ptr<trac::Event> e) { data_g.Set(e); }

	GTEST_TEST(tractor, event_layer)
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
		trac::event_listener_add_nb(trac::EventType::kLayerPushed, event_layer_cb);
		trac::event_listener_add_nb(trac::EventType::kLayerPopped, event_layer_cb);
		trac::event_listener_add_nb(trac::EventType::kLayerUpdated, event_layer_cb);
		trac::event_listener_add_nb(trac::EventType::kLayerAttached, event_layer_cb);
		trac::event_listener_add_nb(trac::EventType::kLayerDetached, event_layer_cb);

		// Create a shared pointer to an event
		std::shared_ptr<trac::Event> e;
		trac::timestamp_t timestamp_ms = 0;

		// Dispatch each event type one by one
		e = std::make_shared<trac::EventLayerPushed>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);

		// Expect nothing before processing the event queue
		EXPECT_STREQ("", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kNone, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kNone, data_g.GetCategoryFlags());
		EXPECT_EQ(0, data_g.GetTimestampMs());
		EXPECT_STREQ("", data_g.GetString().c_str());
		EXPECT_EQ(nullptr, data_g.GetEvent());

		// Process the event queue
		trac::event_queue_process();
		EXPECT_STREQ("EventLayerPushed", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kLayerPushed, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		std::string expected = "EventLayerPushed: [" + std::to_string(timestamp_ms) + " ms]";
		EXPECT_STREQ(expected.c_str(), data_g.GetString().c_str());

		// Dispatch the next event type
		e = std::make_shared<trac::EventLayerPopped>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventLayerPopped", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kLayerPopped, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		expected = "EventLayerPopped: [" + std::to_string(timestamp_ms) + " ms]";
		EXPECT_STREQ(expected.c_str(), data_g.GetString().c_str());

		// Dispatch the next event type
		e = std::make_shared<trac::EventLayerUpdated>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventLayerUpdated", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kLayerUpdated, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		expected = "EventLayerUpdated: [" + std::to_string(timestamp_ms) + " ms]";
		EXPECT_STREQ(expected.c_str(), data_g.GetString().c_str());

		// Dispatch the next event type
		e = std::make_shared<trac::EventLayerAttached>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventLayerAttached", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kLayerAttached, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		expected = "EventLayerAttached: [" + std::to_string(timestamp_ms) + " ms]";
		EXPECT_STREQ(expected.c_str(), data_g.GetString().c_str());

		// Dispatch the next event type
		e = std::make_shared<trac::EventLayerDetached>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventLayerDetached", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kLayerDetached, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		expected = "EventLayerDetached: [" + std::to_string(timestamp_ms) + " ms]";
		EXPECT_STREQ(expected.c_str(), data_g.GetString().c_str());
	}
}