// Google Test Framework
#include <gtest/gtest.h>

// Related header include
#include <tractor.hpp>

// Add test event data
#include "test_event_data.hpp"

namespace test
{
	static void event_gesture_dollar_cb(std::shared_ptr<trac::Event> e);
	static void event_gesture_multi_cb(std::shared_ptr<trac::Event> e);

	struct GestureBaseData
	{
		trac::timestamp_t timestamp_ms = 0;
		trac::GestureData gesture_data = trac::GestureData();
	};

	struct GestureDollarData
	{
		float error = 0.0f;
	};

	struct GestureMultiData
	{
		trac::pos_rel_t d_theta = 0.0f;
		trac::pos_rel_t d_dist = 0.0f;
	};
	
	class EventGestureData : public EventBaseData
	{
	public:
		EventGestureData() : 
			EventBaseData(),
			base_data_ {},
			dollar_data_ {},
			multi_data_ {}
		{}

		void Set(std::shared_ptr<trac::Event> e) override
		{
			EventBaseData::Set(e);

			auto event_gesture = std::static_pointer_cast<trac::EventGesture>(e);
			base_data_.timestamp_ms = event_gesture->GetTimestampMs();
			base_data_.gesture_data.gesture_id = event_gesture->GetGestureId();
			base_data_.gesture_data.touch_id = event_gesture->GetTouchId();
			base_data_.gesture_data.num_fingers = event_gesture->GetNumFingers();
			base_data_.gesture_data.pos_x = event_gesture->GetPosX();
			base_data_.gesture_data.pos_y = event_gesture->GetPosY();
		}

		void SetDollarData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_dollar = std::static_pointer_cast<trac::EventDollarGesture>(e);
			dollar_data_.error = event_dollar->GetError();
		}

		void SetMultiData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_multi = std::static_pointer_cast<trac::EventMultiGesture>(e);
			multi_data_.d_theta = event_multi->GetDTheta();
			multi_data_.d_dist = event_multi->GetDDistance();
		}

		GestureBaseData GetBaseData() const { return base_data_; }
		GestureDollarData GetDollarData() const { return dollar_data_; }
		GestureMultiData GetMultiData() const { return multi_data_; }

	private:
		GestureBaseData base_data_;
		GestureDollarData dollar_data_;
		GestureMultiData multi_data_;
	};

	static EventGestureData data_g = EventGestureData();

	void event_gesture_dollar_cb(std::shared_ptr<trac::Event> e) { data_g.SetDollarData(e); }
	void event_gesture_multi_cb(std::shared_ptr<trac::Event> e) { data_g.SetMultiData(e); }

	GTEST_TEST(tractor, event_gesture)
	{
		trac::event_listener_remove_all();

		// Initial values should be blank / zero
		data_g = EventGestureData();
		EXPECT_STREQ("", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kNone, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kNone, data_g.GetCategoryFlags());
		EXPECT_EQ(0, data_g.GetTimestampMs());
		EXPECT_STREQ("", data_g.GetString().c_str());
		EXPECT_EQ(nullptr, data_g.GetEvent());
		EXPECT_EQ(0, data_g.GetBaseData().gesture_data.gesture_id);
		EXPECT_EQ(0, data_g.GetBaseData().gesture_data.touch_id);
		EXPECT_EQ(0, data_g.GetBaseData().gesture_data.num_fingers);
		EXPECT_FLOAT_EQ(0.0f, data_g.GetBaseData().gesture_data.pos_x);
		EXPECT_FLOAT_EQ(0.0f, data_g.GetBaseData().gesture_data.pos_y);
		EXPECT_FLOAT_EQ(0.0f, data_g.GetDollarData().error);
		EXPECT_FLOAT_EQ(0.0f, data_g.GetMultiData().d_theta);
		EXPECT_FLOAT_EQ(0.0f, data_g.GetMultiData().d_dist);

		// Add event listeners
		trac::event_listener_add_nb(trac::EventType::kDollarGesture, event_gesture_dollar_cb);
		trac::event_listener_add_nb(trac::EventType::kDollarRecord, event_gesture_dollar_cb);
		trac::event_listener_add_nb(trac::EventType::kMultiGesture, event_gesture_multi_cb);

		// Create a shared pointer to an event
		std::shared_ptr<trac::Event> e;
		trac::timestamp_t timestamp_ms = 0;

		// Dispatch each event type one by one
		data_g = EventGestureData();
		e = std::make_shared<trac::EventDollarGesture>(
			trac::GestureData(1, 2, 3, 4.5f, 6.7f),
			1.23f
		);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventDollarGesture", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kDollarGesture, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kInput, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventDollarGesture: [1, 2, 3, 4.5, 6.7]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(1, data_g.GetBaseData().gesture_data.gesture_id);
		EXPECT_EQ(2, data_g.GetBaseData().gesture_data.touch_id);
		EXPECT_EQ(3, data_g.GetBaseData().gesture_data.num_fingers);
		EXPECT_FLOAT_EQ(4.5f, data_g.GetBaseData().gesture_data.pos_x);
		EXPECT_FLOAT_EQ(6.7f, data_g.GetBaseData().gesture_data.pos_y);
		EXPECT_FLOAT_EQ(1.23f, data_g.GetDollarData().error);

		data_g = EventGestureData();
		e = std::make_shared<trac::EventDollarRecord>(
			trac::GestureData(4, 5, 6, 7.8f, 9.0f),
			10.11f
		);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventDollarRecord", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kDollarRecord, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kInput, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventDollarRecord: [4, 5, 6, 7.8, 9]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(4, data_g.GetBaseData().gesture_data.gesture_id);
		EXPECT_EQ(5, data_g.GetBaseData().gesture_data.touch_id);
		EXPECT_EQ(6, data_g.GetBaseData().gesture_data.num_fingers);
		EXPECT_FLOAT_EQ(7.8f, data_g.GetBaseData().gesture_data.pos_x);
		EXPECT_FLOAT_EQ(9.0f, data_g.GetBaseData().gesture_data.pos_y);

		data_g = EventGestureData();
		e = std::make_shared<trac::EventMultiGesture>(
			trac::GestureData(7, 8, 9, 10.11f, 12.13f),
			14.15f,
			16.17f
		);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventMultiGesture", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kMultiGesture, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kInput, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventMultiGesture: [7, 8, 9, 10.11, 12.13], [14.15, 16.17]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(7, data_g.GetBaseData().gesture_data.gesture_id);
		EXPECT_EQ(8, data_g.GetBaseData().gesture_data.touch_id);
		EXPECT_EQ(9, data_g.GetBaseData().gesture_data.num_fingers);
		EXPECT_FLOAT_EQ(10.11f, data_g.GetBaseData().gesture_data.pos_x);
		EXPECT_FLOAT_EQ(12.13f, data_g.GetBaseData().gesture_data.pos_y);
		EXPECT_FLOAT_EQ(14.15f, data_g.GetMultiData().d_theta);
		EXPECT_FLOAT_EQ(16.17f, data_g.GetMultiData().d_dist);
	}

} // namespace test