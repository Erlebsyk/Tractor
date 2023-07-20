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
#include <tractor.hpp>

// Project header includes

// Application entry point
int main(int argc, char* argv[])
{
	const int32_t err = app::sandbox_run();
	if (err != SANDBOX_SUCCESS)
		std::cout << "Sandbox exited with error code: " << err << std::endl;

	return 0;
}

namespace app
{
	// Defines/macros, enums and variables	


	// Funciton declarations


	// Classes and structs


	// Implementation
	int32_t sandbox_run()
	{
		std::cout << "We are in sandbox!" << std::endl;
		trac::tractor();
		std::cout << "End of sandbox!" << std::endl;

		return 0;
	}


} // Namespace app


/*
 * END OF FILE
 */






