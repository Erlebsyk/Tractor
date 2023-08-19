/**
 * @file	tractor.cpp
 * @brief	Main source file for the tractor game engine library. See tractor.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	20.07.2023
 * 
*/

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "tractor.hpp"

// Standard library header includes
#include <exception>

// Project header includes
#include "logger.hpp"
#include "sdl_hook.hpp"
#include "events/event.hpp"

namespace trac
{
	/// Flag indicating if the tractor library is initialized.
	static bool engine_initialized = false;

	/// @brief	Initializes the tractor game engine library. This function is called automatically when the first application is run.
	void initialize_engine()
	{
		// Check if the tractor library is already initialized
		if (is_engine_initialized())
			return;
		
		engine_initialized = true;
		Logger::Initialize();
		EventDispatcher::Initialize();
		sdl_link_events();
	}

	/**
	 * @brief	Check whether the tractor game engine library is initialized.
	 * 
	 * @return bool	Whether or not the tractor game engine library is initialized.
	 * @retval true	The tractor game engine library is initialized.
	 * @retval false	The tractor game engine library is not initialized.
	 * 
	 */
	bool is_engine_initialized()
	{
		return engine_initialized;
	}
} // Namespace trac


