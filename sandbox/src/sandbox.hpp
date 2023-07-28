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

// External libraries header includes
#include <tractor.hpp>

namespace app
{
	/// @brief	The SandboxApp class is the main class for the tractor sandbox. The sandbox can be used to test and play around with the tractor library.
	class SandboxApp : public trac::Application
	{
	public:
		// Constructors and destructors

		SandboxApp();

		// Public functions
		
		void run();
	};
} // Namespace app

#endif // SANDBOX_HPP_