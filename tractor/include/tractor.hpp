/**
 * @file	tractor.hpp
 * @brief	Main header file for the tractor game engine library.
 * 
 * @author	Erlend Elias Isachsen
 * @date	20.07.2023
 * 
*/

#ifndef TRACTOR_HPP_
#define TRACTOR_HPP_

// Standard library header includes
#include <cstdint>
#include <memory>


// Project header includes
#include "tractor/application.hpp"
#include "tractor/logger.hpp"
#include "tractor/window.hpp"

#include "tractor/events.hpp"

namespace trac
{
	void initialize_engine();
	bool is_engine_initialized();
}

#endif // TRACTOR_HPP_