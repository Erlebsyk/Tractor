/**
 * @file	sandbox.hpp
 * @brief	Main header file for the tractor sandbox. The sandbox can be used to test and play around with the tractor game engine library. The sandbox is not
 * 			part of the core tractor library, though it provides example use cases for how the tractor library can be used.
 * 
 * @author	Erlend Elias Isachsen
 * @date	20.07.2023
 * 
*/

#ifndef SANDBOX_HPP_
#define SANDBOX_HPP_

// Standard library header includes
#include <cstdint>

// External libraries header includes
#include <tractor.h>

// Project header includes


namespace app
{
	// Defines/macros, enums and variables	

	// Funciton declarations

	// Classes and structs

	/**
	 * @brief	The SandboxApp class is the main class for the tractor sandbox. The sandbox can be used to test and play around with the tractor game engine
	 * 			library.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	class SandboxApp : public trac::Application
	{
	public:
		// Constructors and destructors
		SandboxApp();
		~SandboxApp();

		// Public functions
		void run();

	private:
		// Private functions

		// Private variables

	};

	// Implementation


} // Namespace app


#endif // SANDBOX_HPP_ 

/*
 * END OF FILE
 */