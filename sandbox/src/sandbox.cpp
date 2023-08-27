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
	
	
	bool SandboxApp::quit_ = false;

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

		trac::listener_id_t quit_id = trac::event_listener_add_b(trac::EventType::kQuit, quit);

		while(!quit_)
		{
			trac::event_queue_process();
		}

		return 0;
	}

	/**
	 * @brief	Mark the application for quitting.
	 * 
	 * @param e	The event that triggered the quit.
	 */
	void SandboxApp::quit(trac::Event& e)
	{
		trac::log_client_info("Application quit requested....");
		quit_ = true;
	}

} // Namespace app