/**
 * @file	sandbox.cpp
 * @brief	Source file for the tractor sandbox. See sandbox.h for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	20.07.2023
 * 
*/

// Related header include
#include "sandbox.h"

// Standard library header includes
#include <iostream>

// External libraries header includes
#include <tractor.h>

// Project header includes

/**
 * @brief	The main function for the sandbox application.
 * 
 * @param argc	The number of command line arguments.
 * @param argv	The command line argument vector.
 * @return int	The exit code for the application.
 * 
 * @author	Erlend Elias Isachsen
 */
int main(int argc, char** argv)
{
	std::cout << "In main()" << std::endl;

	// Create the sandbox application
	std::shared_ptr<app::SandboxApp> sandbox_app = std::make_shared<app::SandboxApp>();

	// Run the sandbox application
	trac::run_application(sandbox_app);

	return 0;
}

namespace app
{
	// Defines/macros, enums and variables	


	// Funciton declarations


	// Classes and structs


	// Public functions


	// Implementation

	/**
	 * @brief	Constructs a sandbox application instance.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	SandboxApp::SandboxApp() : 
		trac::Application()
	{
		
	}

	/**
	 * @brief	Destroys the sandbox application instance.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	SandboxApp::~SandboxApp()
	{}

	/**
	 * @brief	The main application function. This will be executed through the tractor game engine library's run_application() function.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	void SandboxApp::run()
	{
		std::shared_ptr<spdlog::logger> logger = trac::Logger::GetClientLogger();
		logger->info("In SandboxApp::run()");
	}

} // Namespace app


/*
 * END OF FILE
 */






