#include <gtest/gtest.h>

#define STATIC_EXPECT_TRUE(expr) static_assert(expr); EXPECT_TRUE(expr);
#define STATIC_EXPECT_FALSE(expr) static_assert(!(expr)); EXPECT_FALSE(expr);
