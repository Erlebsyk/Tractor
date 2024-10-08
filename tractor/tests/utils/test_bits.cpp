// Google Test Framework
#include <gtest/gtest.h>

// Related header include
#include <tractor.hpp>

/// Test the bit macros.
GTEST_TEST(tractor, bits_macros)
{
	EXPECT_EQ(0b00000000000000000000000000000001, BIT(0));
	EXPECT_EQ(0b00000000000000000000000000000010, BIT(1));
	EXPECT_EQ(0b00000000000000000000000000000100, BIT(2));
	EXPECT_EQ(0b00000000000000000000000000001000, BIT(3));
	EXPECT_EQ(0b00000000000000000000000000010000, BIT(4));
	EXPECT_EQ(0b00000000000000000000000000100000, BIT(5));
	EXPECT_EQ(0b00000000000000000000000001000000, BIT(6));
	EXPECT_EQ(0b00000000000000000000000010000000, BIT(7));
	EXPECT_EQ(0b00000000000000000000000100000000, BIT(8));
	EXPECT_EQ(0b00000000000000000000001000000000, BIT(9));
	EXPECT_EQ(0b00000000000000000000010000000000, BIT(10));
	EXPECT_EQ(0b00000000000000000000100000000000, BIT(11));
	EXPECT_EQ(0b00000000000000000001000000000000, BIT(12));
	EXPECT_EQ(0b00000000000000000010000000000000, BIT(13));
	EXPECT_EQ(0b00000000000000000100000000000000, BIT(14));
	EXPECT_EQ(0b00000000000000001000000000000000, BIT(15));
	EXPECT_EQ(0b00000000000000010000000000000000, BIT(16));
	EXPECT_EQ(0b00000000000000100000000000000000, BIT(17));
	EXPECT_EQ(0b00000000000001000000000000000000, BIT(18));
	EXPECT_EQ(0b00000000000010000000000000000000, BIT(19));
	EXPECT_EQ(0b00000000000100000000000000000000, BIT(20));
	EXPECT_EQ(0b00000000001000000000000000000000, BIT(21));
	EXPECT_EQ(0b00000000010000000000000000000000, BIT(22));
	EXPECT_EQ(0b00000000100000000000000000000000, BIT(23));
	EXPECT_EQ(0b00000001000000000000000000000000, BIT(24));
	EXPECT_EQ(0b00000010000000000000000000000000, BIT(25));
	EXPECT_EQ(0b00000100000000000000000000000000, BIT(26));
	EXPECT_EQ(0b00001000000000000000000000000000, BIT(27));
	EXPECT_EQ(0b00010000000000000000000000000000, BIT(28));
	EXPECT_EQ(0b00100000000000000000000000000000, BIT(29));
	EXPECT_EQ(0b01000000000000000000000000000000, BIT(30));
	EXPECT_EQ(0b10000000000000000000000000000000, BIT(31));

	EXPECT_NE(0b00000000000000000000000000000000, BIT(0));
	EXPECT_NE(0b00000000000000000000000000000010, BIT(3));
	EXPECT_NE(0b00010001000000001000000010000100, BIT(2));
	EXPECT_NE(0b00010001000000001000000010000100, BIT(3));
	
	EXPECT_EQ(0b00000000000000000000000000001100, BIT(2) | BIT(3));
}

GTEST_TEST(tractor, bits_signed_max)
{
	EXPECT_EQ(INT8_MAX, trac::signed_max<int8_t>());
	EXPECT_EQ(INT16_MAX, trac::signed_max<int16_t>());
	EXPECT_EQ(INT32_MAX, trac::signed_max<int32_t>());
	EXPECT_EQ(INT64_MAX, trac::signed_max<int64_t>());

	EXPECT_NE(INT8_MIN, trac::signed_max<int8_t>());
	EXPECT_NE(INT16_MAX, trac::signed_max<int32_t>());
}

GTEST_TEST(tractor, bits_downshift_mask)
{
	uint32_t value = 0b11111111111111111111111111111111;
	// Expect downshift to remove top 7 bits (a signed int8_t has 7 data bits, 1 sign bit).
	EXPECT_EQ(0b00000001111111111111111111111111, trac::downshift_mask<int8_t>(value));
	// Expect downshift to remove top 15 bits (a signed int16_t has 15 data bits, 1 sign bit).
	EXPECT_EQ(0b00000000000000011111111111111111, trac::downshift_mask<int16_t>(value));
	// Expect downshift to remove top 31 bits (a signed int32_t has 31 data bits, 1 sign bit).
	EXPECT_EQ(0b00000000000000000000000000000001, trac::downshift_mask<int32_t>(value));

	value = 0b01111111111111111111111111111111;
	// Expect downshift to remove top 7 bits (a signed int8_t has 7 data bits, 1 sign bit).
	EXPECT_EQ(0b00000000111111111111111111111111, trac::downshift_mask<int8_t>(value));
	// Expect downshift to remove top 15 bits (a signed int16_t has 15 data bits, 1 sign bit).
	EXPECT_EQ(0b00000000000000001111111111111111, trac::downshift_mask<int16_t>(value));
	// Expect downshift to remove top 31 bits (a signed int32_t has 31 data bits, 1 sign bit).
	EXPECT_EQ(0b00000000000000000000000000000000, trac::downshift_mask<int32_t>(value));	

	value = 0;
	EXPECT_EQ(0, trac::downshift_mask<int8_t>(value));
	EXPECT_EQ(0, trac::downshift_mask<int16_t>(value));
	EXPECT_EQ(0, trac::downshift_mask<int32_t>(value));

	value = INT8_MAX;
	EXPECT_EQ(0, trac::downshift_mask<int8_t>(value));
	value = INT8_MAX+1;
	EXPECT_EQ(1, trac::downshift_mask<int8_t>(value));
	value = INT32_MAX;
	EXPECT_TRUE(1 <= trac::downshift_mask<int8_t>(value));
}

/// Test the bit checking function.
GTEST_TEST(tractor, bits_check)
{
	EXPECT_FALSE(trac::is_bit_set(0b00000000000000000000000000000000, 0));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000000000000000000000001, 0));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000000000000000000000010, 1));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000000000000000000000100, 2));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000000000000000000001000, 3));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000000000000000000010000, 4));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000000000000000000100000, 5));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000000000000000001000000, 6));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000000000000000010000000, 7));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000000000000000100000000, 8));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000000000000001000000000, 9));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000000000000010000000000, 10));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000000000000100000000000, 11));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000000000001000000000000, 12));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000000000010000000000000, 13));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000000000100000000000000, 14));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000000001000000000000000, 15));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000000010000000000000000, 16));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000000100000000000000000, 17));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000001000000000000000000, 18));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000010000000000000000000, 19));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000100000000000000000000, 20));
	EXPECT_TRUE(trac::is_bit_set(0b00000000001000000000000000000000, 21));
	EXPECT_TRUE(trac::is_bit_set(0b00000000010000000000000000000000, 22));
	EXPECT_TRUE(trac::is_bit_set(0b00000000100000000000000000000000, 23));
	EXPECT_TRUE(trac::is_bit_set(0b00000001000000000000000000000000, 24));
	EXPECT_TRUE(trac::is_bit_set(0b00000010000000000000000000000000, 25));
	EXPECT_TRUE(trac::is_bit_set(0b00000100000000000000000000000000, 26));
	EXPECT_TRUE(trac::is_bit_set(0b00001000000000000000000000000000, 27));
	EXPECT_TRUE(trac::is_bit_set(0b00010000000000000000000000000000, 28));
	EXPECT_TRUE(trac::is_bit_set(0b00100000000000000000000000000000, 29));
	EXPECT_TRUE(trac::is_bit_set(0b01000000000000000000000000000000, 30));
	EXPECT_TRUE(trac::is_bit_set(0b10000000000000000000000000000000, 31));

	EXPECT_TRUE(trac::is_bit_set(0b00000000000000000000000000001100, 2));
	EXPECT_TRUE(trac::is_bit_set(0b00000000000000000000000000001100, 3));
	EXPECT_TRUE(trac::is_bit_set(0b00000000010000000000000000001100, 2));
	EXPECT_TRUE(trac::is_bit_set(0b00000000010000000000000000001100, 3));

	EXPECT_FALSE(trac::is_bit_set(0b11111111111111111111111111111110, 0));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111111111111111111111101, 1));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111111111111111111111011, 2));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111111111111111111110111, 3));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111111111111111111101111, 4));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111111111111111111011111, 5));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111111111111111110111111, 6));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111111111111111101111111, 7));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111111111111111011111111, 8));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111111111111110111111111, 9));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111111111111101111111111, 10));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111111111111011111111111, 11));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111111111110111111111111, 12));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111111111101111111111111, 13));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111111111011111111111111, 14));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111111110111111111111111, 15));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111111101111111111111111, 16));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111111011111111111111111, 17));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111110111111111111111111, 18));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111101111111111111111111, 19));
	EXPECT_FALSE(trac::is_bit_set(0b11111111111011111111111111111111, 20));
	EXPECT_FALSE(trac::is_bit_set(0b11111111110111111111111111111111, 21));
	EXPECT_FALSE(trac::is_bit_set(0b11111111101111111111111111111111, 22));
	EXPECT_FALSE(trac::is_bit_set(0b11111111011111111111111111111111, 23));
	EXPECT_FALSE(trac::is_bit_set(0b11111110111111111111111111111111, 24));
	EXPECT_FALSE(trac::is_bit_set(0b11111101111111111111111111111111, 25));
	EXPECT_FALSE(trac::is_bit_set(0b11111011111111111111111111111111, 26));
	EXPECT_FALSE(trac::is_bit_set(0b11110111111111111111111111111111, 27));
	EXPECT_FALSE(trac::is_bit_set(0b11101111111111111111111111111111, 28));
	EXPECT_FALSE(trac::is_bit_set(0b11011111111111111111111111111111, 29));
	EXPECT_FALSE(trac::is_bit_set(0b10111111111111111111111111111111, 30));
	EXPECT_FALSE(trac::is_bit_set(0b01111111111111111111111111111111, 31));
}

/// Test the bit manipulation functions.
GTEST_TEST(tractor, bits_manipulation)
{
	uint32_t value = 0;
	EXPECT_EQ(0, value);

	trac::bit_set(value, 0);
	EXPECT_EQ(0b00000000000000000000000000000001, value);
	trac::bit_clear(value, 0);
	EXPECT_EQ(0b00000000000000000000000000000000, value);
	
	trac::bit_set(value, 1);
	EXPECT_EQ(0b00000000000000000000000000000010, value);
	trac::bit_set(value, 2);
	EXPECT_EQ(0b00000000000000000000000000000110, value);
	trac::bit_clear(value, 1);
	EXPECT_EQ(0b00000000000000000000000000000100, value);
	trac::bit_clear(value, 2);
	EXPECT_EQ(0b00000000000000000000000000000000, value);

	trac::bit_toggle(value, 2);
	EXPECT_EQ(0b00000000000000000000000000000100, value);
	trac::bit_toggle(value, 2);
	EXPECT_EQ(0b00000000000000000000000000000000, value);

	trac::bit_set_to(value, 2, true);
	EXPECT_EQ(0b00000000000000000000000000000100, value);
	trac::bit_set_to(value, 20, true);
	EXPECT_EQ(0b00000000000100000000000000000100, value);
	trac::bit_set_to(value, 20, false);
	EXPECT_EQ(0b00000000000000000000000000000100, value);
}