/**
 * @file	logger.h
 * @brief	Logger module for the tractor game engine library. The logger builds upon the spdlog library, and provides one logger for the engine, and one for
 * 			the client.
 * 	
 *	The logger module creates two standard loggers with predefined formats that gives useful debug metadata, as well as clean and readable output. The module
 *	works as a specialication of the spdlog library for application and engine logging. It also works as an interface between the application and the underlying
 *	logging library, such that the application is not hard-dependent on any particular logging library, such that the code on the application side can be kept
 * 	constant, even if the underlying logging library of the engine is interchanged.
 * 
 * @author	Erlend Elias Isachsen
 * @date	23.07.2023
 * 
*/

#ifndef LOGGER_H_
#define LOGGER_H_

// Standard library header includes
#include <cstdint>
#include <memory>

// External libraries header includes
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// Project header includes


namespace trac
{
	// Defines/macros, enums and variables	
	static const char kEngineName[] = "ENGINE";
	static const char kClientName[] = "CLIENT";

	// Funciton declarations


	// Classes and structs

	/**
	 * @brief	Logging class for simplifying logging in the tractor game engine library, both for the engine and the client.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	class Logger
	{
	public:
		// Constructors and destructors
		Logger();
		~Logger();
	
		//Public functions
		static void Initialize();

		//Public variables

		/**
		 * @brief	Get the global engine logger instance.
		 * 
		 * @return std::shared_ptr<spdlog::logger>&	A reference pointer to the global engine logger instance.
		 * 
		 * @author	Erlend Elias Isachsen
		 */
		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return engine_logger_s_; }

		/**
		 * @brief	Get the global client Logger object
		 * 
		 * @return std::shared_ptr<spdlog::logger>& A reference pointer to the global client logger instance.
		 * 
		 * @author	Erlend Elias Isachsen
		 */
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return client_logger_s_; }
	
	private:
		//Private functions
	
		//Private variables
		static std::shared_ptr<spdlog::logger> engine_logger_s_;
		static std::shared_ptr<spdlog::logger> client_logger_s_;
	};

	// Implementation


} // Namespace trac


#endif // LOGGER_H_ 

/*
 * END OF FILE
 */