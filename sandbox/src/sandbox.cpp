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

/**
 * @brief	The main function for the sandbox application.
 * 
 * @param argc	The number of command line arguments.
 * @param argv	The command line argument vector.
 * @return int	The exit code for the application.
 */
int main(int argc, char** argv)
{
	std::cout << "In main()" << std::endl;

	trac::initialize_engine();
	std::shared_ptr<app::SandboxApp> sandbox_app = std::make_shared<app::SandboxApp>();
	trac::run_application(sandbox_app);

	return 0;
}

namespace app
{
	
	/// @brief	Constructs a sandbox application instance.
	SandboxApp::SandboxApp() : 
		trac::Application()
	{
		trac::log_client_trace("Creating sandbox application: [Var={0}].", __FUNCTION__);
	}

	
	/// @brief	The main application function. This will be executed through the tractor game engine library's run_application() function.
	void SandboxApp::run()
	{
		trac::log_client_info("Hello from the sandbox application!");
	}

} // Namespace app