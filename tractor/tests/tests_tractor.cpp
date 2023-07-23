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
	 * 
	 * @author	Erlend Elias Isachsen
	 */
	class TestApp : public trac::Application
	{
	public:
		int8_t value_;

		TestApp() : trac::Application(), value_{0} {}
		~TestApp() {}
		void run() { value_ = 1; }
	};

	// Check that the test application can be created, and that it is not a nullptr.
	GTEST_TEST(tractor, test_app_create)
	{
		std::shared_ptr<TestApp> test_app = std::make_shared<TestApp>();
		EXPECT_TRUE(test_app != nullptr);
		EXPECT_EQ(0, test_app->value_);
	}

	// Check that the test application can be run, and that the value_ variable is set to 1 as a result.
	GTEST_TEST(tractor, test_app_run)
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
}
