#include <gtest/gtest.h>

#include <type_traits>

#include "utils.h"
#include "../cpp-units/utils/constexpr_string.hpp"
#include "../cpp-units/utils/meta_map.hpp"
#include "../cpp-units/dimension.hpp"

using namespace cpp_units;
using namespace cpp_units::utils;

TEST(Dimension, Constructor) {
    using dim = dimension<"L">;
    constexpr constexpr_string key = "L";

    STATIC_EXPECT_TRUE(dim::get_v<key> == 1);
}

TEST(Dimension, Compare) {
    using dim1 = dimension<"L">;
    using dim2 = dimension<"L">;

    STATIC_EXPECT_TRUE((is_same_dimension_v<dim1, dim2>));
    STATIC_EXPECT_TRUE((is_same_dimension_v<dim2, dim1>));
}

TEST(Dimension, Multiply) {
    using dim1 = dimension<"L">;
    constexpr constexpr_string key1 = "L";
    using dim2 = dimension<"M">;
    constexpr constexpr_string key2 = "M";

    using dim3 = dimension_multiply_t<dim1, dim2>;
    STATIC_EXPECT_TRUE(dim3::get_v<key1> == 1);
    STATIC_EXPECT_TRUE(dim3::get_v<key2> == 1);

    using dim4 = dimension_multiply_t<dim1, dim1>;
    STATIC_EXPECT_TRUE(dim4::get_v<key1> == 2);
}

TEST(Dimension, Divide) {
    using dim1 = dimension<"L">;
    constexpr constexpr_string key1 = "L";
    using dim2 = dimension<"M">;
    constexpr constexpr_string key2 = "M";

    using dim3 = dimension_divide_t<dim1, dim2>;
    STATIC_EXPECT_TRUE(dim3::get_v<key1> == 1);
    STATIC_EXPECT_TRUE(dim3::get_v<key2> == -1);

    using dim4 = dimension_divide_t<dim1, dim1>;
    STATIC_EXPECT_TRUE(dim4::get_v<key1> == 0);
}

TEST(Dimension, Dimensionless) {
    using dim1 = dimension<"L">;
    using dim2 = dimension_divide_t<dim1, dim1>;

    STATIC_EXPECT_TRUE((is_same_dimension_v<dim2, dimensionless>));
}
