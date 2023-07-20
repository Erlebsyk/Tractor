// Google Test Framework
#include <gtest/gtest.h>

// Related header include
#include <tractor.hpp>

// Tests
TEST(tractor, test_always_pass)
{
	EXPECT_TRUE(true);
	EXPECT_FALSE(false);
}