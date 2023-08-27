// Google Test Framework
#include <gtest/gtest.h>

// Related header include
#include <tractor.hpp>

// include test event data
#include "test_event_data.hpp"

namespace test
{
	static void event_touch_cb(std::shared_ptr<trac::Event> e);

	struct TouchData
	{
		trac::window_id_t window_id = 0;
		trac::touch_id_t touch_id = 0;
		trac::TouchPoint touch_point = trac::TouchPoint();
	};

	class EventTouchData : public EventBaseData
	{
	public:
		EventTouchData() : 
			EventBaseData(),
			touch_data_()
		{}

		void Set(std::shared_ptr<trac::Event> e) override
		{
			EventBaseData::Set(e);

			auto event_touch = std::dynamic_pointer_cast<trac::EventTouch>(e);
			touch_data_.window_id = event_touch->GetWindowID();
			touch_data_.touch_id = event_touch->GetTouchID();
			touch_data_.touch_point = event_touch->GetTouchPoint();
		}

		TouchData GetTouchData() const { return touch_data_; }

	private:
		TouchData touch_data_;
	};

	static EventTouchData data_g = EventTouchData();

	void event_touch_cb(std::shared_ptr<trac::Event> e) { data_g.Set(e); }

	GTEST_TEST(tractor, event_touch)
	{
		trac::event_listener_remove_all();

		// Initial values should be blank / zero
		data_g = EventTouchData();
		EXPECT_STREQ("", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kNone, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kNone, data_g.GetCategoryFlags());
		EXPECT_EQ(0, data_g.GetTimestampMs());
		EXPECT_STREQ("", data_g.GetString().c_str());
		EXPECT_EQ(nullptr, data_g.GetEvent());
		EXPECT_EQ(0, data_g.GetTouchData().window_id);
		EXPECT_EQ(0, data_g.GetTouchData().touch_id);
		EXPECT_EQ(0, data_g.GetTouchData().touch_point.finger_id);
		EXPECT_FLOAT_EQ(0.0f, data_g.GetTouchData().touch_point.pos_x);
		EXPECT_FLOAT_EQ(0.0f, data_g.GetTouchData().touch_point.pos_y);
		EXPECT_FLOAT_EQ(0.0f, data_g.GetTouchData().touch_point.dx);
		EXPECT_FLOAT_EQ(0.0f, data_g.GetTouchData().touch_point.dy);
		EXPECT_FLOAT_EQ(0.0f, data_g.GetTouchData().touch_point.pressure);

		// Register all event listeners
		trac::event_listener_add_nb(trac::EventType::kFingerDown, event_touch_cb);
		trac::event_listener_add_nb(trac::EventType::kFingerUp, event_touch_cb);
		trac::event_listener_add_nb(trac::EventType::kFingerMotion, event_touch_cb);

		// Create a shared pointer to an event
		std::shared_ptr<trac::Event> e;
		trac::timestamp_t timestamp_ms = 0;

		// Dispatch each event type one by one
		data_g = EventTouchData();
		e = std::make_shared<trac::EventFingerDown>(1, 2, trac::TouchPoint(3, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f));
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventFingerDown", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kFingerDown, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kTouch | trac::EventCategory::kInput), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventFingerDown: [1, 2, 3, (4, 5), (6, 7), 8]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(1, data_g.GetTouchData().window_id);
		EXPECT_EQ(2, data_g.GetTouchData().touch_id);
		EXPECT_EQ(3, data_g.GetTouchData().touch_point.finger_id);
		EXPECT_FLOAT_EQ(4.0f, data_g.GetTouchData().touch_point.pos_x);
		EXPECT_FLOAT_EQ(5.0f, data_g.GetTouchData().touch_point.pos_y);
		EXPECT_FLOAT_EQ(6.0f, data_g.GetTouchData().touch_point.dx);
		EXPECT_FLOAT_EQ(7.0f, data_g.GetTouchData().touch_point.dy);
		EXPECT_FLOAT_EQ(8.0f, data_g.GetTouchData().touch_point.pressure);

		data_g = EventTouchData();
		e = std::make_shared<trac::EventFingerUp>(2, 3, trac::TouchPoint(4, 5.5f, 6.6f, 7.7f, 8.8f, 9.99f));
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventFingerUp", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kFingerUp, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kTouch | trac::EventCategory::kInput), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventFingerUp: [2, 3, 4, (5.5, 6.6), (7.7, 8.8), 9.99]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(2, data_g.GetTouchData().window_id);
		EXPECT_EQ(3, data_g.GetTouchData().touch_id);
		EXPECT_EQ(4, data_g.GetTouchData().touch_point.finger_id);
		EXPECT_FLOAT_EQ(5.5f, data_g.GetTouchData().touch_point.pos_x);
		EXPECT_FLOAT_EQ(6.6f, data_g.GetTouchData().touch_point.pos_y);
		EXPECT_FLOAT_EQ(7.7f, data_g.GetTouchData().touch_point.dx);
		EXPECT_FLOAT_EQ(8.8f, data_g.GetTouchData().touch_point.dy);
		EXPECT_FLOAT_EQ(9.99f, data_g.GetTouchData().touch_point.pressure);

		data_g = EventTouchData();
		e = std::make_shared<trac::EventFingerMotion>(3, 4, trac::TouchPoint(5, 6.6f, 7.7f, 8.8f, 9.9f, 10.10f));
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventFingerMotion", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kFingerMotion, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kTouch | trac::EventCategory::kInput), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventFingerMotion: [3, 4, 5, (6.6, 7.7), (8.8, 9.9), 10.1]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(3, data_g.GetTouchData().window_id);
		EXPECT_EQ(4, data_g.GetTouchData().touch_id);
		EXPECT_EQ(5, data_g.GetTouchData().touch_point.finger_id);
		EXPECT_FLOAT_EQ(6.6f, data_g.GetTouchData().touch_point.pos_x);
		EXPECT_FLOAT_EQ(7.7f, data_g.GetTouchData().touch_point.pos_y);
		EXPECT_FLOAT_EQ(8.8f, data_g.GetTouchData().touch_point.dx);
		EXPECT_FLOAT_EQ(9.9f, data_g.GetTouchData().touch_point.dy);
		EXPECT_FLOAT_EQ(10.10f, data_g.GetTouchData().touch_point.pressure);
	}

} // namespace test