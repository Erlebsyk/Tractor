// Google Test Framework
#include <gtest/gtest.h>

// Related header include
#include <tractor.hpp>

// Add test event data
#include "test_event_data.hpp"

namespace test
{
	static void event_system_cb(std::shared_ptr<trac::Event> e);
	static void event_system_drop_cb(std::shared_ptr<trac::Event> e);

	struct EventDropData
	{
		std::string drop = "";
		trac::window_id_t window_id = 0;
	};

	class EventSystemData : public EventBaseData
	{
	public:
		EventSystemData() :
			EventBaseData(),
			drop_data_()
		{}

		void Set(std::shared_ptr<trac::Event> e) override
		{
			EventBaseData::Set(e);
		}

		void SetDropData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_drop = std::static_pointer_cast<trac::EventDrop>(e);
			drop_data_.drop = event_drop->GetDrop();
			drop_data_.window_id = event_drop->GetWindowId();
		}

		EventDropData GetDropData() const { return drop_data_; }

	private:
		EventDropData drop_data_;
	};

	static EventSystemData data_g = EventSystemData();

	void event_system_cb(std::shared_ptr<trac::Event> e) { data_g.Set(e); }
	void event_system_drop_cb(std::shared_ptr<trac::Event> e) { data_g.SetDropData(e); }

	GTEST_TEST(tractor, event_system)
	{
		trac::event_listener_remove_all();

		// Initial values should be blank / zero
		data_g = EventSystemData();
		EXPECT_STREQ("", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kNone, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kNone, data_g.GetCategoryFlags());
		EXPECT_EQ(0, data_g.GetTimestampMs());
		EXPECT_STREQ("", data_g.GetString().c_str());
		EXPECT_EQ(nullptr, data_g.GetEvent());
		EXPECT_EQ("", data_g.GetDropData().drop);
		EXPECT_EQ(0, data_g.GetDropData().window_id);

		// Register all event listeners
		trac::event_listener_add_nb(trac::EventType::kQuit, event_system_cb);
		trac::event_listener_add_nb(trac::EventType::kLocaleChanged, event_system_cb);
		trac::event_listener_add_nb(trac::EventType::kClipboardUpdate, event_system_cb);
		trac::event_listener_add_nb(trac::EventType::kDropFile, event_system_drop_cb);
		trac::event_listener_add_nb(trac::EventType::kDropText, event_system_drop_cb);
		trac::event_listener_add_nb(trac::EventType::kDropBegin, event_system_drop_cb);
		trac::event_listener_add_nb(trac::EventType::kDropComplete, event_system_drop_cb);

		// Create a shared pointer to an event
		std::shared_ptr<trac::Event> e;
		trac::timestamp_t timestamp_ms = 0;

		// Dispatch each event type one by one
		data_g = EventSystemData();
		e = std::make_shared<trac::EventQuit>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventQuit", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kQuit, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventQuit", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());

		data_g = EventSystemData();
		e = std::make_shared<trac::EventLocaleChanged>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventLocaleChanged", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kLocaleChanged, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventLocaleChanged", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());

		data_g = EventSystemData();
		e = std::make_shared<trac::EventClipboardUpdate>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventClipboardUpdate", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kClipboardUpdate, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kApplication, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventClipboardUpdate", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());

		data_g = EventSystemData();
		e = std::make_shared<trac::EventDropFile>("test.txt", 1);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventDropFile", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kDropFile, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kApplication | trac::EventCategory::kInput), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventDropFile: [\"test.txt\", 1]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ("test.txt", data_g.GetDropData().drop);
		EXPECT_EQ(1, data_g.GetDropData().window_id);

		data_g = EventSystemData();
		e = std::make_shared<trac::EventDropText>("test", 2);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventDropText", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kDropText, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kApplication | trac::EventCategory::kInput), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventDropText: [\"test\", 2]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ("test", data_g.GetDropData().drop);
		EXPECT_EQ(2, data_g.GetDropData().window_id);

		data_g = EventSystemData();
		e = std::make_shared<trac::EventDropBegin>(3);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventDropBegin", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kDropBegin, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kApplication | trac::EventCategory::kInput), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventDropBegin: [3]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(3, data_g.GetDropData().window_id);

		data_g = EventSystemData();
		e = std::make_shared<trac::EventDropComplete>(4);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventDropComplete", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kDropComplete, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kApplication | trac::EventCategory::kInput), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventDropComplete: [4]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(4, data_g.GetDropData().window_id);
	}
} // namespace test