/**
 * @file	logger.cpp
 * @brief	Source file for the logging module. See logger.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	23.07.2023
 * 
 * @todo	Create tests.
*/

// Related header include
#include "logger.hpp"

// Standard library header includes
#include <cstdint>
#include <string>

// External libraries header includes


// Project header includes


namespace trac
{
	// Defines/macros, enums and variables

	/// The format string for the engine logger.
	static const char kEngineFormat[] = "[%T:%e] [%n] [%^%l%$] %v";
	/// The format string for the client logger.
	static const char kClientFormat[] = "[%T:%e] [%n] [%^%l%$] %v";
	/// The log level for the engine logger.
	#define ENGINE_LOG_LEVEL spdlog::level::debug
	/// The log level for the client logger.
	#define CLIENT_LOG_LEVEL spdlog::level::debug

	/// The global engine logger instance.
	std::shared_ptr<spdlog::logger> Logger::engine_logger_s = nullptr;
	/// The global client logger instance.
	std::shared_ptr<spdlog::logger> Logger::client_logger_s = nullptr;

	// Funciton declarations


	// Classes and structs


	// Implementation
	/**
	 * @brief	Construct a Logger object.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	Logger::Logger()
	{
		
	}
	
	/**
	 * @brief	Destroy the Logger object.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	Logger::~Logger()
	{}
	
	/**
	 * @brief	Initializes the default loggers, one for the engine and one for the client.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	void Logger::Initialize()
	{
		if(engine_logger_s == nullptr)
		{
			engine_logger_s = spdlog::stdout_color_mt(kEngineName);
			engine_logger_s->set_pattern(kEngineFormat, spdlog::pattern_time_type::local);
			engine_logger_s->set_level(ENGINE_LOG_LEVEL);
			engine_logger_s->debug("Engine logger initialized.");
		}

		if(client_logger_s == nullptr)
		{
			client_logger_s = spdlog::stdout_color_mt(kClientName);
			engine_logger_s->set_pattern(kClientFormat, spdlog::pattern_time_type::local);
			engine_logger_s->set_level(CLIENT_LOG_LEVEL);
			engine_logger_s->debug("Client logger initialized.");
		}
	}

} // Namespace trac

/*
 * END OF FILE
 */