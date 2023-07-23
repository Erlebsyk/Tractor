/**
 * @file	application.h
 * @brief	The tractor application creates a structure for creating applications that use the tractor game engine library.
 * 
 * @author	Erlend Elias Isachsen
 * @date	21.07.2023
 * 
*/

#ifndef APPLICATION_H_
#define APPLICATION_H_

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
	class Application
	{
	public:
		// Constructors and destructors
		Application();
		~Application();

		// Public functions

		/**
		 * @brief	The run() function is the entry point for the application. This function must be overridden by the application and implemented according
		 * 			to the application's functionality.
		 * 
		 * @author	Erlend Elias Isachsen
		 */
		virtual void run() = 0;

	private:
		// Private functions

		// Private variables


	};

	// Implementation


} // Namespace trac


#endif // APPLICATION_H_ 

/*
 * END OF FILE
 */