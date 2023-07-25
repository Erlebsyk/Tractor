// Google Test Framework
#include <gtest/gtest.h>

// Related header include
#include <tractor.h>

// Tractor application tests

// Application tests

namespace test
{
	/**
	 * @brief	Create the simplest possible application class for testing. When constructed, the value_ variable is set to 0. When run, the value_ variable is
	 * 			set to 1.
	 */
	class TestApp : public trac::Application
	{
	public:
		int8_t value_;

		TestApp() : trac::Application(), value_{0} {}
		~TestApp() {}
		void run() { value_ = 1; }
	};

	GTEST_TEST(tractor, engine_initialize)
	{
		EXPECT_FALSE(trac::is_engine_initialized());
		EXPECT_FALSE(trac::is_app_running());
		trac::initialize_engine();
		EXPECT_TRUE(trac::is_engine_initialized());
		EXPECT_FALSE(trac::is_app_running());
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
		trac::run_application(test_app);
		EXPECT_EQ(1, test_app->value_);

		// Run the test application again, the value_ variable should still be 1.
		trac::run_application(test_app);
		EXPECT_EQ(1, test_app->value_);
	}

	// The logging through the tractor logging module.
	GTEST_TEST(tractor, logging_level)
	{
		trac::initialize_engine();
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
		trac::initialize_engine();
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
		trac::initialize_engine();
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

}
