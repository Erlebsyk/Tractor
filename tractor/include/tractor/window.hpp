/**
 * @file	window.hpp
 * @brief	Module for creating and interacting with windows. This module creates a simple interface for window creation and interaction, from which
 * 			platform-specific window implementations can be derived. The basic window implementation is a SDL window with an OpenGL context that supports
 * 			cross-platform window creation and interaction.
 * 
 * @author	Erlend Elias Isachsen
 * @date	07.08.2023
 * 
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

// External libraries header includes
#include <SDL_video.h>
#include <SDL_opengl.h>

// Project header includes
#include "events/event.hpp"

namespace trac
{
	/// @brief	Window properties struct.
	struct WindowProperties
	{
		/// The title of the window.
		std::string title;
		/// The width of the window.
		uint32_t width;
		/// The height of the window.
		uint32_t height;
		/// The x-position of the window.
		uint32_t pos_x;
		/// The y-position of the window.
		uint32_t pos_y;
		/// Whether or not Vsync should be enabled for the window.
		bool vsync;

		WindowProperties(
			const std::string& title = "Tractor Engine",
			uint32_t width = 1280,
			uint32_t height = 720,
			uint32_t pos_x = SDL_WINDOWPOS_UNDEFINED,
			uint32_t pos_y = SDL_WINDOWPOS_UNDEFINED,
			bool vsync = true
		);
	};

	/// @brief	Struct containing window callback functions.
	struct WindowCallbacks
	{
		/// Blocking callback function for window events.
		event_cb_b_fn* callback_blocking;
		/// Non-blocking callback function for window events.
		event_cb_nb_fn* callback_non_blocking;

		WindowCallbacks(event_cb_b_fn* callback_blocking = nullptr, event_cb_nb_fn* callback_non_blocking = nullptr);
	};

	/**
	 * @brief	Window interface class. The window interface contains all the functions that are relevant for applications, and does not contain any
	 * 			platform-specific code or window data. Every actual window is be derived from this class and implement the functions, but the application
	 * 			only refers to the window interface.
	 */
	class Window
	{
	public:
		// Constructors and destructors

		/// @brief	Default destructor.
		virtual ~Window() = default;
	
		//Public functions

		/// @brief	Runs whenever the window is updated.
		virtual void OnUpdate() = 0;

		/// @brief	Get the width of the window.
		virtual uint32_t GetWidth() const = 0;
		/// @brief	Get the height of the window.
		virtual uint32_t GetHeight() const = 0;

		/**
		 * @brief	Set a blocking callback function for when a window event is triggered.
		 * 
		 * @param callback_blocking	The callback function to be called when a window event is triggered.
		 */
		virtual void SetEventCallbackB(event_cb_b_fn* callback_blocking) = 0;

		/**
		 * @brief	Set a non-blocking callback function for when a window event is triggered.
		 * 
		 * @param callback_non_blocking	The callback function to be called when a window event is triggered.
		 */
		virtual void SetEventCallbackNb(event_cb_nb_fn* callback_non_blocking) = 0;
	
		/**
		 * @brief	Set whether or not Vsync should be enabled for the window.
		 * 
		 * @param enabled	Whether or not Vsync should be enabled.
		 */
		virtual void SetVsync(bool enabled) = 0;
		/// @brief	Check if Vsync is enabled for the window.
		virtual bool IsVsyncEnabled() const = 0;

		/// @brief	Get the native window pointer.
		virtual void* GetNativeWindow() const = 0;

		static std::shared_ptr<Window> Create(const WindowProperties& properties = WindowProperties());
	};

	/**
	 * @brief	Basic window class.
	 */
	class WindowBasic : public Window
	{
	public:
		// Constructors and destructors
		WindowBasic(const WindowProperties& properties = WindowProperties());
		virtual ~WindowBasic();
	
		//Public functions
	
		void OnUpdate() override;

		uint32_t GetWidth() const override;
		uint32_t GetHeight() const override;

		void SetEventCallbackB(event_cb_b_fn* callback_blocking) override;
		void SetEventCallbackNb(event_cb_nb_fn* callback_non_blocking) override;

		void SetVsync(bool enabled) override;
		bool IsVsyncEnabled() const override;

		void* GetNativeWindow() const override;

	private:
		// Private functions

		void Init();
		void Shutdown();

		// Private variables
		static uint32_t windows_n_;

		WindowProperties properties_;
		WindowCallbacks callbacks_;

		SDL_Window* window_;
		SDL_GLContext context_;
	};

} // Namespace trac

#endif // WINDOW_HPP_ 