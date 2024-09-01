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

#include <string>
#include <memory>

#include "window.hpp"
#include "layer_stack.hpp"
#include "events.hpp"

namespace trac
{
	/**
	 * @brief	The base application class that all applications that use the tractor game engine library must inherit from.
	 * 
	 * 	This app class defines the structure for all apps that use the tractor game engine library. The app class is an abstract class, and must be
	 * 	overridden by the application by creating a derived application class. The derived application class must implement the Run() function, which
	 * 	is the entry point for the application. The Run() function is called by calling the run_application() function declared in tractor.hpp.
	 */
	class Application
	{
	public:
		// Constructors and destructors

		Application();
		Application(
			std::string name,
			WindowProperties window_properties = WindowProperties()
		);
		virtual ~Application();

		// Public functions
		virtual int Run();
		virtual void Quit();

		bool IsRunning() const;
		std::string GetName();

		void PushLayer(std::shared_ptr<Layer> layer);
		void PopLayer(std::shared_ptr<Layer> layer);
		void PushOverlay(std::shared_ptr<Layer> overlay);
		void PopOverlay(std::shared_ptr<Layer> overlay);

		void OnEvent(trac::Event& e);

		Window& GetWindow();

		static Application& Get();

	protected:
		virtual void BindEventListeners();
		virtual int RunInit();
		virtual int RunLoop();
		virtual void OnWindowClose(trac::Event& e);

		/// Marks if the application is running or not
		bool running_ = false;
		/// The name of the application
		std::string name_;
		/// The window properties for the application
		std::unique_ptr<WindowProperties> window_properties_;
		/// The Application window
		std::unique_ptr<trac::Window> window_;
		/// The application layer stack
		LayerStack layer_stack_;

		/// Static application instance
		static Application *s_instance;
	};
} // Namespace trac

#endif // APPLICATION_HPP_ 