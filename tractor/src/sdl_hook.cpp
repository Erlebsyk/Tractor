/**
 * @file	sdl_hook.cpp
 * @brief	Sources file for the SDL hook. See sdl_hook.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	16.08.2023
 * 
*/

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "sdl_hook.hpp"

// Project header includes
#include "sdl_hook_events.hpp"

namespace trac
{	
	

	/// @brief	Initializes the sdl library.
	void sdl_init()
	{
		sdl_init_events();
	}

} // Namespace trac