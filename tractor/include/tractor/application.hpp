/**
 * @file	application.hpp
 * @brief	The tractor application creates a structure for creating applications that use the tractor game engine library.
 * 
 * @author	Erlend Elias Isachsen
 * @date	21.07.2023
 * 
*/

#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

namespace trac
{
	/**
	 * @brief	The base application class that all applications that use the tractor game engine library must inherit from.
	 * 
	 * 	This app class defines the structure for all apps that use the tractor game engine library. The app class is an abstract class, and must be
	 * 	overridden by the application by creating a derived application class. The derived application class must implement the run() function, which
	 * 	is the entry point for the application. The run() function is called by calling the run_application() function declared in tractor.hpp.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	class Application
	{
	public:
		// Constructors and destructors

		/// @brief Default constructor.
		Application() = default;
		/// @brief Virtual default destructor.
		virtual ~Application() = default;

		/// @brief Explicitly defined default copy constructor.
		Application(const Application& other) = default;
		/// @brief Explicitly defined default move constructor.
		Application(Application&& other) = default;
		/// @brief Explicitly defined default copy assignment operator.
		Application& operator=(const Application& other) = default;
		/// @brief Explicitly defined default move assignment operator.
		Application& operator=(Application&& other) = default;

		// Public functions

		/**
		 * @brief	The run() function is the entry point for the application. This function must be overridden by the application and implemented according
		 * 			to the application's functionality.
		 */
		virtual void run() = 0;
	};
} // Namespace trac

#endif // APPLICATION_HPP_ 