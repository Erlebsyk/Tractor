/**
 * @file	event_key.hpp
 * @brief	File specifying keyboard input events. 
 * 
 * @author	Erlend Elias Isachsen
 * @date	26.07.2023
 * 
*/

#ifndef EVENT_KEY_HPP_
#define EVENT_KEY_HPP_

// External libraries header includes
#include <SDL_keycode.h>

// Project header includes
#include "event.hpp"

namespace trac
{
	/// Defines a key code type for the SDL key codes. This is used to ensure that the key codes used by the tractor engine is constant even if 
	typedef SDL_KeyCode KeyCode;

	/**
	 * @brief	Key event class. This event is triggered when a key is pressed or released.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	class EventKey : public Event
	{
	public:
		/// @brief Virtual default destructor.
		virtual ~EventKey() = default;

		/// @brief Explicitly defined default copy constructor.
		EventKey(const EventKey& other) = default;
		/// @brief Explicitly defined default move constructor.
		EventKey(EventKey&& other) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventKey& operator=(const EventKey& other) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventKey& operator=(EventKey&& other) = default;

		event_category_t GetCategoryFlags() const override;
		KeyCode GetKeyCode() const;

	protected:
		EventKey(KeyCode key_code);

		/// The key code of the key that triggered the event.
		const KeyCode key_code_;
	};

	/**
	 * @brief	Key pressed event class. The class stores information about the key that triggered the event and whether or not the key press is a repeat type
	 * 			key press.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	class EventKeyPressed : public EventKey
	{
	public:
		// Constructors and destructors
		EventKeyPressed(KeyCode key_code, bool is_repeat = false);
	
		//Public functions
		const char* GetName() const override;
		const EventType GetType() const override;
		std::string ToString() const override;

		bool IsRepeat() const;

	private:
		/// Whether or not the key press is a repeat type key press.
		const bool is_repeat_;
	};

	/**
	 * @brief	Key released event class. The class stores information about the key that triggered the event.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	class EventKeyReleased : public EventKey
	{
	public:
		// Constructors and destructors
		EventKeyReleased(KeyCode key_code);
	
		//Public functions
		const char* GetName() const override;
		const EventType GetType() const override;
		std::string ToString() const override;
	};

	/**
	 * @brief	Key typed event class. The class stores information about the key that triggered the event.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	class EventKeyTyped : public EventKey
	{
	public:
		// Constructors and destructors
		EventKeyTyped(KeyCode key_code);
	
		//Public functions
		const char* GetName() const override;
		const EventType GetType() const override;
		std::string ToString() const override;
	};

} // Namespace trac

#endif // EVENT_KEY_HPP_ 