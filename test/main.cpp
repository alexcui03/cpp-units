#include <type_traits>

#include "../cpp-units/cpp-units.hpp"

using namespace cpp_units::literals;

constexpr cpp_units::utils::constexpr_string str_l = "L";
constexpr cpp_units::utils::constexpr_string str_m = "M";
constexpr cpp_units::utils::constexpr_string str_k = "K";

using pair1 = cpp_units::utils::meta_pair<str_l, 1>;
using pair2 = cpp_units::utils::meta_pair<str_m, 2>;
using pair3 = cpp_units::utils::meta_pair<str_l, 3>;

using map1 = cpp_units::utils::meta_map<pair1, pair2>;
using map2 = cpp_units::utils::meta_map<pair2, pair1>;
using map3 = cpp_units::utils::meta_map<pair1, pair3, pair2>;
using map4 = map1::set_t<str_l, 3>;
using map5 = map1::set_t<str_k, 4>;

static_assert(map1::get_v<str_l> == 1);
static_assert(map1::get_v<str_m> == 2);
static_assert(map3::get_v<str_l> == 3);
static_assert(map4::get_v<str_l> == 3);
static_assert(map5::get_v<str_k> == 4);
static_assert(cpp_units::utils::is_same_map_v<map1, map2>);
static_assert(cpp_units::utils::is_same_map_v<map3, map4>);

using dim1 = cpp_units::dimension<str_l>;
using dim2 = cpp_units::dimension_multiply_t<dim1, dim1>;
using dim3 = cpp_units::dimension<str_m>;
using dim4 = cpp_units::dimension_multiply_t<dim1, dim3>;
using dim5 = cpp_units::dimension_multiply_t<dim3, dim1>;
using dim6 = cpp_units::dimension_divide_t<dim1, dim1>;
using dim7 = cpp_units::dimension_divide_t<dim3, dim3>;

static_assert(cpp_units::is_same_dimension_v<dim1, dim1>);
static_assert(!cpp_units::is_same_dimension_v<dim1, dim2>);
static_assert(cpp_units::is_same_dimension_v<dim4, dim5>);
static_assert(dim1::get_v<str_l> == 1);
static_assert(dim2::get_v<str_l> == 2);
static_assert(dim6::get_v<str_l> == 0);
static_assert(cpp_units::is_same_dimension_v<dim6, dim7>);
static_assert(!cpp_units::utils::is_same_map_v<dim6, dim7>);

int main() {
    constexpr auto v1 = 1_m;
    constexpr auto v2 = 20_mm;
    constexpr auto v3 = v1 - v2;
    constexpr auto v4 = v1 / v2;
    constexpr auto v5 = v1 * v2;
    constexpr auto v6 = v4 + 3;
    constexpr auto v7 = 3 + v4;

    static_assert(cpp_units::is_same_dimension_v<decltype(v4)::dimension, dim6>);
    static_assert(cpp_units::is_same_dimension_v<decltype(v5)::dimension, dim2>);

    return 0;
}
