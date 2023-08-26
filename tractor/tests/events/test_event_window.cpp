// Google Test Framework
#include <gtest/gtest.h>

// Related header include
#include <tractor.hpp>

// include test event data
#include "test_event_data.hpp"

namespace test
{
	static void event_window_cb(std::shared_ptr<trac::Event> e);
	static void event_window_moved_cb(std::shared_ptr<trac::Event> e);
	static void event_window_resize_cb(std::shared_ptr<trac::Event> e);
	static void event_window_display_cb(std::shared_ptr<trac::Event> e);

	struct WindowBaseData
	{
		trac::window_id_t window_id = 0;
	};

	struct WindowPixelData
	{
		trac::pos_pixel_t x = 0;
		trac::pos_pixel_t y = 0;
	};

	struct WindowDisplayData
	{
		trac::display_index_t index = 0;
	};

	class EventWindowData : public EventBaseData
	{
	public:
		EventWindowData() :
			base_data_ {},
			pixel_data_ {},
			display_data_ {}
		{}

		void Set(std::shared_ptr<trac::Event> e)
		{
			EventBaseData::Set(e);
			auto event_window = std::static_pointer_cast<trac::EventWindow>(e);
			base_data_.window_id = event_window->GetWindowID();
		}

		void SetMovedData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_window_moved = std::static_pointer_cast<trac::EventWindowMoved>(e);
			pixel_data_.x = event_window_moved->GetPosX();
			pixel_data_.y = event_window_moved->GetPosY();
		}

		void SetSizeData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_window_size = std::static_pointer_cast<trac::EventWindowResized>(e);
			pixel_data_.x = event_window_size->GetWidth();
			pixel_data_.y = event_window_size->GetHeight();
		}

		void SetDisplayData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_window_display = std::static_pointer_cast<trac::EventWindowDisplayChanged>(e);
			display_data_.index = event_window_display->GetDisplayIndex();
		}

		WindowBaseData GetBaseData() const { return base_data_; }
		WindowPixelData GetPixelData() const { return pixel_data_; }
		WindowDisplayData GetDisplayData() const { return display_data_; }

	private:
		WindowBaseData base_data_;
		WindowPixelData pixel_data_;
		WindowDisplayData display_data_;
	};

	static EventWindowData data_g = EventWindowData();

	void event_window_cb(std::shared_ptr<trac::Event> e) { data_g.Set(e); }
	void event_window_moved_cb(std::shared_ptr<trac::Event> e) { data_g.SetMovedData(e); }
	void event_window_resize_cb(std::shared_ptr<trac::Event> e) { data_g.SetSizeData(e); }
	void event_window_display_cb(std::shared_ptr<trac::Event> e) { data_g.SetDisplayData(e); }

	GTEST_TEST(tractor, event_window)
	{
		trac::event_listener_remove_all();

		// Initial values should be blank / zero
		data_g = EventWindowData();
		EXPECT_STREQ("", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kNone, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kNone, data_g.GetCategoryFlags());
		EXPECT_EQ(0, data_g.GetTimestampMs());
		EXPECT_STREQ("", data_g.GetString().c_str());
		EXPECT_EQ(nullptr, data_g.GetEvent());
		EXPECT_EQ(0, data_g.GetBaseData().window_id);
		EXPECT_EQ(0, data_g.GetPixelData().x);
		EXPECT_EQ(0, data_g.GetPixelData().y);
		EXPECT_EQ(0, data_g.GetDisplayData().index);

		// Register all event listeners
		trac::event_listener_add_nb(trac::EventType::kWindowShown, event_window_cb);
		trac::event_listener_add_nb(trac::EventType::kWindowHidden, event_window_cb);
		trac::event_listener_add_nb(trac::EventType::kWindowExposed, event_window_cb);
		trac::event_listener_add_nb(trac::EventType::kWindowMoved, event_window_moved_cb);
		trac::event_listener_add_nb(trac::EventType::kWindowResized, event_window_resize_cb);
		trac::event_listener_add_nb(trac::EventType::kWindowSizeChanged, event_window_cb);
		trac::event_listener_add_nb(trac::EventType::kWindowMinimized, event_window_cb);
		trac::event_listener_add_nb(trac::EventType::kWindowMaximized, event_window_cb);
		trac::event_listener_add_nb(trac::EventType::kWindowRestored, event_window_cb);
		trac::event_listener_add_nb(trac::EventType::kWindowEnter, event_window_cb);
		trac::event_listener_add_nb(trac::EventType::kWindowLeave, event_window_cb);
		trac::event_listener_add_nb(trac::EventType::kWindowFocusGained, event_window_cb);
		trac::event_listener_add_nb(trac::EventType::kWindowFocusLost, event_window_cb);
		trac::event_listener_add_nb(trac::EventType::kWindowTakeFocus, event_window_cb);
		trac::event_listener_add_nb(trac::EventType::kWindowHitTest, event_window_cb);
		trac::event_listener_add_nb(trac::EventType::kWindowIccProfileChanged, event_window_cb);
		trac::event_listener_add_nb(trac::EventType::kWindowDisplayChanged, event_window_display_cb);
		trac::event_listener_add_nb(trac::EventType::kWindowClosed, event_window_cb);

		// Create a shared pointer to an event
		std::shared_ptr<trac::Event> e;
		trac::timestamp_t timestamp_ms = 0;

		// Dispatch each event type one by one
		data_g = EventWindowData();
		e = std::make_shared<trac::EventWindowShown>(1);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventWindowShown", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kWindowShown, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kWindow , data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventWindowShown: [1]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(1, data_g.GetBaseData().window_id);

		data_g = EventWindowData();
		e = std::make_shared<trac::EventWindowHidden>(2);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventWindowHidden", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kWindowHidden, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kWindow, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventWindowHidden: [2]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(2, data_g.GetBaseData().window_id);

		data_g = EventWindowData();
		e = std::make_shared<trac::EventWindowExposed>(3);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventWindowExposed", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kWindowExposed, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kWindow, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventWindowExposed: [3]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(3, data_g.GetBaseData().window_id);

		data_g = EventWindowData();
		e = std::make_shared<trac::EventWindowMoved>(4, 5, 6);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventWindowMoved", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kWindowMoved, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kWindow, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventWindowMoved: [4], [5, 6]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(4, data_g.GetBaseData().window_id);
		EXPECT_EQ(5, data_g.GetPixelData().x);
		EXPECT_EQ(6, data_g.GetPixelData().y);

		data_g = EventWindowData();
		e = std::make_shared<trac::EventWindowResized>(7, 8, 9);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventWindowResized", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kWindowResized, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kWindow, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventWindowResized: [7], [8, 9]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(7, data_g.GetBaseData().window_id);
		EXPECT_EQ(8, data_g.GetPixelData().x);
		EXPECT_EQ(9, data_g.GetPixelData().y);

		data_g = EventWindowData();
		e = std::make_shared<trac::EventWindowSizeChanged>(10);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventWindowSizeChanged", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kWindowSizeChanged, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kWindow, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventWindowSizeChanged: [10]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(10, data_g.GetBaseData().window_id);

		data_g = EventWindowData();
		e = std::make_shared<trac::EventWindowMinimized>(11);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventWindowMinimized", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kWindowMinimized, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kWindow, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventWindowMinimized: [11]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(11, data_g.GetBaseData().window_id);

		data_g = EventWindowData();
		e = std::make_shared<trac::EventWindowMaximized>(12);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventWindowMaximized", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kWindowMaximized, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kWindow, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventWindowMaximized: [12]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(12, data_g.GetBaseData().window_id);
		
		data_g = EventWindowData();
		e = std::make_shared<trac::EventWindowRestored>(13);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventWindowRestored", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kWindowRestored, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kWindow, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventWindowRestored: [13]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(13, data_g.GetBaseData().window_id);

		data_g = EventWindowData();
		e = std::make_shared<trac::EventWindowEnter>(14);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventWindowEnter", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kWindowEnter, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kWindow, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventWindowEnter: [14]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(14, data_g.GetBaseData().window_id);

		data_g = EventWindowData();
		e = std::make_shared<trac::EventWindowLeave>(15);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventWindowLeave", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kWindowLeave, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kWindow, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventWindowLeave: [15]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(15, data_g.GetBaseData().window_id);

		data_g = EventWindowData();
		e = std::make_shared<trac::EventWindowFocusGained>(16);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventWindowFocusGained", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kWindowFocusGained, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kWindow, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventWindowFocusGained: [16]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(16, data_g.GetBaseData().window_id);

		data_g = EventWindowData();
		e = std::make_shared<trac::EventWindowFocusLost>(17);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventWindowFocusLost", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kWindowFocusLost, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kWindow, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventWindowFocusLost: [17]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(17, data_g.GetBaseData().window_id);

		data_g = EventWindowData();
		e = std::make_shared<trac::EventWindowTakeFocus>(18);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventWindowTakeFocus", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kWindowTakeFocus, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kWindow, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventWindowTakeFocus: [18]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(18, data_g.GetBaseData().window_id);

		data_g = EventWindowData();
		e = std::make_shared<trac::EventWindowHitTest>(19);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventWindowHitTest", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kWindowHitTest, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kWindow, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventWindowHitTest: [19]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(19, data_g.GetBaseData().window_id);

		data_g = EventWindowData();
		e = std::make_shared<trac::EventWindowIccProfileChanged>(20);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventWindowIccProfileChanged", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kWindowIccProfileChanged, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kWindow, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventWindowIccProfileChanged: [20]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(20, data_g.GetBaseData().window_id);

		data_g = EventWindowData();
		e = std::make_shared<trac::EventWindowDisplayChanged>(21, 22);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventWindowDisplayChanged", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kWindowDisplayChanged, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kWindow, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventWindowDisplayChanged: [21], [22]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(21, data_g.GetBaseData().window_id);
		EXPECT_EQ(22, data_g.GetDisplayData().index);

		data_g = EventWindowData();
		e = std::make_shared<trac::EventWindowClosed>(23);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventWindowClosed", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kWindowClosed, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kWindow, data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventWindowClosed: [23]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(23, data_g.GetBaseData().window_id);
	}
} // namespace test