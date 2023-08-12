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

// External libraries header includes
#include <tractor/entry_point.hpp>

/**
 * @brief	Creates a sandbox application instance. This function is called automatically by the tractor game engine library's main() function.
 * 
 * @return std::shared_ptr<trac::Application>	A shared pointer to the sandbox application instance.
 */
std::shared_ptr<trac::Application> trac::create_application()
{
	return std::make_shared<app::SandboxApp>();
}


namespace app
{
	
	/// @brief	Constructs a sandbox application instance.
	SandboxApp::SandboxApp() : 
		trac::Application()
	{
		trac::log_client_trace("Creating sandbox application: [Var={0}].", __FUNCTION__);
	}

	
	/// @brief	The main application function. This will be executed through the tractor game engine library's main function in "entry_point.hpp".
	int SandboxApp::run()
	{
		trac::log_client_info("Hello from the sandbox application!");

		trac::log_client_debug("Creating a window...");
		trac::WindowProperties window_properties("Sandbox", 1280, 720);
		std::shared_ptr<trac::Window> window = trac::Window::Create(window_properties);

		bool quit = false;
		SDL_Event e;
		while( quit == false )
		{
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
			}
		}

		return 0;
	}

} // Namespace app