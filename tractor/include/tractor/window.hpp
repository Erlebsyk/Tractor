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
#include "events.hpp"
#include "utils/bits.hpp"

namespace trac
{
	/// Defines the default window properties
	struct WindowPropertiesDefault
	{
		/// The default title of the window.
		static constexpr const char* kTitle = "Tractor Engine";
		/// The default width of the window.
		static constexpr uint32_t kWidth = 1280;
		/// The default height of the window.
		static constexpr uint32_t kHeight = 720;
		/// The default x-position of the window.
		static constexpr uint32_t kPosX = SDL_WINDOWPOS_UNDEFINED;
		/// The default y-position of the window.
		static constexpr uint32_t kPosY = SDL_WINDOWPOS_UNDEFINED;
		/// Whether or not Vsync should be enabled for the window by default.
		static constexpr bool kVsync = true;
		/// Whether or not the window should be resizable by default.
		static constexpr bool kResizable = true;
		/// Whether or not the window should be borderless by default.
		static constexpr bool kBorderless = false;
		/// Whether or not the window should be fullscreen by default.
		static constexpr bool kFullscreen = false;
		/// Whether or not the window should be visible by default.
		static constexpr bool kVisible = true;
		/// Whether or not the window should be minimized by default.
		static constexpr bool kMinimized = false;
		/// Whether or not the window should be maximized by default.
		static constexpr bool kMaximized = false;
		/// Whether or not the mouse should be grabbed by the window by default.
		static constexpr bool kMouseGrabbed = false;
		/// Whether or not the window should have input focus by default.
		static constexpr bool kInputFocus = false;
		/// Whether or not the window should have mouse focus by default.
		static constexpr bool kMouseFocus = false;
		/// Whether or not the window should be high DPI by default.
		static constexpr bool kHighDPI = false;
		/// Whether or not the mouse should be captured by the window by default.
		static constexpr bool kMouseCaptured = false;
		/// Whether or not the window should always be on top by default.
		static constexpr bool kAlwaysOnTop = false;
		/// Whether or not the keyboard should be grabbed by the window by default.
		static constexpr bool kKeyboardGrabbed = false;
		/// Whether or not input should be grabbed by the window by default.
		static constexpr bool kInputGrabbed = false;
	};

	/// @brief	Window status flags.
	typedef enum
	{
		kWindowFullscreen = BIT(0),
		kWindowVisible = BIT(1),
		kWindowResizable = BIT(2),
		kWindowBorderless = BIT(3),
		kWindowMinimized = BIT(4),
		kWindowMaximized = BIT(5),
		kWindowMouseGrabbed = BIT(6),
		kWindowInputFocus = BIT(7),
		kWindowMouseFocus = BIT(8),
		kWindowHighDPI = BIT(9),
		kWindowMouseCaptured = BIT(10),
		kWindowAlwaysOnTop = BIT(11),
		kWindowKeyboardGrabbed = BIT(12),
		kWindowInputGrabbed = BIT(13)
	} WindowStatus;

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
		/// Whether or not the window should be resizable.
		bool resizable;
		/// Whether or not the window should be borderless.
		bool borderless;
		/// Whether or not the window should be fullscreen.
		bool fullscreen;
		/// Whether or not the window should be visible.
		bool visible;
		/// Whether or not the window should be minimized.
		bool minimized;
		/// Whether or not the window should be maximized.
		bool maximized;
		/// Whether or not the mouse should be grabbed by the window.
		bool mouse_grabbed;
		/// Whether or not the window should have input focus.
		bool input_focus;
		/// Whether or not the window should have mouse focus.
		bool mouse_focus;
		/// Whether or not the window should be high DPI.
		bool high_dpi;
		/// Whether or not the mouse should be captured by the window.
		bool mouse_captured;
		/// Whether or not the window should always be on top.
		bool always_on_top;
		/// Whether or not the keyboard should be grabbed by the window.
		bool keyboard_grabbed;
		/// Whether or not input should be grabbed by the window.
		bool input_grabbed;

		WindowProperties(
			const std::string& title = WindowPropertiesDefault::kTitle,
			uint32_t width = WindowPropertiesDefault::kWidth,
			uint32_t height = WindowPropertiesDefault::kHeight,
			uint32_t pos_x = WindowPropertiesDefault::kPosX,
			uint32_t pos_y = WindowPropertiesDefault::kPosY,
			bool vsync = WindowPropertiesDefault::kVsync,
			bool resizable = WindowPropertiesDefault::kResizable,
			bool borderless = WindowPropertiesDefault::kBorderless,
			bool fullscreen = WindowPropertiesDefault::kFullscreen,
			bool visible = WindowPropertiesDefault::kVisible,
			bool minimized = WindowPropertiesDefault::kMinimized,
			bool maximized = WindowPropertiesDefault::kMaximized,
			bool mouse_grabbed = WindowPropertiesDefault::kMouseGrabbed,
			bool input_focus = WindowPropertiesDefault::kInputFocus,
			bool mouse_focus = WindowPropertiesDefault::kMouseFocus,
			bool high_dpi = WindowPropertiesDefault::kHighDPI,
			bool mouse_captured = WindowPropertiesDefault::kMouseCaptured,
			bool always_on_top = WindowPropertiesDefault::kAlwaysOnTop,
			bool keyboard_grabbed = WindowPropertiesDefault::kKeyboardGrabbed,
			bool input_grabbed = WindowPropertiesDefault::kInputGrabbed
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

		/**
		 * @brief	Get the width of the window.
		 * @return uint32_t	The width of the window in pixels.
		 */
		virtual uint32_t GetWidth() const = 0;
		
		/**
		 * @brief	Get the height of the window.
		 * @return uint32_t	The height of the window in pixels.
		 */
		virtual uint32_t GetHeight() const = 0;

		virtual void SetSize(uint32_t width, uint32_t height);
		/**
		 * @brief	Set the width of the window.
		 * @param width	The width of the window in pixels.
		 */
		virtual void SetWidth(uint32_t width) = 0;
		/**
		 * @brief	Set the height of the window.
		 * @param height	The height of the window in pixels.
		 */
		virtual void SetHeight(uint32_t height) = 0;

		/// @brief  Close the window.
		virtual void Open() = 0;
		/// @brief  Close the window.
		virtual void Close() = 0;
		/// @brief  Show the window.
		virtual void Show() = 0;
		/// @brief  Hide the window.
		virtual void Hide() = 0;

		/**
		 * @brief	Check if the window is open.
		 * @return bool	True if the window is open, false otherwise.
		 */
		virtual bool IsOpen() const = 0;

		/**
		 * @brief	Get the status flags of the window.
		 * @return uint32_t	The status of the window, as a bitfield of WindowStatus flags.
		 */
		virtual uint32_t GetStatusFlags() const = 0;
		
		bool IsFullscreen() const;
		bool IsVisible() const;
		bool IsResizable() const;
		bool IsBorderless() const;
		bool IsMinimized() const;
		bool IsMaximized() const;
		bool IsMouseGrabbed() const;
		bool IsInputFocus() const;
		bool IsMouseFocus() const;
		bool IsHighDPI() const;
		bool IsMouseCaptured() const;
		bool IsAlwaysOnTop() const;
		bool IsKeyboardGrabbed() const;
		bool IsInputGrabbed() const;

		/**
		 * @brief	Set a blocking callback function for when a window event is triggered.
		 * @param callback_blocking	The callback function to be called when a window event is triggered.
		 */
		virtual void SetEventCallbackB(event_cb_b_fn* callback_blocking) = 0;

		/**
		 * @brief	Set a non-blocking callback function for when a window event is triggered.
		 * @param callback_non_blocking	The callback function to be called when a window event is triggered.
		 */
		virtual void SetEventCallbackNb(event_cb_nb_fn* callback_non_blocking) = 0;
	
		/**
		 * @brief	Set whether or not Vsync should be enabled for the window.
		 * @param enabled	Whether or not Vsync should be enabled.
		 */
		virtual void SetVsync(bool enabled) = 0;

		/**
		 * @brief	Set the title of the window.
		 * @param title	The title of the window.
		 */
		virtual void SetTitle(std::string title) = 0;

		/**
		 * @brief	Set the x position of the window.
		 * @param x	The x-position of the window.
		 */
		virtual void SetX(uint32_t x) = 0;

		/**
		 * @brief	Set the y position of the window.
		 * 
		 * @param y	The y-position of the window.
		 */
		virtual void SetY(uint32_t y) = 0;

		virtual void SetPosition(uint32_t x, uint32_t y);

		/**
		 * @brief	Set whether or not the window should be fullscreen.
		 * @param enabled	Whether or not the window should be fullscreen.
		 */
		virtual void SetFullscreen(bool enabled) = 0;

		/**
		 * @brief	Set whether or not the window should be resizable.
		 * @param enabled	Whether or not the window should be resizable.
		 */
		virtual void SetResizable(bool enabled) = 0;

		/**
		 * @brief	Set whether or not the window should be borderless.
		 * @param enabled	Whether or not the window should be borderless.
		 */
		virtual void SetBorderless(bool enabled) = 0;

		/**
		 * @brief	Set whether or not the window should be minimized.
		 * @param enabled	Whether or not the window should be minimized.
		 */
		virtual void SetMinimized(bool enabled) = 0;

		/**
		 * @brief	Set whether or not the window should be maximized.
		 * @param enabled	Whether or not the window should be maximized.
		 */
		virtual void SetMaximized(bool enabled) = 0;

		/**
		 * @brief	Set whether or not the mouse should be grabbed by the window.
		 * @param enabled	Whether or not the mouse should be grabbed by the window.
		 */
		virtual void SetMouseGrabbed(bool enabled) = 0;

		/// @brief Set whether or not the window should have input focus.
		virtual void SetInputFocus() = 0;

		/**
		 * @brief	Set whether or not the window should always be on top.
		 * @param enabled	Whether or not the window should always be on top.
		 */
		virtual void SetAlwaysOnTop(bool enabled) = 0;

		/**
		 * @brief	Set whether or not the keyboard should be grabbed by the window.
		 * @param enabled	Whether or not the keyboard should be grabbed by the window.
		 */
		virtual void SetKeyboardGrabbed(bool enabled) = 0;

		/**
		 * @brief	Set whether or not input should be grabbed by the window.
		 * @param enabled	Whether or not input should be grabbed by the window.
		 */
		virtual void SetInputGrabbed(bool enabled) = 0;

		/// @brief	Check if Vsync is enabled for the window.
		virtual bool IsVsyncEnabled() const = 0;

		/// @brief	Get the native window pointer.
		virtual void* GetNativeWindow() const = 0;

		static std::unique_ptr<Window> Create(const WindowProperties& properties = WindowProperties());
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

		void SetSize(uint32_t width, uint32_t height) override;
		void SetWidth(uint32_t width) override;
		void SetHeight(uint32_t height) override;

		void Open() override;
		void Close() override;
		void Show() override;
		void Hide() override;

		bool IsOpen() const override;

		uint32_t GetStatusFlags() const override;

		void SetEventCallbackB(event_cb_b_fn* callback_blocking) override;
		void SetEventCallbackNb(event_cb_nb_fn* callback_non_blocking) override;

		void SetTitle(std::string title) override;
		void SetX(uint32_t x) override;
		void SetY(uint32_t y) override;
		void SetPosition(uint32_t x, uint32_t y) override;
		void SetVsync(bool enabled) override;
		void SetFullscreen(bool enabled) override;
		void SetResizable(bool enabled) override;
		void SetBorderless(bool enabled) override;
		void SetMinimized(bool enabled) override;
		void SetMaximized(bool enabled) override;
		void SetMouseGrabbed(bool enabled) override;
		void SetInputFocus() override;
		void SetAlwaysOnTop(bool enabled) override;
		void SetKeyboardGrabbed(bool enabled) override;
		void SetInputGrabbed(bool enabled) override;
		
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

		bool open_;
	};

} // Namespace trac

#endif // WINDOW_HPP_ 