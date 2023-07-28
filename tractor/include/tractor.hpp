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
#include "tractor/events/event.hpp"
#include "tractor/events/event_application.hpp"
#include "tractor/events/event_key.hpp"
#include "tractor/events/event_mouse.hpp"

namespace trac
{
	void run_application(std::shared_ptr<Application> app);
	void initialize_engine();

	bool is_engine_initialized();
	bool is_app_running();
}

#endif // TRACTOR_HPP_