// Google Test Framework
#include <gtest/gtest.h>

// Related header include
#include <tractor.hpp>

GTEST_TEST(tractor, utils_bitshift_macros)
{
	
}

GTEST_TEST(tractor, int32_clamp_positive)
{
	// Test the clamp_int_to_positive copy-variant for regular integers
	int a = 0;
	int b = -1;
	int c = 1;
	int d = 10000;
	int e = -10000;
	int f = INT_MAX;
	int g = INT_MIN;

	a = trac::clamp_int_to_positive(a);
	EXPECT_EQ(a, 0);
	b = trac::clamp_int_to_positive(b);
	EXPECT_EQ(b, 0);
	c = trac::clamp_int_to_positive(c);
	EXPECT_EQ(c, 1);
	d = trac::clamp_int_to_positive(d);
	EXPECT_EQ(d, 10000);
	e = trac::clamp_int_to_positive(e);
	EXPECT_EQ(e, 0);
	f = trac::clamp_int_to_positive(f);
	EXPECT_EQ(f, INT_MAX);
	g = trac::clamp_int_to_positive(g);
	EXPECT_EQ(g, 0);

	// Test the clamp_int_to_positive_ref variant for regular integers, passing by reference
	a = 0;
	b = -1;
	c = 1;
	d = 10000;
	e = -10000;
	f = INT_MAX;
	g = INT_MIN;

	trac::clamp_int_to_positive_ref(a);
	EXPECT_EQ(a, 0);
	trac::clamp_int_to_positive_ref(b);
	EXPECT_EQ(b, 0);
	trac::clamp_int_to_positive_ref(c);
	EXPECT_EQ(c, 1);
	trac::clamp_int_to_positive_ref(d);
	EXPECT_EQ(d, 10000);
	trac::clamp_int_to_positive_ref(e);
	EXPECT_EQ(e, 0);
	trac::clamp_int_to_positive_ref(f);
	EXPECT_EQ(f, INT_MAX);
	trac::clamp_int_to_positive_ref(g);
	EXPECT_EQ(g, 0);
}

GTEST_TEST(tractor, int64_clamp_positive)
{
	// Test the clamp_int_to_negative_ref variant for long integers (int64_t)
	int64_t la = 0;
	int64_t lb = -1;
	int64_t lc = 1;
	int64_t ld = 10000;
	int64_t le = -10000;
	int64_t lf = INT64_MAX;
	int64_t lg = INT64_MIN;

	la = trac::clamp_int_to_positive(la);
	EXPECT_EQ(la, 0);
	lb = trac::clamp_int_to_positive(lb);
	EXPECT_EQ(lb, 0);
	lc = trac::clamp_int_to_positive(lc);
	EXPECT_EQ(lc, 1);
	ld = trac::clamp_int_to_positive(ld);
	EXPECT_EQ(ld, 10000);
	le = trac::clamp_int_to_positive(le);
	EXPECT_EQ(le, 0);
	lf = trac::clamp_int_to_positive(lf);
	EXPECT_EQ(lf, INT64_MAX);
	lg = trac::clamp_int_to_positive(lg);
	EXPECT_EQ(lg, 0);

	// Test the clamp_int_to_positive_ref variant for long integers (int64_t), passing by reference
	la = 0;
	lb = -1;
	lc = 1;
	ld = 10000;
	le = -10000;
	lf = INT64_MAX;
	lg = INT64_MIN;

	trac::clamp_int_to_positive_ref(la);
	EXPECT_EQ(la, 0);
	trac::clamp_int_to_positive_ref(lb);
	EXPECT_EQ(lb, 0);
	trac::clamp_int_to_positive_ref(lc);
	EXPECT_EQ(lc, 1);
	trac::clamp_int_to_positive_ref(ld);
	EXPECT_EQ(ld, 10000);
	trac::clamp_int_to_positive_ref(le);
	EXPECT_EQ(le, 0);
	trac::clamp_int_to_positive_ref(lf);
	EXPECT_EQ(lf, INT64_MAX);
	trac::clamp_int_to_positive_ref(lg);
	EXPECT_EQ(lg, 0);
}

GTEST_TEST(tractor, int32_clamp_to_negative)
{
	// Test the clamp_int_to_negative copy-variant for regular integers
	int a = 0;
	int b = -1;
	int c = 1;
	int d = 10000;
	int e = -10000;
	int f = INT_MAX;
	int g = INT_MIN;

	a = trac::clamp_int_to_negative(a);
	EXPECT_EQ(a, 0);
	b = trac::clamp_int_to_negative(b);
	EXPECT_EQ(b, -1);
	c = trac::clamp_int_to_negative(c);
	EXPECT_EQ(c, 0);
	d = trac::clamp_int_to_negative(d);
	EXPECT_EQ(d, 0);
	e = trac::clamp_int_to_negative(e);
	EXPECT_EQ(e, -10000);
	f = trac::clamp_int_to_negative(f);
	EXPECT_EQ(f, 0);
	g = trac::clamp_int_to_negative(g);
	EXPECT_EQ(g, INT_MIN);

	// Test the clamp_int_to_negative_ref variant for regular integers, passing by reference
	a = 0;
	b = -1;
	c = 1;
	d = 10000;
	e = -10000;
	f = INT_MAX;
	g = INT_MIN;

	trac::clamp_int_to_negative_ref(a);
	EXPECT_EQ(a, 0);
	trac::clamp_int_to_negative_ref(b);
	EXPECT_EQ(b, -1);
	trac::clamp_int_to_negative_ref(c);
	EXPECT_EQ(c, 0);
	trac::clamp_int_to_negative_ref(d);
	EXPECT_EQ(d, 0);
	trac::clamp_int_to_negative_ref(e);
	EXPECT_EQ(e, -10000);
	trac::clamp_int_to_negative_ref(f);
	EXPECT_EQ(f, 0);
	trac::clamp_int_to_negative_ref(g);
	EXPECT_EQ(g, INT_MIN);
}

GTEST_TEST(tractor, int64_clamp_to_negative)
{
	
	// Test the clamp_int_to_negative copy-variant for long integers (int64_t)
	int64_t la = 0;
	int64_t lb = -1;
	int64_t lc = 1;
	int64_t ld = 10000;
	int64_t le = -10000;
	int64_t lf = INT64_MAX;
	int64_t lg = INT64_MIN;

	la = trac::clamp_int_to_negative(la);
	EXPECT_EQ(la, 0);
	lb = trac::clamp_int_to_negative(lb);
	EXPECT_EQ(lb, -1);
	lc = trac::clamp_int_to_negative(lc);
	EXPECT_EQ(lc, 0);
	ld = trac::clamp_int_to_negative(ld);
	EXPECT_EQ(ld, 0);
	le = trac::clamp_int_to_negative(le);
	EXPECT_EQ(le, -10000);
	lf = trac::clamp_int_to_negative(lf);
	EXPECT_EQ(lf, 0);
	lg = trac::clamp_int_to_negative(lg);
	EXPECT_EQ(lg, INT64_MIN);

	// Test the clamp_int_to_negative_ref variant for long integers (int64_t), passing by reference
	la = 0;
	lb = -1;
	lc = 1;
	ld = 10000;
	le = -10000;
	lf = INT64_MAX;
	lg = INT64_MIN;

	trac::clamp_int_to_negative_ref(la);
	EXPECT_EQ(la, 0);
	trac::clamp_int_to_negative_ref(lb);
	EXPECT_EQ(lb, -1);
	trac::clamp_int_to_negative_ref(lc);
	EXPECT_EQ(lc, 0);
	trac::clamp_int_to_negative_ref(ld);
	EXPECT_EQ(ld, 0);
	trac::clamp_int_to_negative_ref(le);
	EXPECT_EQ(le, -10000);
	trac::clamp_int_to_negative_ref(lf);
	EXPECT_EQ(lf, 0);
	trac::clamp_int_to_negative_ref(lg);
	EXPECT_EQ(lg, INT64_MIN);
}

GTEST_TEST(tractor, uint32_clamp_int32)
{
	// Test the clamp_uint_to_int copy-variant
	uint32_t ua = 0;
	uint32_t ub = 10;
	uint32_t uc = INT32_MAX;
	uint32_t ud = INT32_MAX + 1;
	uint32_t ue = UINT32_MAX;

	int32_t a = trac::clamp_uint_to_int<int32_t>(ua);
	EXPECT_EQ(a, 0);
	int32_t b = trac::clamp_uint_to_int<int32_t>(ub);
	EXPECT_EQ(b, 10);
	int32_t c = trac::clamp_uint_to_int<int32_t>(uc);
	EXPECT_EQ(c, INT32_MAX);
	int32_t d = trac::clamp_uint_to_int<int32_t>(ud);
	EXPECT_EQ(d, INT32_MAX);
	int32_t e = trac::clamp_uint_to_int<int32_t>(ue);
	EXPECT_EQ(e, INT32_MAX);

	// Test the clamp_uint_to_int_ref variant, passing by reference
	ua = 0;
	ub = 10;
	uc = INT32_MAX;
	ud = INT32_MAX + 1;
	ue = UINT32_MAX;

	trac::clamp_uint_to_int_ref<int32_t>(ua);
	EXPECT_EQ(ua, 0);
	trac::clamp_uint_to_int_ref<int32_t>(ub);
	EXPECT_EQ(ub, 10);
	trac::clamp_uint_to_int_ref<int32_t>(uc);
	EXPECT_EQ(uc, INT32_MAX);
	trac::clamp_uint_to_int_ref<int32_t>(ud);
	EXPECT_EQ(ud, INT32_MAX);
	trac::clamp_uint_to_int_ref<int32_t>(ue);
	EXPECT_EQ(ue, INT32_MAX);
}

GTEST_TEST(tractor, uint32_clamp_int16_t)
{
	// Test the clamp_uint_to_int copy-variant
	uint32_t ua = 0;
	uint32_t ub = 10;
	uint32_t uc = INT16_MAX;
	uint32_t ud = INT16_MAX + 1;
	uint32_t ue = UINT16_MAX;
	uint32_t uf = UINT32_MAX;

	int16_t a = trac::clamp_uint_to_int<int16_t>(ua);
	EXPECT_EQ(a, 0);
	int16_t b = trac::clamp_uint_to_int<int16_t>(ub);
	EXPECT_EQ(b, 10);
	int16_t c = trac::clamp_uint_to_int<int16_t>(uc);
	EXPECT_EQ(c, INT16_MAX);
	int16_t d = trac::clamp_uint_to_int<int16_t>(ud);
	EXPECT_EQ(d, INT16_MAX);
	int16_t e = trac::clamp_uint_to_int<int16_t>(ue);
	EXPECT_EQ(e, INT16_MAX);
	int16_t f = trac::clamp_uint_to_int<int16_t>(uf);
	EXPECT_EQ(f, INT16_MAX);

	// Test the clamp_uint_to_int_ref variant, passing by reference
	ua = 0;
	ub = 10;
	uc = INT16_MAX;
	ud = INT16_MAX + 1;
	ue = UINT16_MAX;
	uf = UINT32_MAX;

	trac::clamp_uint_to_int_ref<int16_t>(ua);
	EXPECT_EQ(ua, 0);
	trac::clamp_uint_to_int_ref<int16_t>(ub);
	EXPECT_EQ(ub, 10);
	trac::clamp_uint_to_int_ref<int16_t>(uc);
	EXPECT_EQ(uc, INT16_MAX);
	trac::clamp_uint_to_int_ref<int16_t>(ud);
	EXPECT_EQ(ud, INT16_MAX);
	trac::clamp_uint_to_int_ref<int16_t>(ue);
	EXPECT_EQ(ue, INT16_MAX);
	trac::clamp_uint_to_int_ref<int16_t>(uf);
	EXPECT_EQ(uf, INT16_MAX);
}