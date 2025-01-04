#include <type_traits>

#include "../cpp-units/cpp-units.hpp"

using namespace cpp_units::literals;

using pair1 = cpp_units::utils::constexpr_pair<'L', 1>;
using pair2 = cpp_units::utils::constexpr_pair<'M', 2>;
using pair3 = cpp_units::utils::constexpr_pair<'L', 3>;

using map1 = cpp_units::utils::constexpr_map<pair1, pair2>;
using map2 = cpp_units::utils::constexpr_map<pair2, pair1>;
using map3 = cpp_units::utils::constexpr_map<pair1, pair3, pair2>;
using map4 = map1::set_t<'L', 3>;
using map5 = map1::set_t<'K', 4>;

static_assert(map1::get_v<'L'> == 1);
static_assert(map1::get_v<'M'> == 2);
static_assert(map3::get_v<'L'> == 3);
static_assert(map4::get_v<'L'> == 3);
static_assert(map5::get_v<'K'> == 4);
static_assert(cpp_units::utils::is_same_map_v<map1, map2>);
static_assert(cpp_units::utils::is_same_map_v<map3, map4>);

using dim1 = cpp_units::dimension<'L'>;
using dim2 = cpp_units::dimension_multiply_t<dim1, dim1>;
using dim3 = cpp_units::dimension<'M'>;
using dim4 = cpp_units::dimension_multiply_t<dim1, dim3>;
using dim5 = cpp_units::dimension_multiply_t<dim3, dim1>;

static_assert(cpp_units::is_same_dimension_v<dim1, dim1>);
static_assert(!cpp_units::is_same_dimension_v<dim1, dim2>);
static_assert(cpp_units::is_same_dimension_v<dim4, dim5>);
static_assert(dim1::get_v<'L'> == 1);
static_assert(dim2::get_v<'L'> == 2);

int main() {
    auto v1 = 1_m;
    auto v2 = 20_mm;

    static_assert(std::is_same_v<decltype(v1), cpp_units::metres<std::intmax_t>>);

    return 0;
}
