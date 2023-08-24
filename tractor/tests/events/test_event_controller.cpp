// Google Test Framework
#include <gtest/gtest.h>

// Related header include
#include <tractor.hpp>

// Add test event data
#include "test_event_data.hpp"

namespace test
{
	struct ControllerAxisData
	{
		uint16_t axis_id = 0;
		int16_t axis_value = 0;
	};

	struct ControllerButtonData
	{
		trac::controller_button_t button_id = trac::controller_button_t::SDL_CONTROLLER_BUTTON_INVALID;
		trac::controller_button_state_t button_state = 0;
	};

	struct ControllerTouchpadData
	{
		trac::controller_touchpad_t touchpad_id = 0;
		trac::controller_touchpad_finger_t touchpad_finger_id = 0;
		trac::pos_rel_t touchpad_pos_x = 0.0f;
		trac::pos_rel_t touchpad_pos_y = 0.0f;
		float touchpad_pressure = 0.0f;
	};

	struct ControllerSensorData
	{
		trac::controller_sensor_id_t sensor_id = 0;
		trac::controller_sensor_data_t sensor_data = {0.0f, 0.0f, 0.0f};
	};

	class EventControllerData : public EventBaseData
	{
	public:

		EventControllerData() :
			EventBaseData(),
			controller_id_ { 0 },
			axis_data_ {},
			button_data_ {},
			touchpad_data_ {},
			sensor_data_ {}
		{}

		void Set(std::shared_ptr<trac::Event> e) override
		{
			EventBaseData::Set(e);
			auto event_controller = std::static_pointer_cast<trac::EventController>(e);
			controller_id_ = event_controller->GetControllerId();
		}

		void SetAxisData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_axis = std::static_pointer_cast<trac::EventControllerAxisMotion>(e);
			axis_data_.axis_id = event_axis->GetAxis();
			axis_data_.axis_value = event_axis->GetValue();
		}

		void SetButtonData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_button = std::static_pointer_cast<trac::EventControllerButton>(e);
			button_data_.button_id = event_button->GetButton();
			button_data_.button_state = event_button->GetButtonState();
		}

		void SetTouchpadBaseData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_touchpad = std::static_pointer_cast<trac::EventControllerTouchpad>(e);
			touchpad_data_.touchpad_id = event_touchpad->GetTouchpadIndex();
			touchpad_data_.touchpad_finger_id = event_touchpad->GetTouchpadFingerIndex();
		}

		void SetTouchpadMotionData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			SetTouchpadBaseData(e);
			auto event_touchpad = std::static_pointer_cast<trac::EventControllerTouchpadMotion>(e);
			touchpad_data_.touchpad_pos_x = event_touchpad->GetX();
			touchpad_data_.touchpad_pos_y = event_touchpad->GetY();
		}

		void SetTouchpadPressureData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			SetTouchpadBaseData(e);
			auto event_touchpad = std::static_pointer_cast<trac::EventControllerTouchpadPressure>(e);
			touchpad_data_.touchpad_pressure = event_touchpad->GetPressure();
		}

		void SetSensorData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_sensor = std::static_pointer_cast<trac::EventControllerSensorUpdate>(e);
			sensor_data_.sensor_id = event_sensor->GetSensorId();
			sensor_data_.sensor_data[0] = event_sensor->GetDataX();
			sensor_data_.sensor_data[1] = event_sensor->GetDataY();
			sensor_data_.sensor_data[2] = event_sensor->GetDataZ();
		}

		trac::controller_id_t GetID() const { return controller_id_; }
		ControllerAxisData GetAxisData() const { return axis_data_; }
		ControllerButtonData GetButtonData() const { return button_data_; }
		ControllerTouchpadData GetTouchpadData() const { return touchpad_data_; }
		ControllerSensorData GetSensorData() const { return sensor_data_; }

	private:
		trac::controller_id_t controller_id_;
		ControllerAxisData axis_data_;
		ControllerButtonData button_data_;
		ControllerTouchpadData touchpad_data_;
		ControllerSensorData sensor_data_;
	};

	static EventControllerData data_g = EventControllerData();

	void event_controller_cb(std::shared_ptr<trac::Event> e)
	{
		data_g.Set(e);
	}

	void event_controller_axis_cb(std::shared_ptr<trac::Event> e)
	{
		data_g.SetAxisData(e);
	}

	void event_controller_button_cb(std::shared_ptr<trac::Event> e)
	{
		data_g.SetButtonData(e);
	}

	void event_controller_touchpad_motion_cb(std::shared_ptr<trac::Event> e)
	{
		data_g.SetTouchpadMotionData(e);
	}

	void event_controller_touchpad_pressure_cb(std::shared_ptr<trac::Event> e)
	{
		data_g.SetTouchpadPressureData(e);
	}

	void event_controller_sensor_cb(std::shared_ptr<trac::Event> e)
	{
		data_g.SetSensorData(e);
	}

	GTEST_TEST(tractor, event_controller)
	{
		trac::event_listener_remove_all();

		// Initial values should be blank
		data_g = EventControllerData();
		EXPECT_STREQ("", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kNone, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kNone, data_g.GetCategoryFlags());
		EXPECT_EQ(0, data_g.GetTimestampMs());
		EXPECT_STREQ("", data_g.GetString().c_str());
		EXPECT_EQ(nullptr, data_g.GetEvent());
		EXPECT_EQ(0, data_g.GetID());
		EXPECT_EQ(0, data_g.GetAxisData().axis_id);
		EXPECT_EQ(0, data_g.GetAxisData().axis_value);
		EXPECT_EQ(trac::controller_button_t::SDL_CONTROLLER_BUTTON_INVALID, data_g.GetButtonData().button_id);
		EXPECT_EQ(0, data_g.GetButtonData().button_state);
		EXPECT_EQ(0, data_g.GetTouchpadData().touchpad_id);
		EXPECT_EQ(0, data_g.GetTouchpadData().touchpad_finger_id);
		EXPECT_EQ(0.0f, data_g.GetTouchpadData().touchpad_pos_x);
		EXPECT_EQ(0.0f, data_g.GetTouchpadData().touchpad_pos_y);
		EXPECT_EQ(0.0f, data_g.GetTouchpadData().touchpad_pressure);
		EXPECT_EQ(0, data_g.GetSensorData().sensor_id);
		EXPECT_EQ(0.0f, data_g.GetSensorData().sensor_data[0]);
		EXPECT_EQ(0.0f, data_g.GetSensorData().sensor_data[1]);
		EXPECT_EQ(0.0f, data_g.GetSensorData().sensor_data[2]);

		// Register all event listeners
		trac::event_listener_add_nb(trac::EventType::kControllerAxisMotion, event_controller_axis_cb);
		trac::event_listener_add_nb(trac::EventType::kControllerButtonDown, event_controller_button_cb);
		trac::event_listener_add_nb(trac::EventType::kControllerButtonUp, event_controller_button_cb);
		trac::event_listener_add_nb(trac::EventType::kControllerDeviceAdded, event_controller_cb);
		trac::event_listener_add_nb(trac::EventType::kControllerDeviceRemoved, event_controller_cb);
		trac::event_listener_add_nb(trac::EventType::kControllerDeviceRemapped, event_controller_cb);
		trac::event_listener_add_nb(trac::EventType::kControllerTouchpadMotion, event_controller_touchpad_motion_cb);
		trac::event_listener_add_nb(trac::EventType::kControllerTouchpadDown, event_controller_touchpad_pressure_cb);
		trac::event_listener_add_nb(trac::EventType::kControllerTouchpadUp, event_controller_touchpad_pressure_cb);
		trac::event_listener_add_nb(trac::EventType::kControllerSensorUpdate, event_controller_sensor_cb);

		// Create a shared pointer to an event
		std::shared_ptr<trac::Event> e;
		trac::timestamp_t timestamp_ms = 0;

		// Dispatch each event type one by one
		data_g = EventControllerData();
		e = std::make_shared<trac::EventControllerAxisMotion>(1, 2, 100);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventControllerAxisMotion", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kControllerAxisMotion, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kController | trac::EventCategory::kInput | trac::EventCategory::kAxis), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventControllerAxisMotion: [1, 2, 100]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(1, data_g.GetID());
		EXPECT_EQ(2, data_g.GetAxisData().axis_id);
		EXPECT_EQ(100, data_g.GetAxisData().axis_value);

		data_g = EventControllerData();
		e = std::make_shared<trac::EventControllerButtonDown>(1, trac::controller_button_t::SDL_CONTROLLER_BUTTON_A);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventControllerButtonDown", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kControllerButtonDown, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kController | trac::EventCategory::kInput | trac::EventCategory::kButton), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventControllerButtonDown: [1, 0]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(1, data_g.GetID());
		EXPECT_EQ(trac::controller_button_t::SDL_CONTROLLER_BUTTON_A, data_g.GetButtonData().button_id);
		EXPECT_EQ(1, data_g.GetButtonData().button_state);

		data_g = EventControllerData();
		e = std::make_shared<trac::EventControllerButtonUp>(1, trac::controller_button_t::SDL_CONTROLLER_BUTTON_A);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventControllerButtonUp", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kControllerButtonUp, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kController | trac::EventCategory::kInput | trac::EventCategory::kButton), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventControllerButtonUp: [1, 0]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(1, data_g.GetID());
		EXPECT_EQ(trac::controller_button_t::SDL_CONTROLLER_BUTTON_A, data_g.GetButtonData().button_id);
		EXPECT_EQ(0, data_g.GetButtonData().button_state);

		data_g = EventControllerData();
		e = std::make_shared<trac::EventControllerDeviceAdded>(1);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventControllerDeviceAdded", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kControllerDeviceAdded, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kController | trac::EventCategory::kDevice), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventControllerDeviceAdded: [1]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(1, data_g.GetID());

		data_g = EventControllerData();
		e = std::make_shared<trac::EventControllerDeviceRemoved>(1);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventControllerDeviceRemoved", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kControllerDeviceRemoved, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kController | trac::EventCategory::kDevice), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventControllerDeviceRemoved: [1]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(1, data_g.GetID());

		data_g = EventControllerData();
		e = std::make_shared<trac::EventControllerDeviceRemapped>(1);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventControllerDeviceRemapped", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kControllerDeviceRemapped, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kController | trac::EventCategory::kDevice), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventControllerDeviceRemapped: [1]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(1, data_g.GetID());
		
		data_g = EventControllerData();
		e = std::make_shared<trac::EventControllerTouchpadMotion>(1, 2, 3, 0.5f, 0.5f);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventControllerTouchpadMotion", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kControllerTouchpadMotion, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kController | trac::EventCategory::kInput | trac::EventCategory::kTouch), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventControllerTouchpadMotion: [1, 2, 3, 0.5, 0.5]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(1, data_g.GetID());
		EXPECT_EQ(2, data_g.GetTouchpadData().touchpad_id);
		EXPECT_EQ(3, data_g.GetTouchpadData().touchpad_finger_id);
		EXPECT_EQ(0.5f, data_g.GetTouchpadData().touchpad_pos_x);
		EXPECT_EQ(0.5f, data_g.GetTouchpadData().touchpad_pos_y);

		data_g = EventControllerData();
		e = std::make_shared<trac::EventControllerTouchpadDown>(1, 2, 3, 0.5f);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventControllerTouchpadDown", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kControllerTouchpadDown, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kController | trac::EventCategory::kInput | trac::EventCategory::kTouch), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventControllerTouchpadDown: [1, 2, 3, 0.5]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(1, data_g.GetID());
		EXPECT_EQ(2, data_g.GetTouchpadData().touchpad_id);
		EXPECT_EQ(3, data_g.GetTouchpadData().touchpad_finger_id);
		EXPECT_EQ(0.5f, data_g.GetTouchpadData().touchpad_pressure);

		data_g = EventControllerData();
		e = std::make_shared<trac::EventControllerTouchpadUp>(1, 2, 3, 0.5f);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventControllerTouchpadUp", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kControllerTouchpadUp, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kController | trac::EventCategory::kInput | trac::EventCategory::kTouch), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventControllerTouchpadUp: [1, 2, 3, 0.5]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(1, data_g.GetID());
		EXPECT_EQ(2, data_g.GetTouchpadData().touchpad_id);
		EXPECT_EQ(3, data_g.GetTouchpadData().touchpad_finger_id);
		EXPECT_EQ(0.5f, data_g.GetTouchpadData().touchpad_pressure);

		data_g = EventControllerData();
		e = std::make_shared<trac::EventControllerSensorUpdate>(1, 2, 3.1f, 4.2f, 5.3f);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventControllerSensorUpdate", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kControllerSensorUpdate, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kController | trac::EventCategory::kInput | trac::EventCategory::kSensor), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventControllerSensorUpdate: [1, 2, 3.1, 4.2, 5.3]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(1, data_g.GetID());
		EXPECT_EQ(2, data_g.GetSensorData().sensor_id);
		EXPECT_EQ(3.1f, data_g.GetSensorData().sensor_data[0]);
		EXPECT_EQ(4.2f, data_g.GetSensorData().sensor_data[1]);
		EXPECT_EQ(5.3f, data_g.GetSensorData().sensor_data[2]);
	}
} // namespace test