/**
 * @file	event_audio.cpp
 * @brief	Source file for audio device events. See event_audio.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	22.08.2023
 */

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "event_types/event_audio.hpp"

// External libraries header includes
#include <SDL_audio.h>
#include <SDL_timer.h>

namespace trac
{
	/**
	 * @brief	Construct a new EventAudioDevice object.
	 * 
	 * @param id	The id of the audio device.
	 * @param type	The type of the audio device. 
	 */
	EventAudioDevice::EventAudioDevice(const audio_device_id_t id, const AudioType type) :
		Event(),
		timestamp_ms_ { SDL_GetTicks64() },
		id_		{ id	},
		type_	{ type	}
	{}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventAudioDevice::GetCategoryFlags() const
	{
		return EventCategory::kDevice | EventCategory::kAudio;
	}
	
	/**
	 * @brief Get the timestamp of the event in milliseconds.
	 * 
	 * @return timestamp_t The timestamp of the event in milliseconds.
	 */
	timestamp_t EventAudioDevice::GetTimestampMs() const
	{
		return timestamp_ms_;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventAudioDevice::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << GetID() << ", " << (uint32_t)GetAudioType() << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the ID of the audio device.
	 * 
	 * @return audio_device_id_t	The ID of the audio device.
	 */
	audio_device_id_t EventAudioDevice::GetID() const
	{
		return id_;
	}

	/**
	 * @brief	Get the type of the audio device (output or capture).
	 * 
	 * @return AudioType	The type of the audio device.
	 * @retval kOutputDevice	The audio device is an output device.
	 * @retval kCaptureDevice	The audio device is a capture device.
	 */
	AudioType EventAudioDevice::GetAudioType() const
	{
		return type_;
	}

	/**
	 * @brief	Construct a new EventAudioDeviceAdded object.
	 * 
	 * @param id	The id of the audio device that was added.
	 * @param type	The type of the audio device that was added (output or capture)
	 */
	EventAudioDeviceAdded::EventAudioDeviceAdded(const audio_device_id_t id, const AudioType type) :
		EventAudioDevice(id, type)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventAudioDeviceAdded::GetName() const
	{
		return "EventAudioDeviceAdded";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventAudioDeviceAdded::GetType() const
	{
		return EventType::kAudioDeviceAdded;
	}
	
	/**
	 * @brief	Construct a new EventAudioDeviceRemoved object.
	 * 
	 * @param id	The ID of the audio device that was removed.
	 * @param type	The type of the audio device that was removed (output or capture).
	 */
	EventAudioDeviceRemoved::EventAudioDeviceRemoved(const audio_device_id_t id, const AudioType type) :
		EventAudioDevice(id, type)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventAudioDeviceRemoved::GetName() const
	{
		return "EventAudioDeviceRemoved";
	}

	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventAudioDeviceRemoved::GetType() const
	{
		return EventType::kAudioDeviceRemoved;
	}

} // namespace trac