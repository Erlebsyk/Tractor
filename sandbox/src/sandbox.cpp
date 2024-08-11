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
		trac::log_client_info("Creating sandbox application: [{0}].", __FUNCTION__);

		trac::log_client_debug("Adding window event listeners");
		trac::listener_id_t quit_id = trac::event_listener_add_b(trac::EventType::kQuit, BIND_EVENT_FN(SandboxApp::OnWindowClose));
	}

	/// @brief	The main application function. This will be executed through the tractor game engine library's main function in "entry_point.hpp".
	int SandboxApp::Run()
	{
		running_ = true;

		trac::log_client_info("Hello from the sandbox application!");

		trac::log_client_debug("Creating a window...");
		trac::WindowProperties window_properties("Sandbox", 1280, 720);
		std::unique_ptr<trac::Window> window = trac::Window::Create(window_properties);

		while(running_)
		{
			trac::event_queue_process();
		}

		return 0;
	}

	/// @brief	Quits the sandbox application.
	void SandboxApp::Quit()
	{
		trac::log_client_info("Quitting sandbox application...");
		running_ = false;
	}

	/**
	 * @brief 	Handles the event when the window is closed.
	 * 
	 * @param e	The event that was triggered.
	 */
	void SandboxApp::OnWindowClose(trac::Event& e)
	{
		Quit();
	}
} // Namespace app