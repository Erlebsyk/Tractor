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

	/**
	 * @brief	The log level enum defines the different log levels that can be used in the tractor game engine library.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
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

	// Funciton declarations

	// Define interface for logging through the engine.
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


		//Public variables

	
	private:
		//Private functions
	
		//Private variables
		static std::shared_ptr<spdlog::logger> engine_logger_s_;
		static std::shared_ptr<spdlog::logger> client_logger_s_;
	};

	// Implementation

	/**
	 * @brief	Print a log message with the engine logger.
	 * 
	 * @tparam Args	The argument types used in the format string.
	 * @param lvl	The log level of the message to print.
	 * @param fmt	The format string.
	 * @param args	The arguments used in the format string.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	template<typename... Args>
	inline void log_engine_log(spdlog::level::level_enum lvl, spdlog::format_string_t<Args...> fmt, Args &&...args)
	{
		Logger::GetEngineLogger()->log(lvl, fmt, std::forward<Args>(args)...);
	}
	
	/**
	 * @brief	Print a trace message with the engine logger.
	 * 
	 * @tparam Args	The argument types used in the format string.
	 * @param fmt	The format string.
	 * @param args	The arguments used in the format string.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	template<typename... Args>
	inline void log_engine_trace(spdlog::format_string_t<Args...> fmt, Args &&...args)
	{
		Logger::GetEngineLogger()->trace(fmt, std::forward<Args>(args)...);
	}

	/**
	 * @brief	Print a debug message with the engine logger.
	 * 
	 * @tparam Args	The argument types used in the format string.
	 * @param fmt	The format string.
	 * @param args	The arguments used in the format string.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	template<typename... Args>
	inline void log_engine_debug(spdlog::format_string_t<Args...> fmt, Args &&...args)
	{
		Logger::GetEngineLogger()->debug(fmt, std::forward<Args>(args)...);
	}

	/**
	 * @brief	Print an info message with the engine logger.
	 * 
	 * @tparam Args	The argument types used in the format string.
	 * @param fmt	The format string.
	 * @param args	The arguments used in the format string.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	template<typename... Args>
	inline void log_engine_info(spdlog::format_string_t<Args...> fmt, Args &&...args)
	{
		Logger::GetEngineLogger()->info(fmt, std::forward<Args>(args)...);
	}

	/**
	 * @brief	Print a warning message with the engine logger.
	 * 
	 * @tparam Args	The argument types used in the format string.
	 * @param fmt	The format string.
	 * @param args	The arguments used in the format string.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	template<typename... Args>
	inline void log_engine_warn(spdlog::format_string_t<Args...> fmt, Args &&...args)
	{
		Logger::GetEngineLogger()->warn(fmt, std::forward<Args>(args)...);
	}

	/**
	 * @brief	Print an error message with the engine logger.
	 * 
	 * @tparam Args	The argument types used in the format string.
	 * @param fmt	The format string.
	 * @param args	The arguments used in the format string.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	template<typename... Args>
	inline void log_engine_error(spdlog::format_string_t<Args...> fmt, Args &&...args)
	{
		Logger::GetEngineLogger()->error(fmt, std::forward<Args>(args)...);
	}

	/**
	 * @brief	Print a log message with the client logger.
	 * 
	 * @tparam Args	The argument types used in the format string.
	 * @param lvl	The log level of the message to print.
	 * @param fmt	The format string.
	 * @param args	The arguments used in the format string.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	template<typename... Args>
	inline void log_client_log(spdlog::level::level_enum lvl, spdlog::format_string_t<Args...> fmt, Args &&...args)
	{
		Logger::GetClientLogger()->log(lvl, fmt, std::forward<Args>(args)...);
	}

	/**
	 * @brief	Print a critical message with the engine logger.
	 *
	 * @tparam Args	The argument types used in the format string.
	 * @param fmt	The format string.
	 * @param args	The arguments used in the format string.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	template<typename... Args>
	inline void log_engine_critical(spdlog::format_string_t<Args...> fmt, Args &&...args)
	{
		Logger::GetEngineLogger()->critical(fmt, std::forward<Args>(args)...);
	}

	/**
	 * @brief	Print a trace message with the client logger.
	 * 
	 * @tparam Args	The argument types used in the format string.
	 * @param fmt	The format string.
	 * @param args	The arguments used in the format string.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	template<typename... Args>
	inline void log_client_trace(spdlog::format_string_t<Args...> fmt, Args &&...args)
	{
		Logger::GetClientLogger()->trace(fmt, std::forward<Args>(args)...);
	}

	/**
	 * @brief	Print a debug message with the client logger.
	 * 
	 * @tparam Args	The argument types used in the format string.
	 * @param fmt	The format string.
	 * @param args	The arguments used in the format string.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	template<typename... Args>
	inline void log_client_debug(spdlog::format_string_t<Args...> fmt, Args &&...args)
	{
		Logger::GetClientLogger()->debug(fmt, std::forward<Args>(args)...);
	}

	/**
	 * @brief	Print an info message with the client logger.
	 * 
	 * @tparam Args	The argument types used in the format string.
	 * @param fmt	The format string.
	 * @param args	The arguments used in the format string.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	template<typename... Args>
	inline void log_client_info(spdlog::format_string_t<Args...> fmt, Args &&...args)
	{
		Logger::GetClientLogger()->info(fmt, std::forward<Args>(args)...);
	}

	/**
	 * @brief	Print a warning message with the client logger.
	 * 
	 * @tparam Args	The argument types used in the format string.
	 * @param fmt	The format string.
	 * @param args	The arguments used in the format string.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	template<typename... Args>
	inline void log_client_warn(spdlog::format_string_t<Args...> fmt, Args &&...args)
	{
		Logger::GetClientLogger()->warn(fmt, std::forward<Args>(args)...);
	}

	/**
	 * @brief	Print an error message with the client logger.
	 * 
	 * @tparam Args	The argument types used in the format string.
	 * @param fmt	The format string.
	 * @param args	The arguments used in the format string.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	template<typename... Args>
	inline void log_client_error(spdlog::format_string_t<Args...> fmt, Args &&...args)
	{
		Logger::GetClientLogger()->error(fmt, std::forward<Args>(args)...);
	}

	/**
	 * @brief	Print a critical message with the client logger.
	 * 
	 * @tparam Args	The argument types used in the format string.
	 * @param fmt	The format string.
	 * @param args	The arguments used in the format string.
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	template<typename... Args>
	inline void log_client_critical(spdlog::format_string_t<Args...> fmt, Args &&...args)
	{
		Logger::GetClientLogger()->critical(fmt, std::forward<Args>(args)...);
	}

} // Namespace trac


#endif // LOGGER_H_ 

/*
 * END OF FILE
 */