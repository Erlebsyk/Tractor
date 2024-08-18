/**
 * @file event_layer.hpp
 * @brief Layer event types for the tractor game engine.
 * 
 * @author Erlend Elias Isachsen
 */

#ifndef EVENT_LAYER_HPP_
#define EVENT_LAYER_HPP_

/** Includes	*/
#include <cstdint>

/** Definitions	*/

namespace trac
{
	/// @brief  Base class for layer events.
	class EventLayer : public Event
	{
	public:
		// Constructors and destructors
		EventLayer();
		virtual ~EventLayer() = default;

		virtual event_category_t GetCategoryFlags() const override;
		timestamp_t GetTimestampMs() const override;
		std::string ToString() const override;

	private:
		/// The timestamp of the event.
		const timestamp_t timestamp_ms_;
	};

	/// @brief  Event for when a layer is pushed onto the layer stack.
	class EventLayerPushed : public EventLayer
	{
	public:
		// Constructors and destructors
		EventLayerPushed();

		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief  Event for when a layer is popped from the layer stack.
	class EventLayerPopped : public EventLayer
	{
	public:
		// Constructors and destructors
		EventLayerPopped();

		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief  Event for when a layer is updated.
	class EventLayerUpdated : public EventLayer
	{
	public:
		// Constructors and destructors
		EventLayerUpdated();

		const char* GetName() const override;
		EventType GetType() const override;
	};
	
	/// @brief  Event for when a layer is attached to the application.
	class EventLayerAttached : public EventLayer
	{
	public:
		// Constructors and destructors
		EventLayerAttached();

		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief  Event for when a layer is detached from the application.
	class EventLayerDetached : public EventLayer
	{
	public:
		// Constructors and destructors
		EventLayerDetached();

		const char* GetName() const override;
		EventType GetType() const override;
	};
} // Namespace trac

#endif /* EVENT_LAYER_HPP_ */