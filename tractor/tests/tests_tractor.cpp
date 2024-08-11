
// Related header include
#include <tractor.hpp>


#define ENTRY_POINT_TEST
#include <tractor/entry_point.hpp>


// Application tests

class TestApp;

/**
 * @brief	Create the simplest possible application class for testing. When constructed, the value_ variable is set to 0. When run, the value_ variable is
 * 			incremented by 1.
 */
class TestApp : public trac::Application
{
public:
	TestApp() : trac::Application(), value_{0} {}

	/**
	 * @brief	Runs the application. Increments the value_ variable by 1 each time it's called.
	 * 
	 * @return int	The exit code for the application. 0 is returned if the application exits successfully.
	 */
	int Run() override
	{
		value_++;
		return 0;
	}

	/**
	 * @brief	Quits the application.
	 */
	void Quit() override
	{
		running_ = false;
	}

	/// A simple variable that counts the number of times the run() function has been called.
	int8_t value_;
};

/**
 * @brief	Create the simplest possible application class for testing. When constructed, the value_ variable is set to 0. When run, the value_ variable is
 * 			incremented by 1.
 * 
 * @return std::shared_ptr<trac::Application>	A shared pointer to the test application.
 */
std::shared_ptr<trac::Application> trac::create_application()
{
	return std::make_shared<TestApp>();
}


namespace test
{

	GTEST_TEST(tractor, tractor_initialize)
	{
		EXPECT_TRUE(trac::is_engine_initialized());
	}

	// Check that the test application can be created, and that it is not a nullptr.
	GTEST_TEST(tractor, app_create)
	{
		std::shared_ptr<TestApp> test_app = std::make_shared<TestApp>();
		EXPECT_TRUE(test_app != nullptr);
		EXPECT_EQ(0, test_app->value_);
	}

	// Check that the test application can be run, and that the value_ variable is set to 1 as a result.
	GTEST_TEST(tractor, app_run)
	{
		// Create the test application.
		std::shared_ptr<TestApp> test_app = std::make_shared<TestApp>();
		EXPECT_EQ(0, test_app->value_);

		// Run the test application.
		int32_t status = test_app->Run();
		EXPECT_EQ(0, status);
		EXPECT_EQ(1, test_app->value_);

		// Run the test application again, the value_ variable should now be 2.
		status = test_app->Run();
		EXPECT_EQ(0, status);
		EXPECT_EQ(2, test_app->value_);
	}

	// Check that the test application can be quit.
	GTEST_TEST(tractor, app_quit)
	{
		// Create the test application.
		std::shared_ptr<TestApp> test_app = std::make_shared<TestApp>();
		EXPECT_EQ(0, test_app->value_);

		// Run the test application.
		int32_t status = test_app->Run();
		EXPECT_EQ(0, status);
		EXPECT_EQ(1, test_app->value_);

		// Quit the test application.
		test_app->Quit();
		EXPECT_FALSE(test_app->IsRunning());
		EXPECT_EQ(1, test_app->value_);
	}

	// The logging through the tractor logging module.
	GTEST_TEST(tractor, logging_level)
	{
		trac::log_engine_set_level(trac::LogLevel::kTrace);
		EXPECT_EQ(trac::LogLevel::kTrace, trac::log_engine_get_level());
		trac::log_engine_set_level(trac::LogLevel::kDebug);
		EXPECT_EQ(trac::LogLevel::kDebug, trac::log_engine_get_level());
		trac::log_engine_set_level(trac::LogLevel::kInfo);
		EXPECT_EQ(trac::LogLevel::kInfo, trac::log_engine_get_level());
		trac::log_engine_set_level(trac::LogLevel::kWarn);
		EXPECT_EQ(trac::LogLevel::kWarn, trac::log_engine_get_level());
		trac::log_engine_set_level(trac::LogLevel::kError);
		EXPECT_EQ(trac::LogLevel::kError, trac::log_engine_get_level());
		trac::log_engine_set_level(trac::LogLevel::kCritical);
		EXPECT_EQ(trac::LogLevel::kCritical, trac::log_engine_get_level());
		trac::log_engine_set_level(trac::LogLevel::kOff);
		EXPECT_EQ(trac::LogLevel::kOff, trac::log_engine_get_level());
		EXPECT_NE(trac::LogLevel::kTrace, trac::log_engine_get_level());
		EXPECT_NE(trac::LogLevel::kDebug, trac::log_engine_get_level());
		EXPECT_NE(trac::LogLevel::kInfo, trac::log_engine_get_level());
		EXPECT_NE(trac::LogLevel::kWarn, trac::log_engine_get_level());
		EXPECT_NE(trac::LogLevel::kError, trac::log_engine_get_level());
		EXPECT_NE(trac::LogLevel::kCritical, trac::log_engine_get_level());

		trac::log_client_set_level(trac::LogLevel::kTrace);
		EXPECT_EQ(trac::LogLevel::kTrace, trac::log_client_get_level());
		trac::log_client_set_level(trac::LogLevel::kDebug);
		EXPECT_EQ(trac::LogLevel::kDebug, trac::log_client_get_level());
		trac::log_client_set_level(trac::LogLevel::kInfo);
		EXPECT_EQ(trac::LogLevel::kInfo, trac::log_client_get_level());
		trac::log_client_set_level(trac::LogLevel::kWarn);
		EXPECT_EQ(trac::LogLevel::kWarn, trac::log_client_get_level());
		trac::log_client_set_level(trac::LogLevel::kError);
		EXPECT_EQ(trac::LogLevel::kError, trac::log_client_get_level());
		trac::log_client_set_level(trac::LogLevel::kCritical);
		EXPECT_EQ(trac::LogLevel::kCritical, trac::log_client_get_level());
		trac::log_client_set_level(trac::LogLevel::kOff);
		EXPECT_EQ(trac::LogLevel::kOff, trac::log_client_get_level());
		EXPECT_NE(trac::LogLevel::kTrace, trac::log_client_get_level());
		EXPECT_NE(trac::LogLevel::kDebug, trac::log_client_get_level());
		EXPECT_NE(trac::LogLevel::kInfo, trac::log_client_get_level());
		EXPECT_NE(trac::LogLevel::kWarn, trac::log_client_get_level());
		EXPECT_NE(trac::LogLevel::kError, trac::log_client_get_level());
		EXPECT_NE(trac::LogLevel::kCritical, trac::log_client_get_level());
	}

	GTEST_TEST(tractor, logging_out)
	{
		trac::log_engine_set_level(trac::LogLevel::kTrace);
		trac::log_engine_trace("This is an engine trace test message.");
		trac::log_engine_debug("This is an engine debug test message.");
		trac::log_engine_info("This is an engine info test message.");
		trac::log_engine_warn("This is an engine warn test message.");
		trac::log_engine_error("This is an engine error test message.");
		trac::log_engine_critical("This is an engine critical test message.");

		trac::log_client_set_level(trac::LogLevel::kTrace);
		trac::log_client_trace("This is a client trace test message.");
		trac::log_client_debug("This is a client debug test message.");
		trac::log_client_info("This is a client info test message.");
		trac::log_client_warn("This is a client warn test message.");
		trac::log_client_error("This is a client error test message.");
		trac::log_client_critical("This is a client critical test message.");
	}

	GTEST_TEST(tractor, logging_out_levels)
	{
		trac::log_engine_set_level(trac::LogLevel::kWarn);
		trac::log_engine_trace("THIS SHOULD NOT BE VISIBLE!");
		trac::log_engine_debug("THIS SHOULD NOT BE VISIBLE!");
		trac::log_engine_info("THIS SHOULD NOT BE VISIBLE!");
		trac::log_engine_warn("This should be visible!");
		trac::log_engine_error("This should be visible!");
		trac::log_engine_critical("This should be visible!");

		trac::log_client_set_level(trac::LogLevel::kWarn);
		trac::log_client_trace("THIS SHOULD NOT BE VISIBLE!");
		trac::log_client_debug("THIS SHOULD NOT BE VISIBLE!");
		trac::log_client_info("THIS SHOULD NOT BE VISIBLE!");
		trac::log_client_warn("This should be visible!");
		trac::log_client_error("This should be visible!");
		trac::log_client_critical("This should be visible!");

		trac::log_engine_set_level(trac::LogLevel::kOff);
		trac::log_engine_trace("THIS SHOULD NOT BE VISIBLE!");
		trac::log_engine_debug("THIS SHOULD NOT BE VISIBLE!");
		trac::log_engine_info("THIS SHOULD NOT BE VISIBLE!");
		trac::log_engine_warn("THIS SHOULD NOT BE VISIBLE!");
		trac::log_engine_error("THIS SHOULD NOT BE VISIBLE!");
		trac::log_engine_critical("THIS SHOULD NOT BE VISIBLE!");

		trac::log_client_set_level(trac::LogLevel::kOff);
		trac::log_client_trace("THIS SHOULD NOT BE VISIBLE!");
		trac::log_client_debug("THIS SHOULD NOT BE VISIBLE!");
		trac::log_client_info("THIS SHOULD NOT BE VISIBLE!");
		trac::log_client_warn("THIS SHOULD NOT BE VISIBLE!");
		trac::log_client_error("THIS SHOULD NOT BE VISIBLE!");
		trac::log_client_critical("THIS SHOULD NOT BE VISIBLE!");
	}

	//GTEST_TEST(tractor, window)
	//{
	//	std::shared_ptr<trac::Window> window = trac::Window::Create();
	//}

} // namespace test
