/**
 * @file	tractor.h
 * @brief	Main header file for the tractor game engine library.
 * 
 * @author	Erlend Elias Isachsen
 * @date	20.07.2023
 * 
*/

#ifndef TRACTOR_H_
#define TRACTOR_H_

// Standard library header includes
#include <cstdint>
#include <memory>

// External libraries header includes


// Project header includes
#include "tractor/application.h"
#include "tractor/logger.h"

namespace trac
{
	void run_application(std::shared_ptr<Application> app);
}


#endif // TRACTOR_H_ 

/*
 * END OF FILE
 */