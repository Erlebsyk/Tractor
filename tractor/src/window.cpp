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
#include "events/event.hpp"
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
	 */
	WindowProperties::WindowProperties(
		const std::string& title,
		const uint32_t width,
		const uint32_t height,
		const uint32_t pos_x,
		const uint32_t pos_y,
		const bool vsync
	) : 
		title	{ title 	},
		width	{ width 	},
		height	{ height	},
		pos_x	{ pos_x		},
		pos_y	{ pos_y		},
		vsync	{ vsync		}
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
	 * @brief	Creates a new window. This definition determines which window type to use, and can be changed to use a different window type by defining
	 * 			preprocessor macros for selecting window type.
	 * 
	 * @param properties	The properties of the window.
	 * @return std::unique_ptr<Window>	A unique pointer to the window.
	 */
	std::shared_ptr<Window> Window::Create(const WindowProperties& properties)
	{
		return std::make_shared<WindowBasic>(properties);
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
		context_		{ nullptr			}
	{
		Init();
		windows_n_++;
	}

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
	 * @brief	Check if vsync is enabled for the window.
	 * 
	 * @return bool	Whether or not vsync is enabled.
	 */
	bool WindowBasic::IsVsyncEnabled() const
	{
		return properties_.vsync;
	}


	void* WindowBasic::GetNativeWindow() const
	{
		return window_;
	}

	void WindowBasic::Init()
	{
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
		SDL_GL_DeleteContext(context_);
		SDL_DestroyWindow(window_);
	}
} // Namespace trac