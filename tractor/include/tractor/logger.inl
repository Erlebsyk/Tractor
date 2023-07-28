/**
 * @file	logger.inl
 * @brief	Inline implementation file for the logger class. This file should only be included by the logger.hpp file.
 * 
 * @author	Erlend Elias Isachsen
 * @date	26.07.2023
 * 
*/

#ifndef LOGGER_INL_
#define LOGGER_INL_

// Ensure that this file is only directly included from the logger.hpp file. Other files should include the logger.hpp file instead.
#ifndef LOGGER_HPP_
#error "Do not include this file directly. Include logger.hpp instead, through which this file is included indirectly."
#endif // LOGGER_HPP_

namespace trac
{
	/**
	 * @brief	Print a log message with the engine logger.
	 * 
	 * @tparam Args	The argument types used in the format string.
	 * @param lvl	The log level of the message to print.
	 * @param fmt	The format string.
	 * @param args	The arguments used in the format string.
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
	 */
	template<typename... Args>
	inline void log_client_critical(spdlog::format_string_t<Args...> fmt, Args &&...args)
	{
		Logger::GetClientLogger()->critical(fmt, std::forward<Args>(args)...);
	}
} // Namespace trac

#endif // LOGGER_INL_ 