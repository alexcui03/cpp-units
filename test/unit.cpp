#include <gtest/gtest.h>

#include "utils.h"
#include "../cpp-units/unit.hpp"

using namespace cpp_units;

TEST(Unit, Constructor) {
    using test_unit = unit<dimension<"L">, int>;

    constexpr test_unit value1(1);
    STATIC_EXPECT_TRUE(value1.value() == 1);
    STATIC_EXPECT_TRUE((is_same_dimension_v<decltype(value1)::dimension, dimension<"L">>));
}

TEST(Unit, ArithmeticExpression) {
    using test_unit = unit<dimension<"L">, int>;
    using dim1 = dimension_multiply_t<dimension<"L">, dimension<"L">>;
    constexpr test_unit value1(2);

    constexpr auto value2 = value1 + value1;
    STATIC_EXPECT_TRUE(value2.value() == 4);
    STATIC_EXPECT_TRUE((is_same_dimension_v<decltype(value2)::dimension, dimension<"L">>));

    constexpr auto value3 = value1 - value1;
    STATIC_EXPECT_TRUE(value3.value() == 0);
    STATIC_EXPECT_TRUE((is_same_dimension_v<decltype(value3)::dimension, dimension<"L">>));

    constexpr auto value4 = value1 * value1;
    STATIC_EXPECT_TRUE(value4.value() == 4);
    STATIC_EXPECT_TRUE((is_same_dimension_v<decltype(value4)::dimension, dim1>));

    constexpr auto value5 = value1 / value1;
    STATIC_EXPECT_TRUE(value5.value() == 1);
    STATIC_EXPECT_TRUE((is_same_dimension_v<decltype(value5)::dimension, dimensionless>));
}

TEST(Unit, ArithmeticWithDemensionless) {
    using test_unit = unit<dimension<"L">, int>;
    constexpr unit<dimensionless, int> value0(1);
    constexpr test_unit value1(2);

    EXPECT_EQ((value0 + 10).value(), 11);
    EXPECT_EQ((10 + value0).value(), 11);
    EXPECT_EQ((value0 - 10).value(), -9);
    EXPECT_EQ((10 - value0).value(), 9);
    EXPECT_EQ((value1 * 10).value(), 20);
    EXPECT_EQ((10 * value1).value(), 20);
    EXPECT_EQ((value1 / 10).value(), 0);
    EXPECT_EQ((10 / value1).value(), 5);
}
