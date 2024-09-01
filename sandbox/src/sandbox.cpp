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
#include <tractor.hpp>

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
		trac::Application("Sandbox", trac::WindowProperties())
	{}

	/// @brief	Sets up the sandbox application.
	int SandboxApp::RunInit()
	{
		Application::RunInit();
		std::shared_ptr<trac::Layer> gui_layer = std::make_shared<trac::GuiLayer>();
		PushOverlay(gui_layer);

		return 0;
	}
} // Namespace app