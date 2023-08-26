// Google Test Framework
#include <gtest/gtest.h>

// Related header include
#include <tractor.hpp>

// Add test event data
#include "test_event_data.hpp"

namespace test
{
	static void event_joystick_cb(std::shared_ptr<trac::Event> e);
	static void event_joystick_axis_cb(std::shared_ptr<trac::Event> e);
	static void event_joystick_ball_cb(std::shared_ptr<trac::Event> e);
	static void event_joystick_hat_cb(std::shared_ptr<trac::Event> e);
	static void event_joystick_button_cb(std::shared_ptr<trac::Event> e);
	static void event_joystick_battery_cb(std::shared_ptr<trac::Event> e);

	struct JoystickAxisData
	{
		trac::index_t index = 0;
		trac::move_value_t value = 0;
	};

	struct JoystickBallData
	{
		trac::index_t index = 0;
		trac::move_value_t x_rel = 0;
		trac::move_value_t y_rel = 0;
	};

	struct JoystickHatData
	{
		trac::index_t index = 0;
		trac::JoystickHatPosition position = trac::JoystickHatPosition::kCentered;
	};

	struct JoystickButtonData
	{
		trac::index_t index = 0;
	};

	struct JoystickBatteryData
	{
		trac::JoystickBatteryLevel level = trac::JoystickBatteryLevel::kUnknown;
	};

	class EventJoystickData : public EventBaseData
	{
	public:
		EventJoystickData() : 
			EventBaseData(),
			id_ { 0 },
			axis_data_ {},
			ball_data_ {},
			hat_data_ {},
			button_data_ {},
			battery_data_ {}
		{}

		void Set(std::shared_ptr<trac::Event> e) override
		{
			EventBaseData::Set(e);

			auto event_joystick = std::static_pointer_cast<trac::EventJoystick>(e);
			id_ = event_joystick->GetJoystickId();
		}

		void SetAxisData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_axis = std::static_pointer_cast<trac::EventJoystickAxisMotion>(e);
			axis_data_.index = event_axis->GetAxisIndex();
			axis_data_.value = event_axis->GetAxisValue();
		}

		void SetBallData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_ball = std::static_pointer_cast<trac::EventJoystickBallMotion>(e);
			ball_data_.index = event_ball->GetBallIndex();
			ball_data_.x_rel = event_ball->GetXRel();
			ball_data_.y_rel = event_ball->GetYRel();
		}

		void SetHatData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_hat = std::static_pointer_cast<trac::EventJoystickHatMotion>(e);
			hat_data_.index = event_hat->GetIndex();
			hat_data_.position = event_hat->GetPosition();
		}

		void SetButtonData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_button = std::static_pointer_cast<trac::EventJoystickButton>(e);
			button_data_.index = event_button->GetButton();
		}

		void SetBatteryData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_battery = std::static_pointer_cast<trac::EventJoystickBatteryUpdated>(e);
			battery_data_.level = event_battery->GetLevel();
		}

		trac::joystick_id_t GetJoystickId() const { return id_; }
		JoystickAxisData GetAxisData() const { return axis_data_; }
		JoystickBallData GetBallData() const { return ball_data_; }
		JoystickHatData GetHatData() const { return hat_data_; }
		JoystickButtonData GetButtonData() const { return button_data_; }
		JoystickBatteryData GetBatteryData() const { return battery_data_; }

	private:
		trac::joystick_id_t id_;
		JoystickAxisData axis_data_;
		JoystickBallData ball_data_;
		JoystickHatData hat_data_;
		JoystickButtonData button_data_;
		JoystickBatteryData battery_data_;
	};

	static EventJoystickData data_g = EventJoystickData();

	void event_joystick_cb(std::shared_ptr<trac::Event> e)
	{
		data_g.Set(e);
	}

	void event_joystick_axis_cb(std::shared_ptr<trac::Event> e)
	{
		data_g.SetAxisData(e);
	}

	void event_joystick_ball_cb(std::shared_ptr<trac::Event> e)
	{
		data_g.SetBallData(e);
	}

	void event_joystick_hat_cb(std::shared_ptr<trac::Event> e)
	{
		data_g.SetHatData(e);
	}

	void event_joystick_button_cb(std::shared_ptr<trac::Event> e)
	{
		data_g.SetButtonData(e);
	}

	void event_joystick_battery_cb(std::shared_ptr<trac::Event> e)
	{
		data_g.SetBatteryData(e);
	}

	GTEST_TEST(tractor, event_joystick)
	{
		trac::event_listener_remove_all();

		// Initial values should be blank
		data_g = EventJoystickData();
		EXPECT_STREQ("", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kNone, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kNone, data_g.GetCategoryFlags());
		EXPECT_EQ(0, data_g.GetTimestampMs());
		EXPECT_STREQ("", data_g.GetString().c_str());
		EXPECT_EQ(nullptr, data_g.GetEvent());
		EXPECT_EQ(0, data_g.GetJoystickId());
		EXPECT_EQ(0, data_g.GetAxisData().index);
		EXPECT_EQ(0, data_g.GetAxisData().value);
		EXPECT_EQ(0, data_g.GetBallData().index);
		EXPECT_EQ(0, data_g.GetBallData().x_rel);
		EXPECT_EQ(0, data_g.GetBallData().y_rel);
		EXPECT_EQ(0, data_g.GetHatData().index);
		EXPECT_EQ(trac::JoystickHatPosition::kCentered, data_g.GetHatData().position);
		EXPECT_EQ(0, data_g.GetButtonData().index);
		EXPECT_EQ(trac::JoystickBatteryLevel::kUnknown, data_g.GetBatteryData().level);

		// Register all event listeners
		trac::event_listener_add_nb(trac::EventType::kJoyAxisMotion, event_joystick_axis_cb);
		trac::event_listener_add_nb(trac::EventType::kJoyBallMotion, event_joystick_ball_cb);
		trac::event_listener_add_nb(trac::EventType::kJoyHatMotion, event_joystick_hat_cb);
		trac::event_listener_add_nb(trac::EventType::kJoyButtonDown, event_joystick_button_cb);
		trac::event_listener_add_nb(trac::EventType::kJoyButtonUp, event_joystick_button_cb);
		trac::event_listener_add_nb(trac::EventType::kJoyDeviceAdded, event_joystick_cb);
		trac::event_listener_add_nb(trac::EventType::kJoyDeviceRemoved, event_joystick_cb);
		trac::event_listener_add_nb(trac::EventType::kJoyBatteryUpdated, event_joystick_battery_cb);

		// Create a shared pointer to an event
		std::shared_ptr<trac::Event> e;
		trac::timestamp_t timestamp_ms = 0;

		// Dispatch each event type one by one
		data_g = EventJoystickData();
		e = std::make_shared<trac::EventJoystickAxisMotion>(1, 2, 3);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventJoystickAxisMotion", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kJoyAxisMotion, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kInput | trac::EventCategory::kJoystick | trac::EventCategory::kAxis), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventJoystickAxisMotion: [1, 2, 3]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(1, data_g.GetJoystickId());
		EXPECT_EQ(2, data_g.GetAxisData().index);
		EXPECT_EQ(3, data_g.GetAxisData().value);

		data_g = EventJoystickData();
		e = std::make_shared<trac::EventJoystickBallMotion>(4, 5, 6, 7);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventJoystickBallMotion", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kJoyBallMotion, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kInput | trac::EventCategory::kJoystick | trac::EventCategory::kBall), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventJoystickBallMotion: [4, 5, 6, 7]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(4, data_g.GetJoystickId());
		EXPECT_EQ(5, data_g.GetBallData().index);
		EXPECT_EQ(6, data_g.GetBallData().x_rel);
		EXPECT_EQ(7, data_g.GetBallData().y_rel);

		data_g = EventJoystickData();
		e = std::make_shared<trac::EventJoystickHatMotion>(8, 9, trac::JoystickHatPosition::kUp);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventJoystickHatMotion", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kJoyHatMotion, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kInput | trac::EventCategory::kJoystick | trac::EventCategory::kHat), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventJoystickHatMotion: [8, 9, up]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(8, data_g.GetJoystickId());
		EXPECT_EQ(9, data_g.GetHatData().index);
		EXPECT_EQ(trac::JoystickHatPosition::kUp, data_g.GetHatData().position);

		data_g = EventJoystickData();
		e = std::make_shared<trac::EventJoystickButtonDown>(9, 2);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventJoystickButtonDown", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kJoyButtonDown, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kInput | trac::EventCategory::kJoystick | trac::EventCategory::kButton), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventJoystickButtonDown: [9, 2]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(9, data_g.GetJoystickId());
		EXPECT_EQ(2, data_g.GetButtonData().index);

		data_g = EventJoystickData();
		e = std::make_shared<trac::EventJoystickButtonUp>(10, 3);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventJoystickButtonUp", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kJoyButtonUp, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kInput | trac::EventCategory::kJoystick | trac::EventCategory::kButton), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventJoystickButtonUp: [10, 3]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(10, data_g.GetJoystickId());
		EXPECT_EQ(3, data_g.GetButtonData().index);

		data_g = EventJoystickData();
		e = std::make_shared<trac::EventJoystickDeviceAdded>(11);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventJoystickDeviceAdded", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kJoyDeviceAdded, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kJoystick | trac::EventCategory::kDevice), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventJoystickDeviceAdded: [11]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(11, data_g.GetJoystickId());

		data_g = EventJoystickData();
		e = std::make_shared<trac::EventJoystickDeviceRemoved>(12);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventJoystickDeviceRemoved", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kJoyDeviceRemoved, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kJoystick | trac::EventCategory::kDevice), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventJoystickDeviceRemoved: [12]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(12, data_g.GetJoystickId());

		data_g = EventJoystickData();
		e = std::make_shared<trac::EventJoystickBatteryUpdated>(13, trac::JoystickBatteryLevel::kLow);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventJoystickBatteryUpdated", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kJoyBatteryUpdated, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kJoystick | trac::EventCategory::kSensor), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventJoystickBatteryUpdated: [13, low]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(trac::JoystickBatteryLevel::kLow, data_g.GetBatteryData().level);
	}

} // namespace test