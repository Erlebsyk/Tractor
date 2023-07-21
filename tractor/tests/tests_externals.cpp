// Google Test Framework
#include <gtest/gtest.h>

// Related header include
#include <glm/glm.hpp>

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