/**
 * @file	sandbox.h
 * @brief	Main header file for the tractor sandbox. The sandbox can be used to test and play around with the tractor game engine library. The sandbox is not
 * 			part of the core tractor library, though it provides example use cases for how the tractor library can be used.
 * 
 * @author	Erlend Elias Isachsen
 * @date	20.07.2023
 * 
*/

#ifndef SANDBOX_H_
#define SANDBOX_H_

// External libraries header includes
#include <tractor.h>

namespace app
{
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

		// Public functions
		void run();
	};
} // Namespace app

#endif // SANDBOX_H_