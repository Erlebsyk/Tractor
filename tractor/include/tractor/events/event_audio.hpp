/**
 * @file	event_audio.hpp
 * @brief	Audio device event header file. All events related to audio device are defined here.
 * 
 * @author	Erlend Elias Isachsen
 * @date	22.08.2023
 */

#ifndef EVENT_AUDIO_HPP_
#define EVENT_AUDIO_HPP_

// Related header include
#include "event.hpp"

// External libraries header includes
#include <SDL_audio.h>

namespace trac
{
	/// Type definition for audio device ID that is used to differentiate between different audio devices.
	typedef uint32_t audio_device_id_t;

	/// @brief Enum class for audio device types.
	enum class AudioType
	{
		kNone,
		kOutputDevice,
		kCaptureDevice
	};

	/// @brief	Abstract base class for all audio device events.
	class EventAudioDevice : public Event
	{
	public:
		// Constructors and destructors
	
		EventAudioDevice(audio_device_id_t id, AudioType type);
		/// @brief Virtual default destructor.
		virtual ~EventAudioDevice() = default;

		/// @brief Explicitly defined default copy constructor.
		EventAudioDevice(const EventAudioDevice&) = default;
		/// @brief Explicitly defined default move constructor.
		EventAudioDevice(EventAudioDevice&&) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventAudioDevice& operator=(const EventAudioDevice&) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventAudioDevice& operator=(EventAudioDevice&&) = default;
	
		//Public functions
	
		event_category_t GetCategoryFlags() const override;
		timestamp_t GetTimestampMs() const override;
		std::string ToString() const override;

		audio_device_id_t GetID() const;
		AudioType GetAudioType() const;

	private:
		/// The timestamp of the event in milliseconds.
		const timestamp_t timestamp_ms_;
		/// The id of the audio device.
		const audio_device_id_t id_;
		/// The type of the audio device.
		const AudioType type_;
	};

	/// @brief	Event for when an audio device is removed.
	class EventAudioDeviceAdded : public EventAudioDevice
	{
	public:
		// Constructors and destructors
	
		EventAudioDeviceAdded(audio_device_id_t id, AudioType type);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Event for when an audio device is added.
	class EventAudioDeviceRemoved : public EventAudioDevice
	{
	public:
		// Constructors and destructors
	
		EventAudioDeviceRemoved(audio_device_id_t id, AudioType type);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

} // namespace 

#endif //EVENT_AUDIO_HPP_