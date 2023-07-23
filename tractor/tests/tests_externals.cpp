// Google Test Framework
#include <gtest/gtest.h>

// Related header include

// GLM (maths)
#include <glm/glm.hpp>

// spdlog (Logging)
#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"

// Perform some vector arithmetic to test the library
GTEST_TEST(externals, glm_vec3_addition)
{
	glm::vec3 a(1.0f, 2.0f, 3.0f);
	glm::vec3 b(1.0f, 2.0f, 3.0f);
	glm::vec3 c = a + b;
	EXPECT_EQ(c.x, 2.0f);
	EXPECT_EQ(c.y, 4.0f);
	EXPECT_EQ(c.z, 6.0f);
}

GTEST_TEST(externals, glm_vec3_subtraction)
{
	glm::vec3 a(1.0f, 2.0f, 3.0f);
	glm::vec3 b(1.0f, 2.0f, 3.0f);
	glm::vec3 c = a - b;
	EXPECT_EQ(c.x, 0.0f);
	EXPECT_EQ(c.y, 0.0f);
	EXPECT_EQ(c.z, 0.0f);
}

GTEST_TEST(externals, glm_vec3_multiplication)
{
	glm::vec3 a(1.0f, 2.0f, 3.0f);
	glm::vec3 b(1.0f, 2.0f, 3.0f);
	glm::vec3 c = a * b;
	EXPECT_EQ(c.x, 1.0f);
	EXPECT_EQ(c.y, 4.0f);
	EXPECT_EQ(c.z, 9.0f);
}

GTEST_TEST(externals, glm_vec3_division)
{
	glm::vec3 a(1.0f, 2.0f, 3.0f);
	glm::vec3 b(1.0f, 2.0f, 3.0f);
	glm::vec3 c = a / b;
	EXPECT_EQ(c.x, 1.0f);
	EXPECT_EQ(c.y, 1.0f);
	EXPECT_EQ(c.z, 1.0f);
}

GTEST_TEST(externals, glm_vec3_dot)
{
	glm::vec3 a(1.0f, 2.0f, 3.0f);
	glm::vec3 b(1.0f, 2.0f, 3.0f);
	float c = glm::dot(a, b);
	EXPECT_EQ(c, 14.0f);
}

GTEST_TEST(externals, glm_vec3_cross)
{
	glm::vec3 a(1.0f, 2.0f, 3.0f);
	glm::vec3 b(1.0f, 2.0f, 3.0f);
	glm::vec3 c = glm::cross(a, b);
	EXPECT_EQ(c.x, 0.0f);
	EXPECT_EQ(c.y, 0.0f);
	EXPECT_EQ(c.z, 0.0f);
}

// Test logging (These are not really unit tests, but they are useful for debugging if checked by used manually.)

// Test direct logging
GTEST_TEST(externals, spdlog_output_direct)
{
	spdlog::set_level(spdlog::level::level_enum::trace);
	spdlog::trace("Test trace");
	spdlog::set_level(spdlog::level::level_enum::debug);
	spdlog::debug("Test debug");
	spdlog::set_level(spdlog::level::level_enum::info);
	spdlog::info("Test info");
	spdlog::set_level(spdlog::level::level_enum::warn);
	spdlog::warn("Test warning");
	spdlog::set_level(spdlog::level::level_enum::err);
	spdlog::error("Test error");
	spdlog::set_level(spdlog::level::level_enum::critical);
	spdlog::critical("Test critical");
}

// Test logging through a logger object
GTEST_TEST(externals, spdlog_output_object)
{
	auto logger = spdlog::stdout_color_mt("console");
	logger->set_level(spdlog::level::level_enum::trace);
	logger->trace("Test trace");
	logger->set_level(spdlog::level::level_enum::debug);
	logger->debug("Test debug");
	logger->set_level(spdlog::level::level_enum::info);
	logger->info("Test info");
	logger->set_level(spdlog::level::level_enum::warn);
	logger->warn("Test warning");
	logger->set_level(spdlog::level::level_enum::err);
	logger->error("Test error");
	logger->set_level(spdlog::level::level_enum::critical);
	logger->critical("Test critical");

	// Change the format of the logger
	logger->set_level(spdlog::level::level_enum::info);
	logger->set_pattern("[%T:%e] [%n] [%^%l%$] %v");
	logger->info("The format should now be different.");
}

// Test level
GTEST_TEST(externas, spdlog_log_level)
{
	spdlog::set_level(spdlog::level::level_enum::info);
	spdlog::info("Setting log level to warn, only warnings and above should be visible of the following output.");

	spdlog::set_level(spdlog::level::level_enum::warn);
	EXPECT_EQ(spdlog::level::level_enum::warn, spdlog::get_level());

	spdlog::trace("THIS SHOULD NOT BE VISIBLE!");
	spdlog::debug("THIS SHOULD NOT BE VISIBLE!");
	spdlog::info("THIS SHOULD NOT BE VISIBLE!");
	spdlog::warn("This should be visible!");
	spdlog::error("This should be visible!");
	spdlog::critical("This should be visible!");
}