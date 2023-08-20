/**
 * @file	event_keyboard.hpp
 * @brief	Keyboard input event header file. All events related to keyboard input are defined here.
 * 
 * @author	Erlend Elias Isachsen
 * @date	18.08.2023
 * 
*/

#ifndef EVENT_KEYBOARD_HPP_
#define EVENT_KEYBOARD_HPP_

// Related header include
#include "event.hpp"

// Standard library header includes
#include <string>

// External libraries header includes
#include <SDL_keyboard.h>

// Project header includes
#include "event_window.hpp"

namespace trac
{
	/// Type definition for key scan codes.
	typedef SDL_Scancode ScanCode;
	/// Type definition for key codes.
	typedef SDL_Keycode KeyCode;
	/// Type definition for key modifiers.
	typedef uint16_t key_mod_t;

	/// @brief Struct containing a key symbol.
	struct KeySym
	{
		KeySym(ScanCode scan, KeyCode key, key_mod_t mod);

		/// Physical key code
		ScanCode scancode;
		/// Virtual key code
		KeyCode keycode;
		/// Current key modifiers
		key_mod_t mod;
	};

	/// @brief Abstract base class for keyboard events.
	class EventKeyboard : public Event
	{
	public:
		// Constructors and destructors
	
		EventKeyboard(const KeySym &key_sym, window_id_t window_id, bool repeat = false);
		/// @brief Virtual default destructor.
		virtual ~EventKeyboard() = default;

		/// @brief Explicitly defined default copy constructor.
		EventKeyboard(const EventKeyboard& other) = default;
		/// @brief Explicitly defined default move constructor.
		EventKeyboard(EventKeyboard&& other) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventKeyboard& operator=(const EventKeyboard& other) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventKeyboard& operator=(EventKeyboard&& other) = default;
	
		//Public functions

		event_category_t GetCategoryFlags() const override;
		timestamp_t GetTimestampMs() const override;
		std::string ToString() const override;

		KeySym GetKeySym() const;
		ScanCode GetScanCode() const;
		KeyCode GetKeyCode() const;
		key_mod_t GetKeyMod() const;

	private:
		/// Timestamp of the event in milliseconds.
		const timestamp_t timestamp_ms_;
		/// Key symbol associated with the event.
		const KeySym key_sym_;
		/// The id of the window associated with the event.
		const window_id_t window_id_;
		/// Whether the key press is a repeat key.
		const bool repeat_;
	};

	/// @brief	Keyboard key press event.
	class EventKeyboardDown : public EventKeyboard
	{
	public:
		// Constructors and destructors
	
		EventKeyboardDown(const KeySym &key_sym, window_id_t window_id, bool repeat = false);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Keyboard key release event.
	class EventKeyboardUp : public EventKeyboard
	{
	public:
		// Constructors and destructors
	
		EventKeyboardUp(const KeySym &key_sym, window_id_t window_id, bool repeat = false);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
	};

	/// @brief	Abstract base class for text editing events.
	class EventText : public Event
	{
	public:
		// Constructors and destructors
	
		EventText(std::string text, window_id_t window_id);
		/// @brief Virtual default destructor.
		virtual ~EventText() = default;

		/// @brief Explicitly defined default copy constructor.
		EventText(const EventText& other) = default;
		/// @brief Explicitly defined default move constructor.
		EventText(EventText&& other) = default;
		/// @brief Explicitly defined default copy assignment operator.
		EventText& operator=(const EventText& other) = default;
		/// @brief Explicitly defined default move assignment operator.
		EventText& operator=(EventText&& other) = default;
	
		//Public functions
	
		timestamp_t GetTimestampMs() const override;

		std::string GetText() const;
	
		private:
		/// Timestamp of the event in milliseconds.
		const timestamp_t timestamp_ms_;
		/// Text associated with the event.
		const std::string text_;
		/// The id of the window associated with the event.
		const window_id_t window_id_;
	};

	/// @brief	Text editing event.
	class EventTextEditing : public EventText
	{
	public:
		// Constructors and destructors
	
		EventTextEditing(std::string text, window_id_t window_id, size_t start, size_t length);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;

		size_t GetStart() const;
		size_t GetLength() const;

	private:
		/// The start curstor position of the editing text.
		size_t start_;
		/// The length of selected editing text.
		size_t length_;
	};

	/// @brief	Text input event.
	class EventTextInput : public EventText
	{
	public:
		// Constructors and destructors
	
		EventTextInput(std::string input, window_id_t window_id);
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		std::string ToString() const override;
	};

	/// @brief	Keyboard key map changed event.
	class EventKeyMapChanged : public Event
	{
	public:
		// Constructors and destructors
	
		EventKeyMapChanged();
	
		//Public functions
	
		const char* GetName() const override;
		EventType GetType() const override;
		event_category_t GetCategoryFlags() const override;
		timestamp_t GetTimestampMs() const override;
		std::string ToString() const override;

	private:
		/// Timestamp of the event in milliseconds.
		const timestamp_t timestamp_ms_;
	};

} // Namespace trac

#endif // EVENT_KEYBOARD_HPP_ 