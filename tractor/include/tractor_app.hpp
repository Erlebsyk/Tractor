/**
 * @file	tractor_app.hpp
 * @brief	The tractor app creates a structure for craeting applications that use the tractor game engine library.
 * 
 * @author	Erlend Elias Isachsen
 * @date	21.07.2023
 * 
*/

#ifndef TRACTOR_APP_HPP_
#define TRACTOR_APP_HPP_

// Standard library header includes
#include <cstdint>

// External libraries header includes


// Project header includes


namespace trac
{
	// Defines/macros, enums and variables	


	// Funciton declarations


	// Classes and structs

	/**
	 * @brief	The base application class that all applications that use the tractor game engine library must inherit from.
	 * 
	 * 	This app class defines the structure for all apps that use the tractor game engine library. The app class is an abstract class, and must be
	 * 	overridden by the application by creating a derived application class. The derived application class must implement the run() function, which
	 * 	is the entry point for the application. The run() function is called by calling the run_application() function declared in tractor.h.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	class App
	{
	public:
		// Constructors and destructors
		App();
		~App();

		// Public functions
		virtual void run() = 0;

	private:
		// Private functions

		// Private variables
	};

	// Implementation


} // Namespace trac


#endif // TRACTOR_APP_HPP_ 

/*
 * END OF FILE
 */