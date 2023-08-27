/**
 * @file	event_render.hpp
 * @brief	Render event header file. All events related to rendering are defined here.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 * 
*/

#ifndef EVENT_RENDER_HPP_
#define EVENT_RENDER_HPP_

// Related header include
#include "event_base.hpp"

namespace trac
{
	/// @brief Render targets have been reset and their contents need to be updated.
	class EventRenderTargetsReset : public Event
	{
	public:
		// Constructors and destructors
	
		EventRenderTargetsReset();
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		timestamp_t GetTimestampMs() const override;

	private:
		/// Timestamp of the event in milliseconds.
		const timestamp_t timestamp_ms_;
	};

	/// @brief Render device has been resets and all resources need to be recreated.
	class EventRenderDeviceReset : public Event
	{
	public:
		// Constructors and destructors
	
		EventRenderDeviceReset();
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		timestamp_t GetTimestampMs() const override;

	private:
		/// Timestamp of the event in milliseconds.
		const timestamp_t timestamp_ms_;
	};

} // Namespace trac

#endif // EVENT_RENDER_HPP_ 