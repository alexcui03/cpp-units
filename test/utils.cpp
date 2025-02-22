#include <gtest/gtest.h>

#include <type_traits>

#include "../cpp-units/utils/constexpr_string.hpp"
#include "../cpp-units/utils/meta_map.hpp"

#define STATIC_EXPECT_TRUE(expr) static_assert(expr); EXPECT_TRUE(expr);
#define STATIC_EXPECT_FALSE(expr) static_assert(!(expr)); EXPECT_FALSE(expr);

using namespace cpp_units;
using namespace cpp_units::utils;

TEST(ConstexprString, Constructor) {
    constexpr constexpr_string str = "Test String";

    EXPECT_STREQ(str.data, "Test String");
}

TEST(ConstexprString, Compare) {
    constexpr constexpr_string str1 = "String 1";
    constexpr constexpr_string str2 = "String 2";

    STATIC_EXPECT_TRUE(str1 == str1);
    STATIC_EXPECT_FALSE(str1 == str2);

    STATIC_EXPECT_FALSE(str1 != str1);
    STATIC_EXPECT_TRUE(str1 != str2);
}

TEST(MetaPair, Constructor) {
    using pair = meta_pair<'A', 1>;

    // Check meta_pair's data and type
    EXPECT_TRUE((std::is_same_v<pair::key_type, char>));
    EXPECT_TRUE((std::is_same_v<pair::value_type, int>));
    EXPECT_EQ(pair::key, 'A');
    EXPECT_EQ(pair::value, 1);
}

TEST(MetaMap, Constructor) {
    using pair1 = meta_pair<'A', 1>;
    using pair2 = meta_pair<'B', 2>;

    using map = meta_map<pair1, pair2>;

    STATIC_EXPECT_TRUE(map::get_v<'A'> == 1);
    STATIC_EXPECT_TRUE(map::get_v<'B'> == 2);
    STATIC_EXPECT_FALSE(map::has_v<'C'>);
}

TEST(MetaMap, ConstructWithDuplicateKey) {
    using pair1 = meta_pair<'A', 1>;
    using pair2 = meta_pair<'A', 2>;

    using map = meta_map<pair1, pair2>;

    STATIC_EXPECT_TRUE(map::get_v<'A'> == 2);
}

TEST(MetaMap, EmptyMap) {
    using map = meta_map<>;

    EXPECT_TRUE(true);
}

TEST(MetaMap, Compare) {
    using pair1 = meta_pair<'A', 1>;
    using pair2 = meta_pair<'B', 2>;

    using map1 = meta_map<pair1, pair2>;
    using map2 = meta_map<pair2, pair1>;

    STATIC_EXPECT_TRUE((is_same_map_v<map1, map2>));
}

TEST(MetaMap, Modify) {
    using pair1 = meta_pair<'A', 1>;

    using map1 = meta_map<pair1>;
    using map2 = map1::set_t<'A', 2>;

    STATIC_EXPECT_TRUE(map1::get_v<'A'> == 1);
    STATIC_EXPECT_TRUE(map2::get_v<'A'> == 2);
}
