/**
 * @file	logger.cpp
 * @brief	Source file for the logging module. See logger.h for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	23.07.2023
 * 
*/

// Related header include
#include "logger.h"

// Standard library header includes
#include <cstdint>
#include <string>

// External libraries header includes


// Project header includes


namespace trac
{
	// Defines/macros, enums and variables

	/// The format string for the engine logger.
	static const char kEngineFormat[] = "[%T:%e] [%n] [%^%L%$] %v";
	/// The format string for the client logger.
	static const char kClientFormat[] = "[%T:%e] [%n] [%^%L%$] %v";
	/// The log level for the engine logger.
	#define ENGINE_LOG_LEVEL spdlog::level::debug
	/// The log level for the client logger.
	#define CLIENT_LOG_LEVEL spdlog::level::debug

	/// The global engine logger instance.
	std::shared_ptr<spdlog::logger> Logger::engine_logger_s_ = nullptr;
	/// The global client logger instance.
	std::shared_ptr<spdlog::logger> Logger::client_logger_s_ = nullptr;

	// Funciton declarations


	// Classes and structs


	// Implementation

	/**
	 * @brief	Get the current log level of the engine logger.
	 * 
	 * @return LogLevel	The current log level of the engine logger.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	LogLevel log_engine_get_level()
	{
		return (LogLevel)(Logger::GetEngineLogger()->level());
	}

	/**
	 * @brief	Set the log level of the engine logger.
	 * 
	 * @param lvl	The log level to set.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	void log_engine_set_level(const LogLevel lvl)
	{
		Logger::GetEngineLogger()->set_level((spdlog::level::level_enum)(lvl));
	}

	/**
	 * @brief	Get the current log level of the client logger.
	 * 
	 * @return LogLevel	The current log level of the client logger.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	LogLevel log_client_get_level()
	{
		return (LogLevel)(Logger::GetClientLogger()->level());
	}

	/**
	 * @brief	Set the log level of the client logger.
	 * 
	 * @param lvl	The log level to set.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	void log_client_set_level(const LogLevel lvl)
	{
		Logger::GetClientLogger()->set_level((spdlog::level::level_enum)(lvl));
	}

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
		if(engine_logger_s_ == nullptr)
		{
			engine_logger_s_ = spdlog::stdout_color_mt(kEngineName);
			engine_logger_s_->set_pattern(kEngineFormat);
			engine_logger_s_->set_level(ENGINE_LOG_LEVEL);
			engine_logger_s_->debug("Engine logger initialized.");
		}

		if(client_logger_s_ == nullptr)
		{
			client_logger_s_ = spdlog::stdout_color_mt(kClientName);
			client_logger_s_->set_pattern(kClientFormat);
			client_logger_s_->set_level(CLIENT_LOG_LEVEL);
			client_logger_s_->debug("Client logger initialized.");
		}
	}

} // Namespace trac

/*
 * END OF FILE
 */