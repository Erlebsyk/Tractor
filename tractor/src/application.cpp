/**
 * @file	application.cpp
 * @brief	
 * 
 * @author	Erlend Elias Isachsen
 * @date	21.07.2023
 * 
*/

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "application.hpp"

// Project includes
#include "logger.hpp"

namespace trac
{
	Application *Application::s_instance = nullptr;
	
	/// @brief Default application constructor. Events are bound at construction.
	Application::Application() : 
		Application("Tractor App", WindowProperties())
	{}

	/**
	 * \brief Constructs an application instance with the given name and window properties. Events are bound at construction.
	 * 
	 * \param name	The name of the application.
	 * \param window_properties	The window properties for the application.
	 */
	Application::Application(const std::string name, const WindowProperties window_properties) :
		running_			{ false													},
		name_				{ name													},
		window_properties_	{ std::make_unique<WindowProperties>(window_properties)	},
		window_				{ nullptr												},
		layer_stack_		{}
	{
		if(s_instance != nullptr)
		{
			log_engine_error("An application instance already exists! Only one application instance can be created.");
			return;
		}
		s_instance = this;

		log_engine_debug("Creating \"{0}\" application: [{1}].", name_, __FUNCTION__);
		BindEventListeners();
	}

	/// @brief Destroys the application instance.
	Application::~Application()
	{
		s_instance = nullptr;
	}

	/**
	 * @brief	Runs the application. This function can be overridden by the application and implemented according to the application's functionality.
	 * 			Alternatively, the derived applications can override RunInit() and RunLoop() functions acoording to needs. These functions should also
	 * 			be used as reference for proper implemantion.
	 * 
	 * @return int	The exit code for the application. 0 is returned if the application exits successfully, and a negative value is returned if the
	 * 				application exits with an error.
	 * @retval 0	The application exited successfully.
	 */
	int Application::Run()
	{
		int status = 0;

		// Initialize the application.
		status = RunInit();

		// Run the application loop if the initialization was successful.
		if(status == 0)
		{
			log_engine_info("Entering the \"{0}\" application main loop.", name_);
			status = RunLoop();
		}
		else
		{
			log_engine_error("Failed to initialize the \"{0}\" application!", name_);
		}
		
		log_engine_info("Application \"{0}\" exited with exit code: {1}.", name_, status);

		Quit();
		return status;
	}

	/// @brief Quits the application. Marks the application as not running.
	void Application::Quit()
	{
		log_client_info("Quitting \"{0}\" application...", name_);
		running_ = false;
	}

	/**
	 * @brief	Returns if the application is running or not.
	 * 
	 * @return bool	True if the application is running, false otherwise.
	 * @retval True	The application is running.
	 * @retval False	The application is not running.
	 */
	bool Application::IsRunning() const
	{
		return running_;
	}

	/**
	 * @brief Get the Name of the application.
	 * 
	 * @return std::string	The name of the application.
	 */
	std::string Application::GetName()
	{
		return name_;
	}

	/**
	 * @brief Push a layer to the layer stack. Layers are pushed to the top of the stack, but below overlays.
	 * 
	 * @param layer	The layer to push to the stack.
	 */
	void Application::PushLayer(std::shared_ptr<Layer> layer)
	{
		layer_stack_.PushLayer(layer);
		layer->OnAttach();
	}

	/**
	 * @brief Pop a layer from the layer stack.
	 * 
	 * @param layer	The layer to pop from the stack.
	 */
	void Application::PopLayer(std::shared_ptr<Layer> layer)
	{
		layer_stack_.PopLayer(layer);
	}

	/**
	 * @brief Push an overlay to the layer stack. Overlays are pushed to the very top of the stack.
	 * 
	 * @param overlay	The overlay to push to the stack.
	 */
	void Application::PushOverlay(std::shared_ptr<Layer> overlay)
	{
		layer_stack_.PushOverlay(overlay);
		overlay->OnAttach();
	}

	/**
	 * @brief Pop an overlay from the layer stack.
	 * 
	 * @param overlay	The overlay to pop from the stack.
	 */
	void Application::PopOverlay(std::shared_ptr<Layer> overlay)
	{
		layer_stack_.PopOverlay(overlay);
	}

	/**
	 * @brief	Processes an event. This function is called by the application when an event is triggered. The event is then passed to all layers in the
	 * 			layer stack in reverse order.
	 * 
	 * @param e	The event to process.
	 */
	void Application::OnEvent(trac::Event& e)
	{
		for(auto it = layer_stack_.end(); it != layer_stack_.begin(); it--)
		{
			(*it)->OnEvent(e);
		}
	}

	/**
	 * \brief Get the static instance of the application.
	 * 
	 * \return Application&	The static instance of the application.
	 */
	Application& Application::Get()
	{
		if(s_instance == nullptr)
			log_engine_error("Application instance is nullptr! Returning nullptr.");

		return *s_instance;
	}

	/**
	 * @brief Get the window of the application.
	 * 
	 * @return Window&	The window of the application.
	 */
	Window& Application::GetWindow()
	{
		return *window_;
	}


	/**
	 * @brief	Main loop that should run while the application is running. This function can be overridden by the application and implemented according
	 * 			to the application's functionality. Note that it should return an exit code and run while "running_" is true.
	 * 
	 * @return int	The exit code for the application. 0 is returned if the application exits successfully, and a negative value is returned if the
	 * 				application exits with an error.
	 * @retval 0	The application exited successfully.
	 */
	int Application::RunLoop()
	{
		int status = 0;

		while(running_)
		{
			// Layer events needs to be processed in order.
			for(auto layer : layer_stack_)
				layer->OnUpdate();

			event_queue_process();
		}

		return status;
	}

	/// @brief Binds event listeners for the application. Can be overridden by derived applications if needed.
	void Application::BindEventListeners()
	{
		log_engine_debug("Binding event listeners.");
		event_listener_add_b(EventType::kQuit, BIND_THIS_EVENT_FN(Application::OnWindowClose));
	}

	/**
	 * @brief	Initializes the application and makes it ready to run. This will open a window and set up the application for the main loop.
	 * 			This function can be overridden by the application and implemented according to the application's functionality.
	 * 
	 * @return int	The status of the initialization. 0 is returned if the initialization was successful, and a negative value is returned if the
	 * 				initialization failed.
	 * @retval 0	The initialization was successful.
	 * @retval -1	A window could not be created.
	 */
	int Application::RunInit()
	{
		int status = 0;
		running_ = true;
		log_engine_info("Running the \"{0}\" application!", name_);

		log_engine_debug("Creating a window...");
		window_ = Window::Create(*window_properties_);
		if(window_ == nullptr)
		{
			log_engine_error("Failed to create window for application: {0}", name_);
			status = -1;
		}

		return status;
	}

	/**
	 * @brief Function to run when the window is closed. This function will quit the application.
	 * 
	 * @param e	The event that triggered the function.
	 */
	void Application::OnWindowClose(Event& e)
	{
		Quit();
	}

} // Namespace trac
