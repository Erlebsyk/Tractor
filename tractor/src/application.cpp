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

namespace trac
{
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
} // Namespace trac
