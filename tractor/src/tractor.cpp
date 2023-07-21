/**
 * @file	tractor.cpp
 * @brief	Main source file for the tractor game engine library. See tractor.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	20.07.2023
 * 
*/

// Related header include
#include "tractor.h"

// Standard library header includes
#include <cstdint>
#include <iostream>

// External libraries header includes


// Project header includes


namespace trac
{
	// Defines/macros, enums and variables	


	// Funciton declarations


	// Classes and structs


	// Implementation

	/**
	 * @brief	Runs the provided application.
	 * 
	 * 	This function is the main entry point for the tractor game engine library. It will run the provided application, which must be derived from the
	 * 	trac::App class.
	 * 
	 * @param	app		The application to run. Must be derived from the trac::App class.
	 */
	void run_application(std::shared_ptr<App> app)
	{
		// Check that the application is not null
		if (app == nullptr)
		{
			std::cout << "ERROR: The provided application is null." << std::endl;
			return;
		}

		// Do required initialization here

		// Run the application
		app->run();

		// Do required cleanup here

		return;
	}


} // Namespace trac

/*
 * END OF FILE
 */



