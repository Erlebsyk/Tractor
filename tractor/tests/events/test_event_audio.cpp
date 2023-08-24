// Google Test Framework
#include <gtest/gtest.h>

// Related header include
#include <tractor.hpp>

// include test event data
#include "test_event_data.hpp"

namespace test
{
	class EventAudioData : public EventBaseData
	{
	public:
		EventAudioData() :
			EventBaseData(),
			device_id_ { 0 },
			device_type_ { trac::AudioType::kNone }
		{}

		void Set(std::shared_ptr<trac::Event> e) override
		{
			EventBaseData::Set(e);
			auto event_audio = std::static_pointer_cast<trac::EventAudioDevice>(e);
			device_id_ = event_audio->GetID();
			device_type_ = event_audio->GetAudioType();
		}

		trac::audio_device_id_t GetID() const {return device_id_; }
		trac::AudioType GetAudioType() const { return device_type_; }

	private:
		trac::audio_device_id_t device_id_;
		trac::AudioType device_type_;
	};

	static EventAudioData data_g = EventAudioData();

	void event_audio_cb(std::shared_ptr<trac::Event> e)
	{
		data_g.Set(e);
	}

	GTEST_TEST(tractor, event_audio)
	{
		trac::event_listener_remove_all();

		// Initial values should be blank
		data_g = EventAudioData();
		EXPECT_STREQ("", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kNone, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kNone, data_g.GetCategoryFlags());
		EXPECT_EQ(0, data_g.GetTimestampMs());
		EXPECT_STREQ("", data_g.GetString().c_str());
		EXPECT_EQ(nullptr, data_g.GetEvent());
		EXPECT_EQ(0, data_g.GetID());
		EXPECT_EQ(trac::AudioType::kNone, data_g.GetAudioType());

		// Register all event listeners
		trac::event_listener_add_nb(trac::EventType::kAudioDeviceAdded, event_audio_cb);
		trac::event_listener_add_nb(trac::EventType::kAudioDeviceRemoved, event_audio_cb);

		// Create a shared pointer to an event
		std::shared_ptr<trac::Event> e;
		trac::timestamp_t timestamp_ms = 0;

		// Dispatch each event type one by one
		e = std::make_shared<trac::EventAudioDeviceRemoved>(10, trac::AudioType::kOutputDevice);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAudioDeviceRemoved", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kAudioDeviceRemoved, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kAudio | trac::EventCategory::kDevice), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventAudioDeviceRemoved: 10 1", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(10, data_g.GetID());
		EXPECT_EQ(trac::AudioType::kOutputDevice, data_g.GetAudioType());
		
		e = std::make_shared<trac::EventAudioDeviceAdded>(11, trac::AudioType::kCaptureDevice);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventAudioDeviceAdded", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kAudioDeviceAdded, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kAudio | trac::EventCategory::kDevice), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventAudioDeviceAdded: 11 2", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(11, data_g.GetID());
		EXPECT_EQ(trac::AudioType::kCaptureDevice, data_g.GetAudioType());

	}

} // namespace test