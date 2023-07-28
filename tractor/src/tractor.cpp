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
#include "logger.hpp"

// Standard library header includes
#include <exception>

// Project header includes
#include "events/event.hpp"

namespace trac
{
	/// Flag indicating if the tractor library is initialized.
	static bool engine_initialized = false;
	/// Flag indicating if an application is running.
	static bool app_running = false;

	/// @brief	Initializes the tractor game engine library. This function is called automatically when the first application is run.
	void initialize_engine()
	{
		// Check if the tractor library is already initialized
		if (engine_initialized)
			return;
		
		engine_initialized = true;
		Logger::Initialize();
		EventDispatcher::Initialize();
	}

	/**
	 * @brief	Runs the provided application. Before running the application, the tractor library will be initialized using the initialize_engine() function.
	 * 
	 * 	This function is the main entry point for the tractor game engine library. It will run the provided application, which must be derived from the
	 * 	trac::Application class.
	 * 
	 * @param	app		The application to run. Must be derived from the trac::Application class.
	 */
	void run_application(std::shared_ptr<Application> app)
	{
		// Ensure that the tractor library is initialized
		if(!engine_initialized)
			throw(std::exception("The tractor library has not been initialized. Call the initialize_engine() function before running an application."));

		// Check that the application is not null
		if (app == nullptr)
		{
			std::cout << "ERROR: The provided application is null." << std::endl;
			return;
		}

		// Run the application
		app_running = true;
		app->run();

		// Do required cleanup
		app_running = false;

		return;
	}

	/**
	 * @brief	Check if the tractor game engine library is initialized.
	 * 
	 * @return bool	True if the tractor library is initialized, false otherwise.
	 * @retval true	The tractor library is initialized.
	 * @retval false	The tractor library is not initialized.
	 */
	bool is_engine_initialized()
	{
		return engine_initialized;
	}

	/**
	 * @brief	Check if an application is currently running.
	 * 
	 * @return bool	True if an application is running, false otherwise.
	 * @retval true	An application is running.
	 * @retval false	No application is running.
	 */
	bool is_app_running()
	{
		return app_running;
	}
} // Namespace trac


