/**
 * @file	sdl_hook_events.cpp
 * @brief	
 * 
 * @author	Erlend Elias Isachsen
 * @date	27.08.2023
 */

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "sdl_hook_events.hpp"

// External libraries header includes
#include <SDL_events.h>
#include <SDL_mouse.h>

// Project header includes
#include "logger.hpp"

namespace trac
{
	
	static SDL_EventType get_sdl_event_type(const EventType e);

	static std::shared_ptr<Event> create_window_event(const SDL_Event* e);
	static std::shared_ptr<Event> create_display_event(const SDL_Event* e);
	static AudioType get_audio_type(const SDL_Event* e);
	static std::shared_ptr<Event> create_key_event(const SDL_Event* e);
	static MouseButton get_mouse_button(const SDL_Event* e);
	static std::shared_ptr<Event> create_mouse_event(const SDL_Event* e);
	static JoystickHatPosition get_hat_position(const SDL_Event* e);
	static JoystickBatteryLevel get_joystick_battery_level(const SDL_Event* e);
	static std::shared_ptr<Event> create_controller_touchpad_event(const SDL_Event *e);
	static std::shared_ptr<Event> create_controller_sensor_event(const SDL_Event *e);
	static std::shared_ptr<Event> create_touch_event(const SDL_Event* e);
	static std::shared_ptr<Event> create_gesture_event(const SDL_Event* e);

	static std::shared_ptr<Event> parse_unsupported_event(const SDL_Event *e);
	static std::shared_ptr<Event> parse_sdl_event(const SDL_Event *e);
	static int sdl_event_callback(void *data, SDL_Event *event);

	/// List of all SDL events.
	static const SDL_EventType kSdlEventList[] = {
		SDL_QUIT,
		SDL_APP_TERMINATING,
		SDL_APP_LOWMEMORY,
		SDL_APP_WILLENTERBACKGROUND,
		SDL_APP_DIDENTERBACKGROUND,
		SDL_APP_WILLENTERFOREGROUND,
		SDL_APP_DIDENTERFOREGROUND,
		SDL_LOCALECHANGED,
		SDL_DISPLAYEVENT,
		SDL_WINDOWEVENT,
		SDL_SYSWMEVENT,
		SDL_KEYDOWN,
		SDL_KEYUP,
		SDL_TEXTEDITING,
		SDL_TEXTINPUT,
		SDL_KEYMAPCHANGED,
		SDL_TEXTEDITING_EXT,
		SDL_MOUSEMOTION,
		SDL_MOUSEBUTTONDOWN,
		SDL_MOUSEBUTTONUP,
		SDL_MOUSEWHEEL,
		SDL_JOYAXISMOTION,
		SDL_JOYBALLMOTION,
		SDL_JOYHATMOTION,
		SDL_JOYBUTTONDOWN,
		SDL_JOYBUTTONUP,
		SDL_JOYDEVICEADDED,
		SDL_JOYDEVICEREMOVED,
		SDL_JOYBATTERYUPDATED,
		SDL_CONTROLLERAXISMOTION,
		SDL_CONTROLLERBUTTONDOWN,
		SDL_CONTROLLERBUTTONUP,
		SDL_CONTROLLERDEVICEADDED,
		SDL_CONTROLLERDEVICEREMOVED,
		SDL_CONTROLLERDEVICEREMAPPED,
		SDL_CONTROLLERTOUCHPADDOWN,
		SDL_CONTROLLERTOUCHPADMOTION,
		SDL_CONTROLLERTOUCHPADUP,
		SDL_CONTROLLERSENSORUPDATE,
		SDL_FINGERDOWN,
		SDL_FINGERUP,
		SDL_FINGERMOTION,
		SDL_DOLLARGESTURE,
		SDL_DOLLARRECORD,
		SDL_MULTIGESTURE,
		SDL_CLIPBOARDUPDATE,
		SDL_DROPFILE,
		SDL_DROPTEXT,
		SDL_DROPBEGIN,
		SDL_DROPCOMPLETE,
		SDL_AUDIODEVICEADDED,
		SDL_AUDIODEVICEREMOVED,
		SDL_SENSORUPDATE,
		SDL_RENDER_TARGETS_RESET,
		SDL_RENDER_DEVICE_RESET,
		SDL_POLLSENTINEL,
		SDL_USEREVENT
	};

	/// Lists all SDL event types that are not supported by the tractor event system. All SDL events should either be listed here or used in parse_sdl_event.
	static const SDL_EventType kSdlUnsupportedTypes[] = {
		SDL_SYSWMEVENT,
		SDL_TEXTEDITING_EXT,
		SDL_SENSORUPDATE,
		SDL_POLLSENTINEL,
		SDL_USEREVENT
	};

	/**
	 * @brief	Get the sdl event type object
	 * 
	 * @param e	
	 * @return SDL_EventType	
	 * 
	 */
	SDL_EventType get_sdl_event_type(const EventType e)
	{
		switch(e)
		{
			case EventType::kQuit:						return SDL_QUIT;
			case EventType::kLocaleChanged:				return SDL_LOCALECHANGED;
			case EventType::kClipboardUpdate:			return SDL_CLIPBOARDUPDATE;
			case EventType::kDropFile:					return SDL_DROPFILE;
			case EventType::kDropText:					return SDL_DROPTEXT;
			case EventType::kDropBegin:					return SDL_DROPBEGIN;
			case EventType::kDropComplete:				return SDL_DROPCOMPLETE;

			case EventType::kAudioDeviceAdded:			return SDL_AUDIODEVICEADDED;
			case EventType::kAudioDeviceRemoved:		return SDL_AUDIODEVICEREMOVED;

			case EventType::kAppTerminating:			return SDL_APP_TERMINATING;
			case EventType::kAppLowMemory:				return SDL_APP_LOWMEMORY;
			case EventType::kAppEnteringBackground:		return SDL_APP_WILLENTERBACKGROUND;
			case EventType::kAppEnteredBackground:		return SDL_APP_DIDENTERBACKGROUND;
			case EventType::kAppEnteringForeground:		return SDL_APP_WILLENTERFOREGROUND;
			case EventType::kAppEnteredForeground:		return SDL_APP_DIDENTERFOREGROUND;
			case EventType::kAppTick:					return SDL_USEREVENT;
			case EventType::kAppUpdated:				return SDL_USEREVENT;
			case EventType::kAppRendered:				return SDL_USEREVENT;

			case EventType::kDisplayOrientation:		return SDL_DISPLAYEVENT;
			case EventType::kDisplayConnected:			return SDL_DISPLAYEVENT;
			case EventType::kDisplayDisconnected:		return SDL_DISPLAYEVENT;

			case EventType::kWindowShown:				return SDL_WINDOWEVENT;
			case EventType::kWindowHidden:				return SDL_WINDOWEVENT;
			case EventType::kWindowExposed:				return SDL_WINDOWEVENT;
			case EventType::kWindowMoved:				return SDL_WINDOWEVENT;
			case EventType::kWindowResized:				return SDL_WINDOWEVENT;
			case EventType::kWindowSizeChanged:			return SDL_WINDOWEVENT;
			case EventType::kWindowMinimized:			return SDL_WINDOWEVENT;
			case EventType::kWindowMaximized:			return SDL_WINDOWEVENT;
			case EventType::kWindowRestored:			return SDL_WINDOWEVENT;
			case EventType::kWindowEnter:				return SDL_WINDOWEVENT;
			case EventType::kWindowLeave:				return SDL_WINDOWEVENT;
			case EventType::kWindowFocusGained:			return SDL_WINDOWEVENT;
			case EventType::kWindowFocusLost:			return SDL_WINDOWEVENT;
			case EventType::kWindowTakeFocus:			return SDL_WINDOWEVENT;
			case EventType::kWindowHitTest:				return SDL_WINDOWEVENT;
			case EventType::kWindowIccProfileChanged:	return SDL_WINDOWEVENT;
			case EventType::kWindowDisplayChanged:		return SDL_WINDOWEVENT;
			case EventType::kWindowClosed:				return SDL_WINDOWEVENT;

			case EventType::kKeyDown:					return SDL_KEYDOWN;
			case EventType::kKeyUp:						return SDL_KEYUP;
			case EventType::kTextEditing:				return SDL_TEXTEDITING;
			case EventType::kTextInput:					return SDL_TEXTINPUT;
			case EventType::kKeyMapChanged:				return SDL_KEYMAPCHANGED;

			case EventType::kMouseMotion:				return SDL_MOUSEMOTION;
			case EventType::kMouseButtonDown:			return SDL_MOUSEBUTTONDOWN;
			case EventType::kMouseButtonUp:				return SDL_MOUSEBUTTONUP;
			case EventType::kMouseButtonClicked:		return SDL_MOUSEBUTTONDOWN;
			case EventType::kMouseWheel:				return SDL_MOUSEWHEEL;

			case EventType::kJoyAxisMotion:				return SDL_JOYAXISMOTION;
			case EventType::kJoyBallMotion:				return SDL_JOYBALLMOTION;
			case EventType::kJoyHatMotion:				return SDL_JOYHATMOTION;
			case EventType::kJoyButtonDown:				return SDL_JOYBUTTONDOWN;
			case EventType::kJoyButtonUp:				return SDL_JOYBUTTONUP;
			case EventType::kJoyDeviceAdded:			return SDL_JOYDEVICEADDED;
			case EventType::kJoyDeviceRemoved:			return SDL_JOYDEVICEREMOVED;
			case EventType::kJoyBatteryUpdated:			return SDL_JOYDEVICEADDED;

			case EventType::kControllerAxisMotion:		return SDL_CONTROLLERAXISMOTION;
			case EventType::kControllerButtonDown:		return SDL_CONTROLLERBUTTONDOWN;
			case EventType::kControllerButtonUp:		return SDL_CONTROLLERBUTTONUP;
			case EventType::kControllerDeviceAdded:		return SDL_CONTROLLERDEVICEADDED;
			case EventType::kControllerDeviceRemoved:	return SDL_CONTROLLERDEVICEREMOVED;
			case EventType::kControllerDeviceRemapped:	return SDL_CONTROLLERDEVICEREMAPPED;
			case EventType::kControllerTouchpadMotion:	return SDL_CONTROLLERTOUCHPADMOTION;
			case EventType::kControllerTouchpadDown:	return SDL_CONTROLLERTOUCHPADDOWN;
			case EventType::kControllerTouchpadUp:		return SDL_CONTROLLERTOUCHPADUP;
			case EventType::kControllerSensorUpdate:	return SDL_CONTROLLERSENSORUPDATE;

			case EventType::kFingerDown:				return SDL_FINGERDOWN;
			case EventType::kFingerUp:					return SDL_FINGERUP;
			case EventType::kFingerMotion:				return SDL_FINGERMOTION;

			case EventType::kDollarGesture:				return SDL_DOLLARGESTURE;
			case EventType::kDollarRecord:				return SDL_DOLLARRECORD;
			case EventType::kMultiGesture:				return SDL_MULTIGESTURE;

			case EventType::kRenderTargetsReset:		return SDL_RENDER_TARGETS_RESET;
			case EventType::kRenderDeviceReset:			return SDL_RENDER_DEVICE_RESET;

			default:									return SDL_USEREVENT;
		}
	}

	/**
	 * @brief	Creates a tractor window event from an SDL window event.
	 * 
	 * @param e	The SDL window event.
	 */
	std::shared_ptr<Event> create_window_event(const SDL_Event* e)
	{
		switch(e->window.event)
		{
			case SDL_WINDOWEVENT_SHOWN:				return std::make_shared<EventWindowShown>(e->window.windowID);
			case SDL_WINDOWEVENT_HIDDEN:			return std::make_shared<EventWindowHidden>(e->window.windowID);
			case SDL_WINDOWEVENT_EXPOSED:			return std::make_shared<EventWindowExposed>(e->window.windowID);
			case SDL_WINDOWEVENT_MOVED:				return std::make_shared<EventWindowMoved>(e->window.windowID, e->window.data1, e->window.data2);
			case SDL_WINDOWEVENT_RESIZED:			return std::make_shared<EventWindowResized>(e->window.windowID, e->window.data1, e->window.data2);
			case SDL_WINDOWEVENT_SIZE_CHANGED:		return std::make_shared<EventWindowSizeChanged>(e->window.windowID);
			case SDL_WINDOWEVENT_MINIMIZED:			return std::make_shared<EventWindowMinimized>(e->window.windowID);
			case SDL_WINDOWEVENT_MAXIMIZED:			return std::make_shared<EventWindowMaximized>(e->window.windowID);
			case SDL_WINDOWEVENT_RESTORED:			return std::make_shared<EventWindowRestored>(e->window.windowID);
			case SDL_WINDOWEVENT_ENTER:				return std::make_shared<EventWindowEnter>(e->window.windowID);
			case SDL_WINDOWEVENT_LEAVE:				return std::make_shared<EventWindowLeave>(e->window.windowID);
			case SDL_WINDOWEVENT_FOCUS_GAINED:		return std::make_shared<EventWindowFocusGained>(e->window.windowID);
			case SDL_WINDOWEVENT_FOCUS_LOST:		return std::make_shared<EventWindowFocusLost>(e->window.windowID);
			case SDL_WINDOWEVENT_CLOSE:				return std::make_shared<EventWindowClosed>(e->window.windowID);
			case SDL_WINDOWEVENT_TAKE_FOCUS:		return std::make_shared<EventWindowTakeFocus>(e->window.windowID);
			case SDL_WINDOWEVENT_HIT_TEST:			return std::make_shared<EventWindowHitTest>(e->window.windowID);
			case SDL_WINDOWEVENT_ICCPROF_CHANGED:	return std::make_shared<EventWindowIccProfileChanged>(e->window.windowID);
			case SDL_WINDOWEVENT_DISPLAY_CHANGED:	return std::make_shared<EventWindowDisplayChanged>(e->window.windowID, e->window.data1);
			default:
				log_engine_error("Unknown SDL window event type [{0:d}].", (uint16_t)e->window.event);
				return nullptr;
		}
	}

	/**
	 * @brief	Create a tractor display event from an SDL display event.
	 * 
	 * @param e	The SDL display event.
	 * @return std::shared_ptr<Event>	The tractor display event.
	 */
	std::shared_ptr<Event> create_display_event(const SDL_Event* e)
	{
		switch(e->display.event)
		{
			case SDL_DISPLAYEVENT_ORIENTATION:	return std::make_shared<EventDisplayOrientation>(e->display.display, (DisplayOrientation)(e->display.data1));
			case SDL_DISPLAYEVENT_CONNECTED:	return std::make_shared<EventDisplayConnected>(e->display.display);
			case SDL_DISPLAYEVENT_DISCONNECTED:	return std::make_shared<EventDisplayDisconnected>(e->display.display);
			default:
				log_engine_error("Unknown SDL display event type [{0:d}].", (uint16_t)e->display.event);
				return nullptr;
		}
	}

	/**
	 * @brief	Get the audio type of an SDL audio device event.
	 * 
	 * @param e	The SDL audio device event.
	 * @return AudioType	The audio type.
	 */
	AudioType get_audio_type(const SDL_Event* e)
	{
		return (e->adevice.iscapture == 0) ? AudioType::kOutputDevice : AudioType::kCaptureDevice;
	}

	/**
	 * @brief	Create a tractor key event from an SDL key event.
	 * 
	 * @param e	The SDL key event.
	 * @return std::shared_ptr<Event>	The tractor key event.
	 */
	std::shared_ptr<Event> create_key_event(const SDL_Event* e)
	{
		// Create the key symbol from the SDL key event.
		const KeySym key_sym = KeySym(e->key.keysym.scancode, e->key.keysym.sym, e->key.keysym.mod);

		// Create the key event.
		std::shared_ptr<Event> key_e = nullptr;
		if(e->key.state == SDL_PRESSED)
			key_e = std::make_shared<EventKeyboardDown>(key_sym, e->key.windowID, e->key.repeat);
		else
			key_e = std::make_shared<EventKeyboardUp>(key_sym, e->key.windowID);

		return key_e;
	}

	/**
	 * @brief	Get the mouse button from an SDL mouse event.
	 * 
	 * @param e	The SDL mouse event.
	 * @return MouseButton	The mouse button.
	 */
	MouseButton get_mouse_button(const SDL_Event* e)
	{
		switch(e->button.button)
		{
			case SDL_BUTTON_LEFT:		return MouseButton::kLeft;
			case SDL_BUTTON_MIDDLE:		return MouseButton::kMiddle;
			case SDL_BUTTON_RIGHT:		return MouseButton::kRight;
			case SDL_BUTTON_X1:			return MouseButton::kX1;
			case SDL_BUTTON_X2:			return MouseButton::kX2;
			default:					return MouseButton::kUnknown;
		}
	}

	/**
	 * @brief	Create a tractor mouse event from an SDL mouse event.
	 * 
	 * @param e	The SDL mouse event.
	 * @return std::shared_ptr<Event>	The tractor mouse event.
	 */
	std::shared_ptr<Event> create_mouse_event(const SDL_Event* e)
	{
		// Create the mouse event. (krrrrghhhh this is ugly)
		std::shared_ptr<Event> mouse_e = nullptr;
		MouseData m_data;
		
		if(e->type == SDL_MOUSEMOTION)
		{
			m_data = MouseData(e->motion.which, e->motion.windowID, e->motion.x, e->motion.y);
			mouse_e = std::make_shared<EventMouseMotion>(m_data, e->motion.state, e->motion.xrel, e->motion.yrel);
		}
		else if(e->type == SDL_MOUSEBUTTONDOWN)
		{
			m_data = MouseData(e->button.which, e->button.windowID, e->button.x, e->button.y);
			mouse_e = std::make_shared<EventMouseButtonDown>(m_data, get_mouse_button(e));
		}
		else if(e->type == SDL_MOUSEBUTTONUP)
		{
			m_data = MouseData(e->button.which, e->button.windowID, e->button.x, e->button.y);
			MouseButton button = MouseButton::kUnknown;
			mouse_e = std::make_shared<EventMouseButtonUp>(m_data, get_mouse_button(e));
		}
		else if(e->type == SDL_MOUSEWHEEL)
		{
			m_data = MouseData(e->wheel.which, e->wheel.windowID, e->wheel.mouseX, e->wheel.mouseY);
			mouse_e = std::make_shared<EventMouseWheel>(m_data, e->wheel.x, e->wheel.y);
		}
		else
		{
			log_engine_error("Unknown SDL mouse event type [{0:d}].", (uint16_t)e->type);
		}

		return mouse_e;
	}

	/**
	 * @brief	Get the joystick hat position from an SDL joystick hat event.
	 * 
	 * @param e	The SDL joystick event.
	 * @return JoystickHatPosition	The joystick hat position.
	 */
	JoystickHatPosition get_hat_position(const SDL_Event* e)
	{
		switch(e->jhat.value)
		{
			case SDL_HAT_CENTERED:		return JoystickHatPosition::kCentered;
			case SDL_HAT_UP:			return JoystickHatPosition::kUp;
			case SDL_HAT_RIGHT:			return JoystickHatPosition::kRight;
			case SDL_HAT_DOWN:			return JoystickHatPosition::kDown;
			case SDL_HAT_LEFT:			return JoystickHatPosition::kLeft;
			case SDL_HAT_RIGHTUP:		return JoystickHatPosition::kRightUp;
			case SDL_HAT_RIGHTDOWN:		return JoystickHatPosition::kRightDown;
			case SDL_HAT_LEFTUP:		return JoystickHatPosition::kLeftUp;
			case SDL_HAT_LEFTDOWN:		return JoystickHatPosition::kLeftDown;
			default:					return JoystickHatPosition::kUnknown;
		}
	}

	/**
	 * @brief	Get the joystick battery level from an SDL joystick battery event.
	 * 
	 * @param e	The SDL joystick event.
	 * @return JoystickBatteryLevel	The joystick battery level.
	 */
	JoystickBatteryLevel get_joystick_battery_level(const SDL_Event* e)
	{
		switch(e->jbattery.level)
		{
			case SDL_JOYSTICK_POWER_UNKNOWN:	return JoystickBatteryLevel::kUnknown;
			case SDL_JOYSTICK_POWER_EMPTY:		return JoystickBatteryLevel::kEmpty;
			case SDL_JOYSTICK_POWER_LOW:		return JoystickBatteryLevel::kLow;
			case SDL_JOYSTICK_POWER_MEDIUM:		return JoystickBatteryLevel::kMedium;
			case SDL_JOYSTICK_POWER_FULL:		return JoystickBatteryLevel::kFull;
			case SDL_JOYSTICK_POWER_WIRED:		return JoystickBatteryLevel::kWired;
			default:							return JoystickBatteryLevel::kUnknown;
		}
	}

	/**
	 * @brief	Create a tractor touchpad event from an SDL controller touchpad event.
	 * 
	 * @param e	The SDL controller touchpad event.
	 * @return std::shared_ptr<Event>	The tractor touchpad event.
	 */
	std::shared_ptr<Event> create_controller_touchpad_event(const SDL_Event *e)
	{
		// Create the touchpad event.
		std::shared_ptr<Event> touch_e = nullptr;
		const SDL_ControllerTouchpadEvent touch = e->ctouchpad;

		if(e->type == SDL_CONTROLLERTOUCHPADMOTION)
			touch_e = std::make_shared<EventControllerTouchpadMotion>(touch.which, touch.touchpad, touch.finger, touch.x, touch.y);
		else if(e->type == SDL_CONTROLLERTOUCHPADDOWN)
			touch_e = std::make_shared<EventControllerTouchpadDown>(touch.which, touch.touchpad, touch.finger, touch.pressure);
		else if(e->type == SDL_CONTROLLERTOUCHPADUP)
			touch_e = std::make_shared<EventControllerTouchpadUp>(touch.which, touch.touchpad, touch.finger, touch.pressure);
		else
			log_engine_error("Unknown SDL controller touchpad event type [{0:d}].", (uint16_t)e->type);

		return touch_e;
	}

	/**
	 * @brief	Create a tractor controller sensor event from an SDL controller sensor event.
	 * 
	 * @param e	The SDL controller sensor event.
	 * @return std::shared_ptr<Event>	The tractor controller sensor event.
	 */
	std::shared_ptr<Event> create_controller_sensor_event(const SDL_Event *e)
	{
		// Create the sensor event.
		const SDL_ControllerSensorEvent se = e->csensor;
		std::shared_ptr<Event> sensor_e = std::make_shared<EventControllerSensorUpdate>(se.which, se.sensor, se.data[0], se.data[1], se.data[2]);
		return sensor_e;
	}

	/**
	 * @brief	Create a tractor touch event from an SDL touch event.
	 * 
	 * @param e	The SDL touch event.
	 * @return std::shared_ptr<Event>	The tractor touch event.
	 */
	std::shared_ptr<Event> create_touch_event(const SDL_Event* e)
	{
		// Create the touch event.
		std::shared_ptr<Event> touch_e = nullptr;
		const SDL_TouchFingerEvent touch = e->tfinger;
		const TouchPoint touch_point = TouchPoint(touch.fingerId, touch.x, touch.y, touch.dx, touch.dy, touch.pressure);

		if(e->type == SDL_FINGERDOWN)
			touch_e = std::make_shared<EventFingerDown>(touch.windowID, touch.touchId, touch_point);
		else if(e->type == SDL_FINGERUP)
			touch_e = std::make_shared<EventFingerUp>(touch.windowID, touch.touchId, touch_point);
		else if(e->type == SDL_FINGERMOTION)
			touch_e = std::make_shared<EventFingerMotion>(touch.windowID, touch.touchId, touch_point);
		else
			log_engine_error("Unknown SDL touch event type [{0:d}].", (uint16_t)e->type);

		return touch_e;
	}

	/**
	 * @brief	Create a tractor gesture event from an SDL gesture event.
	 * 
	 * @param e	The SDL gesture event.
	 * @return std::shared_ptr<Event>	The tractor gesture event.
	 */
	std::shared_ptr<Event> create_gesture_event(const SDL_Event* e)
	{
		const GestureData g_data = ((e->type == SDL_DOLLARGESTURE) || (e->type == SDL_DOLLARRECORD)) ? 
			GestureData(e->dgesture.touchId, e->dgesture.numFingers, e->dgesture.x, e->dgesture.y) : 
			GestureData(e->mgesture.touchId, e->mgesture.numFingers, e->mgesture.x, e->mgesture.y);
		
		switch(e->type)
		{
			case SDL_DOLLARGESTURE:	return std::make_shared<EventDollarGesture>(g_data, e->dgesture.gestureId, e->dgesture.error);
			case SDL_DOLLARRECORD:	return std::make_shared<EventDollarRecord>(g_data, e->dgesture.gestureId, e->dgesture.error);
			case SDL_MULTIGESTURE:	return std::make_shared<EventMultiGesture>(g_data, e->mgesture.dTheta, e->mgesture.dDist);
			default:
				log_engine_error("Unknown SDL gesture event type [{0:d}].", (uint16_t)e->type);
				return nullptr;
		}
	}

	/**
	 * @brief	Parse an SDL event that does not have a defined translation in the sdl event parser. This will return nullptr, and log an error if the event is
	 * 			not explicitly unsupported (listed in kSdlUnsupportedTypes).
	 * 
	 * @param e	The SDL event that was not directly parsed.
	 * @return std::shared_ptr<Event>	Null-pointer.
	 * @retval nullptr
	 */
	std::shared_ptr<Event> parse_unsupported_event(const SDL_Event *e)
	{
		bool unsupported = false;
		for(auto event : kSdlUnsupportedTypes)
		{
			if(e->type == event)
			{
				unsupported = true;
				break;
			}
		}

		// An unknown event that is not explicitly unsupported was parsed, this should not happen.
		if(!unsupported)
			log_engine_error("Unknown SDL event type [{0:d}].", (uint16_t)e->type);

		return nullptr;
	}

	/**
	 * @brief	Attempts to parse an SDL event by converting it into a tractor event. If the event is not supported, nullptr is returned.
	 * 
	 * @param e	The SDL event to parse.
	 * @return std::shared_ptr<Event>	The tractor event. This may be nullptr if the event is not supported.
	 */
	std::shared_ptr<Event> parse_sdl_event(const SDL_Event *e)
	{
		switch(e->type)
		{
			case SDL_QUIT:						return std::make_shared<EventQuit>();
			case SDL_LOCALECHANGED:				return std::make_shared<EventLocaleChanged>();
			case SDL_CLIPBOARDUPDATE:			return std::make_shared<EventClipboardUpdate>();
			case SDL_DROPFILE:					return std::make_shared<EventDropFile>(e->drop.file, e->drop.windowID);
			case SDL_DROPTEXT:					return std::make_shared<EventDropText>(e->drop.file, e->drop.windowID);
			case SDL_DROPBEGIN:					return std::make_shared<EventDropBegin>(e->drop.windowID);
			case SDL_DROPCOMPLETE:				return std::make_shared<EventDropComplete>(e->drop.windowID);

			case SDL_AUDIODEVICEADDED:			return std::make_shared<EventAudioDeviceAdded>(e->adevice.which, get_audio_type(e));
			case SDL_AUDIODEVICEREMOVED:		return std::make_shared<EventAudioDeviceRemoved>(e->adevice.which, get_audio_type(e));

			case SDL_APP_TERMINATING:			return std::make_shared<EventAppTerminating>();
			case SDL_APP_LOWMEMORY:				return std::make_shared<EventAppLowMemory>();
			case SDL_APP_WILLENTERBACKGROUND:	return std::make_shared<EventAppEnteringBackground>();
			case SDL_APP_DIDENTERBACKGROUND:	return std::make_shared<EventAppEnteredBackground>();
			case SDL_APP_WILLENTERFOREGROUND:	return std::make_shared<EventAppEnteringForeground>();
			case SDL_APP_DIDENTERFOREGROUND:	return std::make_shared<EventAppEnteredForeground>();

			case SDL_DISPLAYEVENT:				return create_display_event(e);

			case SDL_WINDOWEVENT:				return create_window_event(e);

			case SDL_KEYDOWN:					return create_key_event(e);
			case SDL_KEYUP:						return create_key_event(e);
			case SDL_TEXTEDITING:				return std::make_shared<EventTextEditing>(e->edit.text, e->edit.windowID, e->edit.start, e->edit.length);
			case SDL_TEXTINPUT:					return std::make_shared<EventTextInput>(e->text.text, e->text.windowID);
			case SDL_KEYMAPCHANGED:				return std::make_shared<EventKeyMapChanged>();

			case SDL_MOUSEMOTION:				return create_mouse_event(e);
			case SDL_MOUSEBUTTONDOWN:			return create_mouse_event(e);
			case SDL_MOUSEBUTTONUP:				return create_mouse_event(e);
			case SDL_MOUSEWHEEL:				return create_mouse_event(e);

			case SDL_JOYAXISMOTION:				return std::make_shared<EventJoystickAxisMotion>(e->jaxis.which, e->jaxis.axis, e->jaxis.value);
			case SDL_JOYBALLMOTION:				return std::make_shared<EventJoystickBallMotion>(e->jball.which, e->jball.ball, e->jball.xrel, e->jball.yrel);
			case SDL_JOYHATMOTION:				return std::make_shared<EventJoystickHatMotion>(e->jhat.which, e->jhat.hat, get_hat_position(e));
			case SDL_JOYBUTTONDOWN:				return std::make_shared<EventJoystickButtonDown>(e->jbutton.which, e->jbutton.button);
			case SDL_JOYBUTTONUP:				return std::make_shared<EventJoystickButtonUp>(e->jbutton.which, e->jbutton.button);
			case SDL_JOYDEVICEADDED:			return std::make_shared<EventJoystickDeviceAdded>(e->jdevice.which);
			case SDL_JOYDEVICEREMOVED:			return std::make_shared<EventJoystickDeviceRemoved>(e->jdevice.which);
			case SDL_JOYBATTERYUPDATED:			return std::make_shared<EventJoystickBatteryUpdated>(e->jbattery.which, get_joystick_battery_level(e));
			
			case SDL_CONTROLLERAXISMOTION:		return std::make_shared<EventControllerAxisMotion>(e->caxis.which, e->caxis.axis, e->caxis.value);
			case SDL_CONTROLLERBUTTONDOWN:		return std::make_shared<EventControllerButtonDown>(e->cbutton.which, (controller_button_t)(e->cbutton.button));
			case SDL_CONTROLLERBUTTONUP:		return std::make_shared<EventControllerButtonUp>(e->cbutton.which, (controller_button_t)(e->cbutton.button));
			case SDL_CONTROLLERDEVICEADDED:		return std::make_shared<EventControllerDeviceAdded>(e->cdevice.which);
			case SDL_CONTROLLERDEVICEREMOVED:	return std::make_shared<EventControllerDeviceRemoved>(e->cdevice.which);
			case SDL_CONTROLLERDEVICEREMAPPED:	return std::make_shared<EventControllerDeviceRemapped>(e->cdevice.which);
			case SDL_CONTROLLERTOUCHPADMOTION:	return create_controller_touchpad_event(e);
			case SDL_CONTROLLERTOUCHPADDOWN:	return create_controller_touchpad_event(e);
			case SDL_CONTROLLERTOUCHPADUP:		return create_controller_touchpad_event(e);
			case SDL_CONTROLLERSENSORUPDATE:	return create_controller_sensor_event(e);

			case SDL_FINGERDOWN:				return create_touch_event(e);
			case SDL_FINGERUP:					return create_touch_event(e);
			case SDL_FINGERMOTION:				return create_touch_event(e);

			case SDL_DOLLARGESTURE:				return create_gesture_event(e);
			case SDL_DOLLARRECORD:				return create_gesture_event(e);
			case SDL_MULTIGESTURE:				return create_gesture_event(e);

			case SDL_RENDER_TARGETS_RESET:		return std::make_shared<EventRenderTargetsReset>();
			case SDL_RENDER_DEVICE_RESET:		return std::make_shared<EventRenderDeviceReset>();

			default:							return parse_unsupported_event(e);
		}
	}

	/**
	 * @brief	Callback function for all SDL events.
	 * 
	 * @param data	User data (unused).
	 * @param event	The SDL event.
	 * @return int	Always 0.
	 */
	int sdl_event_callback(void *data, SDL_Event *event)
	{
		std::shared_ptr<Event> e = parse_sdl_event(event);
		int err = -1;

		if(e != nullptr)
		{
			log_engine_debug("Dispatching SDL event: [{0} : {1:d}].", e->ToString(), (uint16_t)event->type);
			event_dispatch(e);
			err = 0;
		}

		return err;
	}

	/// @brief	Initializes SDL event handling. This will link SDL events into the tractor event system.
	void sdl_init_events()
	{
		// Disable all SDL events by default. Events will be enabled as listeners are registered to various event types.
		for(auto event : kSdlEventList)
		{
			SDL_EventState(event, SDL_IGNORE);
		}

		SDL_FlushEvents(0, SDL_LASTEVENT);
		SDL_AddEventWatch(sdl_event_callback, nullptr);
	}

	/// @brief Construct a new Sdl Listener Tracker.
	SdlListenerTracker::SdlListenerTracker() : 
		sdl_listener_counts_{}
	{}

	/**
	 * @brief	Adds a listener to the tracker. This will enable the SDL event type if it is not already enabled, and increment the listener count for the
	 * 			event type.
	 * 
	 * @param e	The event to add.
	 */
	void SdlListenerTracker::AddListener(const std::shared_ptr<trac::Event> e)
	{
		AddListener(e->GetType());
	}

	/**
	 * @brief	Adds a listener to the tracker. This will enable the SDL event type if it is not already enabled, and increment the listener count for the
	 * 			event type.
	 * 
	 * @param e_type	The event type to add.
	 * 
	 */
	void SdlListenerTracker::AddListener(const trac::EventType e_type)
	{
		const SDL_EventType sdl_event = get_sdl_event_type(e_type);
		MapInsertListener(sdl_event);
	}

	/**
	 * @brief	Removes the event listener from the tracker. This function will obtain the event type from the event, and call the other RemoveListener
	 * 			function.
	 * 
	 * @param e	The event to remove.
	 */
	void SdlListenerTracker::RemoveListener(const std::shared_ptr<trac::Event> e)
	{
		RemoveListener(e->GetType());
	}

	/**
	 * @brief	Removes a listener from the tracker. This will decrement the listener count for the event type, and disable the SDL event type if the listener
	 * 			count reaches zero.
	 * 
	 * If the listener count becomes zero at the end of this function, the SDL event type will also be removed from the map.
	 * 
	 * @param e_type	The event type to remove.
	 */
	void SdlListenerTracker::RemoveListener(const trac::EventType e_type)
	{
		MapRemoveListener(get_sdl_event_type(e_type));
	}

	/**
	 * @brief	Checks if the tracker has a listener for the given SDL event type.
	 * 
	 * @param event_type	The SDL event type to check.
	 * @return bool	Whether or not the tracker has a listener for the given SDL event type.
	 */
	bool SdlListenerTracker::MapHasListener(const SDL_EventType event_type)
	{
		auto it = sdl_listener_counts_.find(event_type);
		const bool has_listener = (it == sdl_listener_counts_.end()) ? false : (it->second > 0);
		return has_listener;
	}
	
	/**
	 * @brief	Inserts a listener for the given SDL event type into the tracker. This will enable the SDL event type if it is not already enabled, and
	 * 			increment the listener count for the event type. If the event type is already in the map, the listener count will be incremented.
	 * 			If the event type is not in the map, it will be added with a listener count of 1.
	 * 
	 * @param event_type	The SDL event type to insert.
	 */
	void SdlListenerTracker::MapInsertListener(const SDL_EventType event_type)
	{
		auto it = sdl_listener_counts_.find(event_type);
		if((it == sdl_listener_counts_.end()) || (it->second == 0))
		{
			SDL_EventState(event_type, SDL_ENABLE);
			sdl_listener_counts_.insert(std::make_pair(event_type, 1));
			log_engine_debug("'MapInsertListener' added the first listener with SDL event type [{0:d}] and enabled the event.", (uint16_t)event_type);
		}
		else
		{
			it->second++;
		}
	}

	/**
	 * @brief	Removes a listener for the given SDL event type from the tracker. This will decrement the listener count for the event type, and disable the
	 * 			SDL event type if the listener count reaches zero. If the listener count becomes zero at the end of this function, the SDL event type will
	 * 			also be removed from the map.
	 * 
	 * @param event_type	The SDL event type to remove.
	 * @return bool	Whether or not any listeners remain for the SDL event type.
	 * @retval true	There are still listeners for the SDL event type.
	 * @retval false	There are no more listeners for the SDL event type and the SDL event type has been disabled and removed from the map.
	 */
	bool SdlListenerTracker::MapRemoveListener(const SDL_EventType event_type)
	{
		bool listeners_remain = false;

		auto it = sdl_listener_counts_.find(event_type);
		if(it == sdl_listener_counts_.end())
		{
			log_engine_warn("'MapRemoveListener' attempted to remove listener with SDL event type [{0:d}] that is not in the map.", (uint16_t)event_type);
			listeners_remain = false;
		}
		else if(it->second == 1)
		{
			SDL_EventState(event_type, SDL_IGNORE);
			sdl_listener_counts_.erase(it);
			listeners_remain = false;
			log_engine_debug("'MapRemoveListener' removed the last listener with SDL event type [{0:d}] and disabled the event.", (uint16_t)event_type);
		}
		else
		{
			it->second--;
			listeners_remain = true;
		}

		return listeners_remain;
	}

} // namespace trac
