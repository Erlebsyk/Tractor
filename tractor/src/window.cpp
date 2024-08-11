/**
 * @file	window.cpp
 * @brief	Sources file for the window class. See window.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	07.08.2023
 * 
*/

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "window.hpp"

// External library header includes
#include <SDL_events.h>

// Project header includes
#include "events.hpp"
#include "logger.hpp"

namespace trac
{
	/// The number of existing windows.
	uint32_t WindowBasic::windows_n_ = 0;

	/**
	 * @brief	Construct a new Window Properties object.
	 * 
	 * @param title	The title of the window.
	 * @param width	The width of the window.
	 * @param height	The height of the window.
	 * @param pos_x	The horizontal position of the window.
	 * @param pos_y	The vertical position of the window.
	 * @param vsync	Whether or not Vsync should be enabled for the window.
	 * @param fullscreen	Whether or not the window should be in fullscreen mode.
	 * @param resizable	Whether or not the window should be resizable.
	 * @param borderless	Whether or not the window should be borderless.
	 * @param visible	Whether or not the window should be visible.
	 * @param minimized	Whether or not the window should be minimized.
	 * @param maximized	Whether or not the window should be maximized.
	 * @param mouse_grabbed	Whether or not the mouse should be grabbed by the window.
	 * @param input_focus	Whether or not the window should have input focus.
	 * @param mouse_focus	Whether or not the window should have mouse focus.
	 * @param high_dpi	Whether or not the window should be in high DPI mode.
	 * @param mouse_captured	Whether or not the mouse should be captured by the window.
	 * @param always_on_top	Whether or not the window should always be on top.
	 * @param keyboard_grabbed	Whether or not the keyboard should be grabbed by the window.
	 * @param input_grabbed	Whether or not input should be grabbed by the window.
	 */
	WindowProperties::WindowProperties(
		const std::string& title,
		const uint32_t width,
		const uint32_t height,
		const uint32_t pos_x,
		const uint32_t pos_y,
		const bool vsync,
		const bool fullscreen,
		const bool resizable,
		const bool borderless,
		const bool visible,
		const bool minimized,
		const bool maximized,
		const bool mouse_grabbed,
		const bool input_focus,
		const bool mouse_focus,
		const bool high_dpi,
		const bool mouse_captured,
		const bool always_on_top,
		const bool keyboard_grabbed,
		const bool input_grabbed
	) : 
		title			{ title 			},
		width			{ width 			},
		height			{ height			},
		pos_x			{ pos_x				},
		pos_y			{ pos_y				},
		vsync			{ vsync				},
		fullscreen		{ fullscreen		},
		resizable		{ resizable			},
		borderless		{ borderless		},
		visible			{ visible			},
		minimized		{ minimized			},
		maximized		{ maximized			},
		mouse_grabbed	{ mouse_grabbed		},
		input_focus		{ input_focus		},
		mouse_focus		{ mouse_focus		},
		high_dpi		{ high_dpi			},
		mouse_captured	{ mouse_captured	},
		always_on_top	{ always_on_top		},
		keyboard_grabbed{ keyboard_grabbed	},
		input_grabbed	{ input_grabbed		}
	{}

	/**
	 * @brief	Constructs a WindowCallbacks struct.
	 * 
	 * @param callback_blocking	Blocking callback function for window events.
	 * @param callback_non_blocking	Non-blocking callback function for window events.
	 */
	WindowCallbacks::WindowCallbacks(event_cb_b_fn* callback_blocking, event_cb_nb_fn* callback_non_blocking) :
		callback_blocking		{ callback_blocking		},
		callback_non_blocking	{ callback_non_blocking	}
	{}

	/**
	 * @brief	Set the size of the window.
	 * 
	 * @param width	The width of the window.
	 * @param height	The height of the window.
	 */
	void Window::SetSize(const uint32_t width, const uint32_t height)
	{
		SetWidth(width);
		SetHeight(height);
	}

	/**
	 * @brief	Check if the window is in fullscreen mode.
	 * @return bool	Whether or not the window is in fullscreen mode.
	 * @retval true	The window is in fullscreen mode.
	 * @retval false	The window is not in fullscreen mode.
	 */
	bool Window::IsFullscreen() const
	{
		return kWindowFullscreen & GetStatusFlags();
	}

	/**
	 * @brief	Check if the window is currently visible.
	 * @return bool	Whether or not the window is visible.
	 * @retval true	The window is visible.
	 * @retval false	The window is not visible.
	 */
	bool Window::IsVisible() const
	{
		return kWindowVisible & GetStatusFlags();
	}

	/**
	 * @brief	Check if the window is resizable.
	 * @return bool	Whether or not the window is resizable.
	 * @retval true	The window is resizable.
	 * @retval false	The window is not resizable.
	 */
	bool Window::IsResizable() const
	{
		return kWindowResizable & GetStatusFlags();
	}

	/**
	 * @brief	Check if the window is borderless.
	 * @return bool	Whether or not the window is borderless.
	 * @retval true	The window is borderless.
	 * @retval false	The window is not borderless.
	 */
	bool Window::IsBorderless() const
	{
		return kWindowBorderless & GetStatusFlags();
	}

	/**
	 * @brief	Check if the window is minimized.
	 * @return bool	Whether or not the window is minimized.
	 * @retval true	The window is minimized.
	 * @retval false	The window is not minimized.
	 */
	bool Window::IsMinimized() const
	{
		return kWindowMinimized & GetStatusFlags();
	}

	/**
	 * @brief	Check if the window is maximized.
	 * @return bool	Whether or not the window is maximized.
	 * @retval true	The window is maximized.
	 * @retval false	The window is not maximized.
	 */
	bool Window::IsMaximized() const
	{
		return kWindowMaximized & GetStatusFlags();
	}

	/**
	 * @brief	Check if the mouse is grabbed by the window.
	 * @return bool	Whether or not the mouse is grabbed by the window.
	 * @retval true	The mouse is grabbed by the window.
	 * @retval false	The mouse is not grabbed by the window.
	 */
	bool Window::IsMouseGrabbed() const
	{
		return kWindowMouseGrabbed & GetStatusFlags();
	}

	/**
	 * @brief	Check if the window has input focus.
	 * @return bool	Whether or not the window has input focus.
	 * @retval true	The window has input focus.
	 * @retval false	The window does not have input focus.
	 */
	bool Window::IsInputFocus() const
	{
		return kWindowInputFocus & GetStatusFlags();
	}

	/**
	 * @brief	Check if the mouse has focus.
	 * @return bool	Whether or not the mouse has focus.
	 * @retval true	The mouse has focus.
	 * @retval false	The mouse does not have focus.
	 */
	bool Window::IsMouseFocus() const
	{
		return kWindowMouseFocus & GetStatusFlags();
	}

	/**
	 * @brief	Check if the window is in high DPI mode.
	 * @return bool	Whether or not the window is in high DPI mode.
	 * @retval true	The window is in high DPI mode.
	 * @retval false	The window is not in high DPI mode.
	 */
	bool Window::IsHighDPI() const
	{
		return kWindowHighDPI & GetStatusFlags();
	}

	/**
	 * @brief	Check if the mouse is captured by the window.
	 * @return bool	Whether or not the mouse is captured by the window.
	 * @retval true	The mouse is captured by the window.
	 * @retval false	The mouse is not captured by the window.
	 */
	bool Window::IsMouseCaptured() const
	{
		return kWindowMouseCaptured & GetStatusFlags();
	}

	/**
	 * @brief	Check if the window is always on top.
	 * @return bool	Whether or not the window is always on top.
	 * @retval true	The window is always on top.
	 * @retval false	The window is not always on top.
	 */
	bool Window::IsAlwaysOnTop() const
	{
		return kWindowAlwaysOnTop & GetStatusFlags();
	}

	/**
	 * @brief	Check if the keyboard is grabbed by the window.
	 * @return bool	Whether or not the keyboard is grabbed by the window.
	 * @retval true	The keyboard is grabbed by the window.
	 * @retval false	The keyboard is not grabbed by the window.
	 */
	bool Window::IsKeyboardGrabbed() const
	{
		return kWindowKeyboardGrabbed & GetStatusFlags();
	}

	/**
	 * @brief	Check if input is grabbed by the window.
	 * @return bool	Whether or not input is grabbed by the window.
	 * @retval true	Input is grabbed by the window.
	 * @retval false	Input is not grabbed by the window.
	 */
	bool Window::IsInputGrabbed() const
	{
		return kWindowInputGrabbed & GetStatusFlags();
	}

	/**
	 * @brief	Set the position of the window on the screen.
	 * 
	 * @param x	The horizontal position of the window.
	 * @param y	The vertical position of the window.
	 */
	void Window::SetPosition(const uint32_t x, const uint32_t y)
	{
		SetX(x);
		SetY(y);
	}

	/**
	 * @brief	Creates a new window. This definition determines which window type to use, and can be changed to use a different window type by defining
	 * 			preprocessor macros for selecting window type.
	 * 
	 * @param properties	The properties of the window.
	 * @return std::unique_ptr<Window>	A unique pointer to the window.
	 */
	std::unique_ptr<Window> Window::Create(const WindowProperties& properties)
	{
		return std::make_unique<WindowBasic>(properties);
	}

	/**
	 * @brief	Constructs a new window.
	 * 
	 * @param properties	The properties of the window.
	 */
	WindowBasic::WindowBasic(const WindowProperties& properties) : 
		properties_		{ properties		},
		callbacks_		{ WindowCallbacks()	},
		window_			{ nullptr			},
		context_		{ nullptr			},
		open_			{ false				}
	{
		Init();
		windows_n_++;
	}

	/// @brief	Destructor for the window.
	WindowBasic::~WindowBasic()
	{
		Shutdown();
		windows_n_--;
	}

	/// @brief	Function called whenever the window is updated.
	void WindowBasic::OnUpdate()
	{

	}

	/**
	 * @brief	Get the width of the window.
	 * 
	 * @return uint32_t	The width of the window.
	 */
	uint32_t WindowBasic::GetWidth() const
	{
		return properties_.width;
	}

	/**
	 * @brief	Get the height of the window.
	 * 
	 * @return uint32_t	The height of the window.
	 */
	uint32_t WindowBasic::GetHeight() const
	{
		return properties_.height;
	}

	/**
	 * @brief	Set the width and height of the window.
	 * 
	 * @param width	The width of the window.
	 * @param height	The height of the window.
	 */
	void WindowBasic::SetSize(const uint32_t width, const uint32_t height)
	{
		SDL_SetWindowSize(window_, width, height);
		properties_.width = width;
		properties_.height = height;
	}

	/**
	 * @brief	Set the width of the window.
	 * 
	 * @param width	The width of the window.
	 */
	void WindowBasic::SetWidth(const uint32_t width)
	{
		SetSize(width, properties_.height);
	}

	/**
	 * @brief	Set the height of the window.
	 * 
	 * @param height	The height of the window.
	 */
	void WindowBasic::SetHeight(const uint32_t height)
	{
		SetSize(properties_.width, height);
	}
	
	/// @brief  Opens the window if it is closed.
	void WindowBasic::Open()
	{
		if(!open_)
			Init();
	}

	/// @brief	Close the window.
	void WindowBasic::Close()
	{
		if(open_)
			Shutdown();
	}

	/// @brief	Show the window.
	void WindowBasic::Show()
	{
		SDL_ShowWindow(window_);
		properties_.visible = true;
	}

	/// @brief	Hide the window.
	void WindowBasic::Hide()
	{
		SDL_HideWindow(window_);
		properties_.visible = false;
	}

	/**
	 * @brief	Check if the window is open.
	 * 
	 * @return bool	Whether or not the window is open.
	 * @retval true	The window is open.
	 * @retval false	The window is closed.
	 */
	bool WindowBasic::IsOpen() const
	{
		return open_;
	}

	/**
	 * @brief	Get the status flags of the window as a 32-bit bitfield.
	 * 
	 * @return uint32_t	The status flags of the window.
	 */
	uint32_t WindowBasic::GetStatusFlags() const
	{
		const uint32_t sdl_flags = SDL_GetWindowFlags(window_);
		uint32_t status_flags = 0;

		status_flags |= (sdl_flags & SDL_WINDOW_FULLSCREEN) ? kWindowFullscreen : 0;
		status_flags |= (sdl_flags & SDL_WINDOW_SHOWN) ? kWindowVisible : 0;
		status_flags |= (sdl_flags & SDL_WINDOW_RESIZABLE) ? kWindowResizable : 0;
		status_flags |= (sdl_flags & SDL_WINDOW_BORDERLESS) ? kWindowBorderless : 0;
		status_flags |= (sdl_flags & SDL_WINDOW_MINIMIZED) ? kWindowMinimized : 0;
		status_flags |= (sdl_flags & SDL_WINDOW_MAXIMIZED) ? kWindowMaximized : 0;
		status_flags |= (sdl_flags & SDL_WINDOW_MOUSE_GRABBED) ? kWindowMouseGrabbed : 0;
		status_flags |= (sdl_flags & SDL_WINDOW_INPUT_FOCUS) ? kWindowInputFocus : 0;
		status_flags |= (sdl_flags & SDL_WINDOW_MOUSE_FOCUS) ? kWindowMouseFocus : 0;
		status_flags |= (sdl_flags & SDL_WINDOW_ALLOW_HIGHDPI) ? kWindowHighDPI : 0;
		status_flags |= (sdl_flags & SDL_WINDOW_MOUSE_CAPTURE) ? kWindowMouseCaptured : 0;
		status_flags |= (sdl_flags & SDL_WINDOW_ALWAYS_ON_TOP) ? kWindowAlwaysOnTop : 0;
		status_flags |= (sdl_flags & SDL_WINDOW_KEYBOARD_GRABBED) ? kWindowKeyboardGrabbed : 0;
		status_flags |= (sdl_flags & SDL_WINDOW_INPUT_GRABBED) ? kWindowInputGrabbed : 0;

		return status_flags;
	}

	/**
	 * @brief	Set a blocking callback function for window events.
	 * 
	 * @param callback_blocking	The blocking callback function.
	 */
	void WindowBasic::SetEventCallbackB(event_cb_b_fn* callback_blocking)
	{
		callbacks_.callback_blocking = callback_blocking;
	}

	/**
	 * @brief	Set a non-blocking callback function for window events.
	 * 
	 * @param callback_non_blocking	The non-blocking callback function.
	 */
	void WindowBasic::SetEventCallbackNb(event_cb_nb_fn* callback_non_blocking)
	{
		callbacks_.callback_non_blocking = callback_non_blocking;
	}

	/**
	 * @brief	Set whether or not vsync should be enabled for the window.
	 * 
	 * @param enabled	Whether or not vsync should be enabled.
	 */
	void WindowBasic::SetVsync(const bool enabled)
	{
		const int sdl_enable_val = (enabled) ? -1 : 0;
		int vsync_status = SDL_GL_SetSwapInterval(enabled);
		if(vsync_status < 0 && enabled) // Adaptive VSync failed.
			vsync_status = SDL_GL_SetSwapInterval(1); // Try regular VSync.
		
		if(vsync_status == 0)
			properties_.vsync = enabled;
		else
			log_engine_error("SDL could not [%s] vsync! SDL error: [%s]", (enabled ? "enable" : "disable"), SDL_GetError());
	}

	/**
	 * @brief	Set the title of the window.
	 * @param title	The title of the window.
	 */
	void WindowBasic::SetTitle(const std::string title)
	{
		SDL_SetWindowTitle(window_, title.c_str());
		properties_.title = title;
	}

	/**
	 * @brief	Set the horizontal position of the window.
	 * @param x	The horizontal position of the window.
	 */
	void WindowBasic::SetX(const uint32_t x)
	{
		int y;
		SDL_GetWindowPosition(window_, NULL, &y);
		SetPosition(x, y);
	}

	/**
	 * @brief	Set the vertical position of the window.
	 * @param y	The vertical position of the window.
	 */
	void WindowBasic::SetY(const uint32_t y)
	{
		int x;
		SDL_GetWindowPosition(window_, &x, NULL);
		SetPosition(x, y);
	}

	/**
	 * @brief	Set the position of the window.
	 * 
	 * @param x	The horizontal position of the window.
	 * @param y	The vertical position of the window.
	 */
	void WindowBasic::SetPosition(const uint32_t x, const uint32_t y)
	{
		if(x > INT_MAX || y > INT_MAX)
		{
			log_engine_error("Window position out of bounds! x: [%d], y: [%d]", x, y);
			return;
		}
			
		SDL_SetWindowPosition(window_, (int)x, (int)y);
		properties_.pos_x = x;
		properties_.pos_y = y;
	}

	/**
	 * @brief	Set whether or not the window should be in fullscreen mode.
	 * @param enabled	Whether or not the window should be in fullscreen mode.
	 */
	void WindowBasic::SetFullscreen(const bool enabled)
	{
		SDL_SetWindowFullscreen(window_, enabled ? SDL_WINDOW_FULLSCREEN : 0);
		properties_.fullscreen = enabled;
	}

	/**
	 * @brief	Set whether or not the window should be resizable.
	 * @param enabled	Whether or not the window should be resizable.
	 */
	void WindowBasic::SetResizable(const bool enabled)
	{
		SDL_SetWindowResizable(window_, enabled ? SDL_TRUE : SDL_FALSE);
		properties_.resizable = enabled;
	}

	/**
	 * @brief	Set whether or not the window should be borderless.
	 * @param enabled	Whether or not the window should be borderless.
	 */
	void WindowBasic::SetBorderless(const bool enabled)
	{
		SDL_SetWindowBordered(window_, enabled ? SDL_FALSE : SDL_TRUE);
		properties_.borderless = enabled;
	}

	/**
	 * @brief	Set whether or not the window should be minimized.
	 * @param enabled	Whether or not the window should be minimized.
	 */
	void WindowBasic::SetMinimized(const bool enabled)
	{
		SDL_MinimizeWindow(window_);
		properties_.minimized = enabled;
	}

	/**
	 * @brief	Set whether or not the window should be maximized.
	 * @param enabled	Whether or not the window should be maximized.
	 */
	void WindowBasic::SetMaximized(const bool enabled)
	{
		SDL_MaximizeWindow(window_);
		properties_.maximized = enabled;
	}

	/**
	 * @brief	Set whether or not the window should grab the mouse.
	 * @param enabled	Whether or not the window should grab the mouse.
	 */
	void WindowBasic::SetMouseGrabbed(const bool enabled)
	{
		SDL_SetWindowMouseGrab(window_, enabled ? SDL_TRUE : SDL_FALSE);
		properties_.mouse_grabbed = enabled;
	}

	/// @brief	Request the window to have input focus.
	void WindowBasic::SetInputFocus()
	{
		SDL_SetWindowInputFocus(window_);
		properties_.input_focus = true;
	}

	/**
	 * @brief	Set whether or not the window should be "Always on top".
	 * @param enabled	Whether or not the window should be "Always on top".
	 */
	void WindowBasic::SetAlwaysOnTop(const bool enabled)
	{
		SDL_SetWindowAlwaysOnTop(window_, enabled ? SDL_TRUE : SDL_FALSE);
		properties_.always_on_top = enabled;
	}

	/**
	 * @brief	Set whether or not the window should grab the keyboard.
	 * @param enabled	Whether or not the window should grab the keyboard.
	 */
	void WindowBasic::SetKeyboardGrabbed(const bool enabled)
	{
		SDL_SetWindowKeyboardGrab(window_, enabled ? SDL_TRUE : SDL_FALSE);
		properties_.keyboard_grabbed = enabled;
	}

	/**
	 * @brief	Set whether or not the window should grab input.
	 * @param enabled	Whether or not the window should grab input.
	 */
	void WindowBasic::SetInputGrabbed(const bool enabled)
	{
		SDL_SetWindowGrab(window_, enabled ? SDL_TRUE : SDL_FALSE);
	}

	/**
	 * @brief	Check if vsync is enabled for the window.
	 * 
	 * @return bool	Whether or not vsync is enabled.
	 */
	bool WindowBasic::IsVsyncEnabled() const
	{
		return properties_.vsync;
	}

	/**
	 * @brief Returns a pointer to the native window.
	 * 
	 * @return void*	A pointer to the native window.
	 */
	void* WindowBasic::GetNativeWindow() const
	{
		return window_;
	}

	/// @brief	Initializes the window.
	void WindowBasic::Init()
	{
		open_ = true;

		window_ = SDL_CreateWindow(
			properties_.title.c_str(),
			properties_.pos_x,
			properties_.pos_y,
			properties_.width,
			properties_.height,
			SDL_WINDOW_OPENGL
		);
		if (window_ == nullptr)
			log_engine_error("SDL could not create window! SDL error: [%s]", SDL_GetError());

		context_ = SDL_GL_CreateContext(window_);
		if (context_ == nullptr)
			log_engine_error("SDL could not create OpenGL context! SDL error: [%s]", SDL_GetError());

		SetVsync(properties_.vsync);

		//Get window surface
		SDL_Surface* screenSurface = SDL_GetWindowSurface( window_ );
		
		//Update the surface
		SDL_UpdateWindowSurface( window_ );
		
	}

	/**
	 * @brief	Shuts down the window.
	 * 
	 * 	Destroys the window and deletes the OpenGL context.
	 */
	void WindowBasic::Shutdown()
	{
		open_ = false;
		SDL_GL_DeleteContext(context_);
		SDL_DestroyWindow(window_);
	}
	
} // Namespace trac