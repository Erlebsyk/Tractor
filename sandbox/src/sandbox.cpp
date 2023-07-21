/**
 * @file	sandbox.cpp
 * @brief	Source file for the tractor sandbox. See sandbox.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	20.07.2023
 * 
*/

// Related header include
#include "sandbox.hpp"

// Standard library header includes
#include <iostream>

// External libraries header includes
#include <tractor.h>

// Project header includes

int main(int argc, char** argv)
{
	std::cout << "Starting sandbox application." << std::endl;

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
		trac::App()
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
		std::cout << "Running the sandbox application!" << std::endl;
	}

} // Namespace app


/*
 * END OF FILE
 */






