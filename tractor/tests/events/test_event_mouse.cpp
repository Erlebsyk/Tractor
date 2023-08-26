// Google Test Framework
#include <gtest/gtest.h>

// Related header include
#include <tractor.hpp>

// Add test event data
#include "test_event_data.hpp"

namespace test
{
	static void event_mouse_cb(std::shared_ptr<trac::Event> e);
	static void event_mouse_motion_cb(std::shared_ptr<trac::Event> e);
	static void event_mouse_button_cb(std::shared_ptr<trac::Event> e);
	static void event_mouse_clicked_cb(std::shared_ptr<trac::Event> e);
	static void event_mouse_scroll_cb(std::shared_ptr<trac::Event> e);

	struct MouseBaseData
	{
		trac::mouse_id_t mouse_id = 0;
		trac::window_id_t window_id = 0;
		trac::pos_pixel_t pos_x = 0;
		trac::pos_pixel_t pos_y = 0;
	};

	struct MouseMotionData
	{
		trac::mouse_button_state_t button_state = 0;
		trac::pos_pixel_t dx = 0;
		trac::pos_pixel_t dy = 0;
	};

	struct MouseButtonData
	{
		trac::MouseButton button = trac::MouseButton::kUnknown;
	};

	struct MouseClickedData
	{
		uint32_t clicks = 0;
	};

	struct MouseScrollData
	{
		trac::pos_pixel_t scroll_x = 0;
		trac::pos_pixel_t scroll_y = 0;
		bool flipped_ = false;
	};

	class EventMouseData : public EventBaseData
	{
	public:
		EventMouseData() :
			EventBaseData(),
			mouse_base_data_ {},
			mouse_motion_data_ {},
			mouse_button_data_ {},
			mouse_clicked_data_ {},
			mouse_scroll_data_ {}
		{}

		void Set(std::shared_ptr<trac::Event> e) override
		{
			EventBaseData::Set(e);

			auto event_mouse = std::static_pointer_cast<trac::EventMouse>(e);
			mouse_base_data_.mouse_id = event_mouse->GetMouseID();
			mouse_base_data_.window_id = event_mouse->GetWindowID();
			mouse_base_data_.pos_x = event_mouse->GetPosX();
			mouse_base_data_.pos_y = event_mouse->GetPosY();
		}

		void SetMotionData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_motion = std::static_pointer_cast<trac::EventMouseMotion>(e);
			mouse_motion_data_.button_state = event_motion->GetButtonState();
			mouse_motion_data_.dx = event_motion->GetRelX();
			mouse_motion_data_.dy = event_motion->GetRelY();
		}

		void SetButtonData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_button = std::static_pointer_cast<trac::EventMouseButton>(e);
			mouse_button_data_.button = event_button->GetButton();
		}

		void SetClickedData(std::shared_ptr<trac::Event> e)
		{
			SetButtonData(e);
			auto event_clicked = std::static_pointer_cast<trac::EventMouseButtonClicked>(e);
			mouse_clicked_data_.clicks = event_clicked->GetClicks();
		}

		void SetScrollData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_scroll = std::static_pointer_cast<trac::EventMouseWheel>(e);
			mouse_scroll_data_.scroll_x = event_scroll->GetScrollX();
			mouse_scroll_data_.scroll_y = event_scroll->GetScrollY();
			mouse_scroll_data_.flipped_ = event_scroll->IsFlipped();
		}

		MouseBaseData GetMouseBaseData() const { return mouse_base_data_; }
		MouseMotionData GetMouseMotionData() const { return mouse_motion_data_; }
		MouseButtonData GetMouseButtonData() const { return mouse_button_data_; }
		MouseClickedData GetMouseClickedData() const { return mouse_clicked_data_; }
		MouseScrollData GetMouseScrollData() const { return mouse_scroll_data_; }

	private:
		MouseBaseData mouse_base_data_;
		MouseMotionData mouse_motion_data_;
		MouseButtonData mouse_button_data_;
		MouseClickedData mouse_clicked_data_;
		MouseScrollData mouse_scroll_data_;
	};

	static EventMouseData data_g = EventMouseData();

	void event_mouse_cb(std::shared_ptr<trac::Event> e) { data_g.Set(e); }
	void event_mouse_motion_cb(std::shared_ptr<trac::Event> e) { data_g.SetMotionData(e); }
	void event_mouse_button_cb(std::shared_ptr<trac::Event> e) { data_g.SetButtonData(e); }
	void event_mouse_clicked_cb(std::shared_ptr<trac::Event> e) { data_g.SetClickedData(e); }
	void event_mouse_scroll_cb(std::shared_ptr<trac::Event> e) { data_g.SetScrollData(e); }

	GTEST_TEST(tractor, event_mouse)
	{
		trac::event_listener_remove_all();

		// Initial values should be blank / zero
		data_g = EventMouseData();
		EXPECT_STREQ("", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kNone, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kNone, data_g.GetCategoryFlags());
		EXPECT_EQ(0, data_g.GetTimestampMs());
		EXPECT_STREQ("", data_g.GetString().c_str());
		EXPECT_EQ(nullptr, data_g.GetEvent());
		EXPECT_EQ(0, data_g.GetMouseBaseData().mouse_id);
		EXPECT_EQ(0, data_g.GetMouseBaseData().window_id);
		EXPECT_EQ(0, data_g.GetMouseBaseData().pos_x);
		EXPECT_EQ(0, data_g.GetMouseBaseData().pos_y);
		EXPECT_EQ(0, data_g.GetMouseMotionData().button_state);
		EXPECT_EQ(0, data_g.GetMouseMotionData().dx);
		EXPECT_EQ(0, data_g.GetMouseMotionData().dy);
		EXPECT_EQ(trac::MouseButton::kUnknown, data_g.GetMouseButtonData().button);
		EXPECT_EQ(0, data_g.GetMouseClickedData().clicks);
		EXPECT_EQ(0, data_g.GetMouseScrollData().scroll_x);
		EXPECT_EQ(0, data_g.GetMouseScrollData().scroll_y);
		EXPECT_FALSE(data_g.GetMouseScrollData().flipped_);

		// Register all event listeners
		trac::event_listener_add_nb(trac::EventType::kMouseMotion, event_mouse_motion_cb);
		trac::event_listener_add_nb(trac::EventType::kMouseButtonDown, event_mouse_button_cb);
		trac::event_listener_add_nb(trac::EventType::kMouseButtonUp, event_mouse_button_cb);
		trac::event_listener_add_nb(trac::EventType::kMouseButtonClicked, event_mouse_clicked_cb);
		trac::event_listener_add_nb(trac::EventType::kMouseWheel, event_mouse_scroll_cb);

		// Create a shared pointer to an event
		std::shared_ptr<trac::Event> e;
		trac::timestamp_t timestamp_ms = 0;

		// Dispatch each event type one by one
		data_g = EventMouseData();
		e = std::make_shared<trac::EventMouseMotion>(1, 2, 3, 4, ((1 << 0) | (1 << 3)) , 5, 6);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventMouseMotion", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kMouseMotion, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kMouse | trac::EventCategory::kInput), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventMouseMotion: [1, 2, 3, 4], [9, (5, 6)]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(1, data_g.GetMouseBaseData().mouse_id);
		EXPECT_EQ(2, data_g.GetMouseBaseData().window_id);
		EXPECT_EQ(3, data_g.GetMouseBaseData().pos_x);
		EXPECT_EQ(4, data_g.GetMouseBaseData().pos_y);
		EXPECT_EQ(9, data_g.GetMouseMotionData().button_state);
		EXPECT_EQ(5, data_g.GetMouseMotionData().dx);
		EXPECT_EQ(6, data_g.GetMouseMotionData().dy);
		
		data_g = EventMouseData();
		e = std::make_shared<trac::EventMouseButtonDown>(2, 3, 11, 12, trac::MouseButton::kLeft);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventMouseButtonDown", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kMouseButtonDown, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kMouse | trac::EventCategory::kInput | trac::EventCategory::kButton), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventMouseButtonDown: [2, 3, 11, 12], [left]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(2, data_g.GetMouseBaseData().mouse_id);
		EXPECT_EQ(3, data_g.GetMouseBaseData().window_id);
		EXPECT_EQ(11, data_g.GetMouseBaseData().pos_x);
		EXPECT_EQ(12, data_g.GetMouseBaseData().pos_y);
		EXPECT_EQ(trac::MouseButton::kLeft, data_g.GetMouseButtonData().button);

		data_g = EventMouseData();
		e = std::make_shared<trac::EventMouseButtonUp>(3, 4, 21, 22, trac::MouseButton::kRight);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventMouseButtonUp", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kMouseButtonUp, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kMouse | trac::EventCategory::kInput | trac::EventCategory::kButton), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventMouseButtonUp: [3, 4, 21, 22], [right]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(3, data_g.GetMouseBaseData().mouse_id);
		EXPECT_EQ(4, data_g.GetMouseBaseData().window_id);
		EXPECT_EQ(21, data_g.GetMouseBaseData().pos_x);
		EXPECT_EQ(22, data_g.GetMouseBaseData().pos_y);
		EXPECT_EQ(trac::MouseButton::kRight, data_g.GetMouseButtonData().button);

		data_g = EventMouseData();
		e = std::make_shared<trac::EventMouseButtonClicked>(4, 5, 31, 32, trac::MouseButton::kMiddle, 2);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventMouseButtonClicked", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kMouseButtonClicked, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kMouse | trac::EventCategory::kInput | trac::EventCategory::kButton), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventMouseButtonClicked: [4, 5, 31, 32], [middle], [2]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(4, data_g.GetMouseBaseData().mouse_id);
		EXPECT_EQ(5, data_g.GetMouseBaseData().window_id);
		EXPECT_EQ(31, data_g.GetMouseBaseData().pos_x);
		EXPECT_EQ(32, data_g.GetMouseBaseData().pos_y);
		EXPECT_EQ(trac::MouseButton::kMiddle, data_g.GetMouseButtonData().button);
		EXPECT_EQ(2, data_g.GetMouseClickedData().clicks);

		data_g = EventMouseData();
		e = std::make_shared<trac::EventMouseWheel>(5, 6, 41, 42, 101, 102, false);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventMouseWheel", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kMouseWheel, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kMouse | trac::EventCategory::kInput), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventMouseWheel: [5, 6, 41, 42], [(101, 102), false]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(5, data_g.GetMouseBaseData().mouse_id);
		EXPECT_EQ(6, data_g.GetMouseBaseData().window_id);
		EXPECT_EQ(41, data_g.GetMouseBaseData().pos_x);
		EXPECT_EQ(42, data_g.GetMouseBaseData().pos_y);
		EXPECT_EQ(101, data_g.GetMouseScrollData().scroll_x);
		EXPECT_EQ(102, data_g.GetMouseScrollData().scroll_y);
		EXPECT_FALSE(data_g.GetMouseScrollData().flipped_);

		data_g = EventMouseData();
		e = std::make_shared<trac::EventMouseWheel>(5, 6, 41, 42, 101, 102, true);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventMouseWheel", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kMouseWheel, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kMouse | trac::EventCategory::kInput), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventMouseWheel: [5, 6, 41, 42], [(-101, -102), true]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(5, data_g.GetMouseBaseData().mouse_id);
		EXPECT_EQ(6, data_g.GetMouseBaseData().window_id);
		EXPECT_EQ(41, data_g.GetMouseBaseData().pos_x);
		EXPECT_EQ(42, data_g.GetMouseBaseData().pos_y);
		EXPECT_EQ(101, data_g.GetMouseScrollData().scroll_x);
		EXPECT_EQ(102, data_g.GetMouseScrollData().scroll_y);
		EXPECT_TRUE(data_g.GetMouseScrollData().flipped_);
	}

} // namespace test