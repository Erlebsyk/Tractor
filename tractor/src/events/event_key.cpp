/**
 * @file	event_key.cpp
 * @brief	Sources file for keyboard input events. See event_key.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	26.07.2023
 * 
*/

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "events/event_key.hpp"

namespace trac
{
	/**
	 * @brief	Construct a keyboard input event with a given key code.
	 * 
	 * @param key_code	The key code of the key that was pressed.
	 */
	EventKey::EventKey(const KeyCode key_code) : 
		key_code_ { key_code }
	{}

	/**
	 * @brief	Get the category flags of the event.
	 * 
	 * @return event_category_t	The category flags of the event.
	 */
	event_category_t EventKey::GetCategoryFlags() const
	{
		return (EventCategory::kKeyboard) | (EventCategory::kInput);
	}

	/**
	 * @brief	Get the key code of the key event.
	 * 
	 * @return KeyCode	The key code of the key event.
	 */
	KeyCode EventKey::GetKeyCode() const
	{
		return key_code_;
	}

	/**
	 * @brief	Construct a key pressed event with a given key code and repeat flag.
	 * 
	 * @param key_code	The key code of the key that was pressed.
	 * @param is_repeat	Whether or not the key press is a repeat type key press.
	 */
	EventKeyPressed::EventKeyPressed(const KeyCode key_code, const bool is_repeat) : 
		EventKey(key_code),
		is_repeat_ { is_repeat }
	{}

	/**
	 * @brief	Get the name of the event.
	 * 
	 * @return const char*	The name of the event.
	 */
	const char* EventKeyPressed::GetName() const
	{
		return "EventKeyPressed";
	}

	/**
	 * @brief	Get the type of the event.
	 * 
	 * @return const EventType	The type of the event.
	 */
	const EventType EventKeyPressed::GetType() const
	{
		return EventType::kKeyDown;
	}

	/**
	 * @brief	Get a string representation of the event.
	 * 
	 * @return std::string	A string representation of the event.
	 */
	std::string EventKeyPressed::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": " << key_code_ << " (" << is_repeat_ << ")";
		return ss.str();
	}

	/**
	 * @brief	Get whether or not the key press is a repeat type key press.
	 * 
	 * @return bool	Whether or not the key press is a repeat type key press.
	 */
	bool EventKeyPressed::IsRepeat() const
	{
		return is_repeat_;
	}
	
	/**
	 * @brief	Construct a key released event with a given key code.
	 * 
	 * @param key_code	The key code of the key that was released.
	 */
	EventKeyReleased::EventKeyReleased(const KeyCode key_code) :
		EventKey(key_code)
	{}

	/**
	 * @brief	Get the name of the event.
	 * 
	 * @return const char*	The name of the event.
	 */
	const char* EventKeyReleased::GetName() const
	{
		return "EventKeyReleased";
	}

	/**
	 * @brief	Get the type of the event.
	 * 
	 * @return const EventType	The type of the event.
	 */
	const EventType EventKeyReleased::GetType() const
	{
		return EventType::kKeyUp;
	}

	/**
	 * @brief	Get a string representation of the event.
	 * 
	 * @return std::string	The string representation of the event.
	 */
	std::string EventKeyReleased::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": " << key_code_;
		return ss.str();
	}

	/**
	 * @brief	Construct a key typed event with a given key code.
	 * 
	 * @param key_code	The key code of the key that was typed.
	 */
	EventKeyTyped::EventKeyTyped(const KeyCode key_code) : 
		EventKey(key_code)
	{}

	/**
	 * @brief	Get the name of the event.
	 * 
	 * @return const char*	The name of the event.
	 */
	const char* EventKeyTyped::GetName() const
	{
		return "EventKeyTyped";
	}

	/**
	 * @brief	Get the type of the event.
	 * 
	 * @return const EventType	The type of the event.
	 */
	const EventType EventKeyTyped::GetType() const
	{
		return EventType::kKeyTyped;
	}

	/**
	 * @brief	Get a string representation of the event.
	 * 
	 * @return std::string	The string representation of the event.
	 */
	std::string EventKeyTyped::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": " << key_code_;
		return ss.str();
	}
} // Namespace trac