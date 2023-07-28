/**
 * @file	logger.hpp
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

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

// Standard library header includes
#include <cstdint>
#include <memory>

// External libraries header includes
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace trac
{
	/// @brief	The log level enum defines the different log levels that can be used in the tractor game engine library.
	enum class LogLevel
	{
		kTrace		= spdlog::level::trace,
		kDebug		= spdlog::level::debug,
		kInfo		= spdlog::level::info,
		kWarn		= spdlog::level::warn,
		kError		= spdlog::level::err,
		kCritical	= spdlog::level::critical,
		kOff		= spdlog::level::off,
		n_levels	= 6 
	};

	// Declare interface for logging through the engine.

	template<typename... Args>
	inline void log_engine_log(spdlog::level::level_enum lvl, spdlog::format_string_t<Args...> fmt, Args &&...args);
	template<typename... Args>
	inline void log_engine_trace(spdlog::format_string_t<Args...> fmt, Args &&...args);
	template<typename... Args>
	inline void log_engine_debug(spdlog::format_string_t<Args...> fmt, Args &&...args);
	template<typename... Args>
	inline void log_engine_info(spdlog::format_string_t<Args...> fmt, Args &&...args);
	template<typename... Args>
	inline void log_engine_warn(spdlog::format_string_t<Args...> fmt, Args &&...args);
	template<typename... Args>
	inline void log_engine_error(spdlog::format_string_t<Args...> fmt, Args &&...args);
	template<typename... Args>
	inline void log_engine_critical(spdlog::format_string_t<Args...> fmt, Args &&...args);
	
	template<typename... Args>
	inline void log_client_log(spdlog::level::level_enum lvl, spdlog::format_string_t<Args...> fmt, Args &&...args);
	template<typename... Args>
	inline void log_client_trace(spdlog::format_string_t<Args...> fmt, Args &&...args);
	template<typename... Args>
	inline void log_client_debug(spdlog::format_string_t<Args...> fmt, Args &&...args);
	template<typename... Args>
	inline void log_client_info(spdlog::format_string_t<Args...> fmt, Args &&...args);
	template<typename... Args>
	inline void log_client_warn(spdlog::format_string_t<Args...> fmt, Args &&...args);
	template<typename... Args>
	inline void log_client_error(spdlog::format_string_t<Args...> fmt, Args &&...args);
	template<typename... Args>
	inline void log_client_critical(spdlog::format_string_t<Args...> fmt, Args &&...args);

	// Functions for modifying the loggers.

	LogLevel log_engine_get_level();
	void log_engine_set_level(LogLevel lvl);
	LogLevel log_client_get_level();
	void log_client_set_level(LogLevel lvl);

	/// @brief	Logging class for simplifying logging in the tractor game engine library, both for the engine and the client.
	class Logger
	{
	public:
		static void Initialize();

		static std::shared_ptr<spdlog::logger>& GetEngineLogger();
		static std::shared_ptr<spdlog::logger>& GetClientLogger();

	private:
		static std::shared_ptr<spdlog::logger> engine_logger_s_;
		static std::shared_ptr<spdlog::logger> client_logger_s_;
	};
} // Namespace trac

#endif // LOGGER_HPP_ 

// Include the inline implementations of the logger module.
#include "logger.inl"