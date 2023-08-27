/**
 * @file	event_keyboard.cpp
 * @brief	Source file for keyboard events. See event_keyboard.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 */

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "event_types/event_keyboard.hpp"

// External libraries header includes
#include <SDL_keyboard.h>
#include <SDL_timer.h>

namespace trac
{
	KeySym::KeySym() : 
		scancode	{ SDL_Scancode::SDL_SCANCODE_UNKNOWN	},
		keycode		{ SDL_KeyCode::SDLK_UNKNOWN				},
		mod			{ 0		}
	{}

	/**
	 * @brief	Construct a new key symbol.
	 * 
	 * @param scan	The scan code of the key (physical key code).
	 * @param key	The key code of the key (virtual key code).
	 * @param mod	The currently active key modifiers.
	 */
	KeySym::KeySym(const ScanCode scan, const KeyCode key, const key_mod_t mod) : 
		scancode	{ scan	},
		keycode		{ key	},
		mod			{ mod	}
	{}

	/**
	 * @brief	Construct a new keyboard event.
	 * 
	 * @param key_sym	The key symbol of the event.
	 * @param window_id	The ID of the window that the event occurred in.
	 * @param repeat	Whether the key press is a repeat key.
	 */
	EventKeyboard::EventKeyboard(const KeySym &key_sym, const window_id_t window_id, const bool repeat) :
		Event(),
		timestamp_ms_	{ SDL_GetTicks64()	},
		key_sym_		{ key_sym 			},
		window_id_		{ window_id			},
		repeat_			{ repeat			}
	{}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventKeyboard::GetCategoryFlags() const
	{
		return EventCategory::kKeyboard | EventCategory::kInput;
	}
	
	/**
	 * @brief Get the timestamp of the event in milliseconds.
	 * 
	 * @return timestamp_t The timestamp of the event in milliseconds.
	 */
	timestamp_t EventKeyboard::GetTimestampMs() const
	{
		return timestamp_ms_;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventKeyboard::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << GetWindowId() << ", " << GetScanCode() << " (" << GetKeyCode() << "), " << GetKeyMod();
		ss << ", " << (IsRepeat() ? "true" : "false") << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the key symbol of the event.
	 * 
	 * @return KeySym	The key symbol of the event.
	 */
	KeySym EventKeyboard::GetKeySym() const
	{
		return key_sym_;
	}

	/**
	 * @brief	Get the scan code of the event.
	 * 
	 * @return ScanCode	The scan code of the event.
	 */
	ScanCode EventKeyboard::GetScanCode() const
	{
		return key_sym_.scancode;
	}

	/**
	 * @brief	Get the key code of the event.
	 * 
	 * @return KeyCode	The key code of the event.
	 */
	KeyCode EventKeyboard::GetKeyCode() const
	{	
		return key_sym_.keycode;
	}

	/**
	 * @brief	Get the key modifiers of the event.
	 * 
	 * @return key_mod_t	The key modifiers of the event.
	 */
	key_mod_t EventKeyboard::GetKeyMod() const
	{
		return key_sym_.mod;
	}

	/**
	 * @brief	Get the ID of the window that the event occurred in.
	 * 
	 * @return window_id_t	The ID of the window that the event occurred in.
	 */
	window_id_t EventKeyboard::GetWindowId() const
	{
		return window_id_;
	}

	/**
	 * @brief	Get whether the key press is a repeat key.
	 * 
	 * @return bool	Whether the key press is a repeat key.
	 */
	bool EventKeyboard::IsRepeat() const
	{
		return repeat_;
	}
	
	/**
	 * @brief	Construct a new keyboard key press event.
	 * 
	 * @param key_sym	The key symbol of the key that was pressed.
	 * @param window_id	The ID of the window that the event occurred in.
	 * @param repeat	Whether the key press is a repeat key.
	 */
	EventKeyboardDown::EventKeyboardDown(const KeySym &key_sym, const window_id_t window_id, const bool repeat) :
		EventKeyboard(key_sym, window_id, repeat)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventKeyboardDown::GetName() const
	{
		return "EventKeyboardDown";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventKeyboardDown::GetType() const
	{
		return EventType::kKeyDown;
	}
	
	/**
	 * @brief	Construct a new keyboard key release event.
	 * 
	 * @param key_sym	The key symbol of the key that was released.
	 * @param window_id	The ID of the window that the event occurred in.
	 */
	EventKeyboardUp::EventKeyboardUp(const KeySym &key_sym, const window_id_t window_id) :
		EventKeyboard(key_sym, window_id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventKeyboardUp::GetName() const
	{
		return "EventKeyboardUp";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventKeyboardUp::GetType() const
	{
		return EventType::kKeyUp;
	}
	
	/**
	 * @brief	Construct a new text editing event.
	 * 
	 * @param text	The text that was edited.
	 * @param window_id	The ID of the window that the event occurred in.
	 */
	EventText::EventText(const std::string text, const window_id_t window_id) :
		Event(),
		timestamp_ms_ { SDL_GetTicks64()	},
		text_		  { text				},
		window_id_	  { window_id			}
	{}
	
	/**
	 * @brief Get the timestamp of the event in milliseconds.
	 * 
	 * @return timestamp_t The timestamp of the event in milliseconds.
	 */
	timestamp_t EventText::GetTimestampMs() const
	{
		return timestamp_ms_;
	}

	/**
	 * @brief	Get the text that was edited.
	 * 
	 * @return std::string	The text that was edited.
	 */
	std::string EventText::GetText() const
	{
		return text_;
	}

	/**
	 * @brief	Get the ID of the window that the event occurred in.
	 * 
	 * @return window_id_t	The ID of the window that the event occurred in.
	 */
	window_id_t EventText::GetWindowId() const
	{
		return window_id_;
	}

	/**
	 * @brief	Construct a new text editing event.
	 * 
	 * @param text	The text that was edited.
	 * @param window_id	The ID of the window that the event occurred in.
	 * @param start	The start cursor position of the editing text.
	 * @param length	The length of the editing text.
	 */
	EventTextEditing::EventTextEditing(const std::string text, const window_id_t window_id, const size_t start, const size_t length) :
		EventText(text, window_id),
		start_	{ start		},
		length_	{ length	}
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventTextEditing::GetName() const
	{
		return "EventTextEditing";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventTextEditing::GetType() const
	{
		return EventType::kTextEditing;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventTextEditing::GetCategoryFlags() const
	{
		return EventCategory::kKeyboard | EventCategory::kInput;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventTextEditing::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << GetWindowId() << ", \"" << GetText() << "\" (" << GetStart() << ", " << GetLength() << ")" << "]";
		return ss.str();
	}

	/**
	 * @brief	Get the start cursor position of the editing text.
	 * 
	 * @return size_t	The start cursor position of the editing text.
	 */
	size_t EventTextEditing::GetStart() const
	{
		return start_;
	}

	/**
	 * @brief	Get the length of the editing text.
	 * 
	 * @return size_t	The length of the editing text.
	 */
	size_t EventTextEditing::GetLength() const
	{
		return length_;
	}

	/**
	 * @brief	Construct a new text input event.
	 * 
	 * @param input	The text that was input.
	 * @param window_id	The ID of the window that the event occurred in.
	 */
	EventTextInput::EventTextInput(const std::string input, const window_id_t window_id) :
		EventText(input, window_id)
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventTextInput::GetName() const
	{
		return "EventTextInput";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventTextInput::GetType() const
	{
		return EventType::kTextInput;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventTextInput::GetCategoryFlags() const
	{
		return EventCategory::kKeyboard | EventCategory::kInput;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventTextInput::ToString() const
	{
		std::stringstream ss;
		ss << GetName() << ": [" << GetWindowId() << ", \"" << GetText() << "\"]";
		return ss.str();
	}

	/// @brief	Construct a new keyboard key map changed event.
	EventKeyMapChanged::EventKeyMapChanged() :
		Event(),
		timestamp_ms_ { SDL_GetTicks64() }
	{}
	
	/**
	 * @brief Get the name of the event.
	 * 
	 * @return const char* The name of the event.
	 */
	const char* EventKeyMapChanged::GetName() const
	{
		return "EventKeyMapChanged";
	}
	
	/**
	 * @brief Get the type of the event.
	 * 
	 * @return EventType The type of the event.
	 */
	EventType EventKeyMapChanged::GetType() const
	{
		return EventType::kKeyMapChanged;
	}
	
	/**
	 * @brief Get the category flags of the event.
	 * 
	 * @return event_category_t The category flags of the event.
	 */
	event_category_t EventKeyMapChanged::GetCategoryFlags() const
	{
		return EventCategory::kKeyboard | EventCategory::kDevice;
	}
	
	/**
	 * @brief Get the timestamp of the event in milliseconds.
	 * 
	 * @return timestamp_t The timestamp of the event in milliseconds.
	 */
	timestamp_t EventKeyMapChanged::GetTimestampMs() const
	{
		return timestamp_ms_;
	}
	
	/**
	 * @brief Get the string representation of the event.
	 * 
	 * @return std::string The string representation of the event.
	 */
	std::string EventKeyMapChanged::ToString() const
	{
		std::stringstream ss;
		ss << GetName();
		return ss.str();
	}

} // namespace trac