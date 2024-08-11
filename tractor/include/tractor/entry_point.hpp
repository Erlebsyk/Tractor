/**
 * @file	entry_point.hpp
 * @brief	File containing the entry point for the user application. This file must be included in the user application's main source file, where the
 * 			"create_application" function must be defined by the user. The main function is defined here to properly interface with both SDL and the Google
 * 			Test Framework, and performs all necessary initialization before calling the user-defined "create_application" function, and then runs the
 * 			application.
 * 
 * 	The "create_application" function must be defined by the user application, and must return a pointer to an instance of the user-defined application which
 * 	is derived from the tractor game engine library's Application class. The "create_application" function must be defined in the same file that includes
 * 	"entry_point.hpp".
 * 
 * @author	Erlend Elias Isachsen
 * @date	09.08.2023
 * 
*/

#ifdef ENTRY_POINT_TEST
	#define MAIN_TEST_VARIANT
	#include <gtest/gtest.h>
	#define SDL_MAIN_HANDLED // Let Google Test Framework handle main.
#endif

// Standard library header includes
#include <iostream>
#include <memory>

// External libraries header includes
#include <SDL.h>

// Project header includes
#include <tractor.hpp>

namespace trac
{
	extern std::shared_ptr<Application> create_application();
	inline int32_t run(int argc, char* argv[]);
}

/**
 * @brief	Entry point for the tractor game engine library. When entry_point.hpp is included in a project, this function will be the entry point of the
 * 			application. All necessary systems are initialized here, and the user-defined "create_application" function is called to create and run the
 * 			application. If "ENTRY_POINT_TEST" is defined before including this file, the Google Test Framework will be used to run all tests in stead, after
 * 			initializing all necessary systems.
 * 
 * 			The main function is defined here to properly interface with both SDL and the Google Test Framework. SDL requires that the main function is defined
 * 			within the same translation unit where "SDL.h" is included, since SDL defines its own main function for cross-platform compatibility. However, this
 * 			interferes with the Google Test Framework, which also defines its own main function. To solve this, the preprocesser macro "SDL_MAIN_HANDLED" is
 * 			used whenever "ENTRY_POINT_TEST" is defined before including this file. This tells SDL to not define its own main function, and lets the Google
 * 			Test Framework handle main instead.
 * 
 * @param argc	Argument count.
 * @param argv	Argument vector.
 * @return int	0 if the application is run successfully, negative integer otherwise.
 */
int main(int argc, char* argv[])
{
	// Initialize SDL

	const int sdl_init_status = SDL_Init(SDL_INIT_EVERYTHING);
	if (sdl_init_status != 0)
	{
		std::cout << "SDL_Init failed: " << SDL_GetError() << std::endl;
		return -1;
	}

	// Initialize the tractor game engine library.
	trac::initialize_engine();

	// Run the application.
	return trac::run(argc, argv);
}


#ifdef MAIN_TEST_VARIANT

/**
 * @brief	Initializes the google test framework and runs all tests.
 * 
 * @param argc	Argument count.
 * @param argv	Argument vector.
 * @return int32_t	0 if all tests are successful, 1 otherwise.
 */
inline int32_t trac::run(int argc, char* argv[])
{
	// Run the Google Test Framework.
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#else

/**
 * @brief	Runs the application.
 * 
 * @param argc	Argument count.
 * @param argv	Argument vector.
 * @return int32_t	0 if the application is run successfully, negative integer otherwise.
 */
inline int32_t trac::run(int argc, char* argv[])
{
	// Run the application.
	std::shared_ptr<trac::Application> app = trac::create_application();

	int32_t status;
	if(app == nullptr)
	{
		trac::log_engine_error("Failed to create application. trac::create_application() returned nullptr.");
		status = -1;
	}
	else
	{
		status = app->Run();
	}

	return status;
}

#endif