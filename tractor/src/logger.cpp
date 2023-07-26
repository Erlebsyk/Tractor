/**
 * @file	logger.cpp
 * @brief	Source file for the logging module. See logger.hpp for more information.
 * 
 * @author	Erlend Elias Isachsen
 * @date	23.07.2023
 * 
*/

// Precompiled header include
#include "tractor_pch.hpp"

// Related header include
#include "logger.hpp"

namespace trac
{
	/// The name of the engine logger.
	static const char kEngineName[] = "ENGINE";
	/// The name of the client logger.
	static const char kClientName[] = "CLIENT";
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

	/**
	 * @brief	Get the current log level of the engine logger.
	 * 
	 * @return LogLevel	The current log level of the engine logger.
	 */
	LogLevel log_engine_get_level()
	{
		return (LogLevel)(Logger::GetEngineLogger()->level());
	}

	/**
	 * @brief	Set the log level of the engine logger.
	 * 
	 * @param lvl	The log level to set.
	 */
	void log_engine_set_level(const LogLevel lvl)
	{
		Logger::GetEngineLogger()->set_level((spdlog::level::level_enum)(lvl));
	}

	/**
	 * @brief	Get the current log level of the client logger.
	 * 
	 * @return LogLevel	The current log level of the client logger.
	 */
	LogLevel log_client_get_level()
	{
		return (LogLevel)(Logger::GetClientLogger()->level());
	}

	/**
	 * @brief	Set the log level of the client logger.
	 * 
	 * @param lvl	The log level to set.
	 */
	void log_client_set_level(const LogLevel lvl)
	{
		Logger::GetClientLogger()->set_level((spdlog::level::level_enum)(lvl));
	}
	
	
	/// @brief	Initializes the default loggers, one for the engine and one for the client.
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

	/**
	 * @brief	Get the global engine logger instance.
	 * 
	 * @return std::shared_ptr<spdlog::logger>&	A reference pointer to the global engine logger instance.
	 */
	std::shared_ptr<spdlog::logger>& Logger::GetEngineLogger()
	{
		return engine_logger_s_;
	}

	/**
	 * @brief	Get the global client Logger object
	 * 
	 * @return std::shared_ptr<spdlog::logger>& A reference pointer to the global client logger instance.
	 */
	std::shared_ptr<spdlog::logger>& Logger::GetClientLogger()
	{
		return client_logger_s_;
	}
} // Namespace trac