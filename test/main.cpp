#include <type_traits>

#include "../cpp-units/cpp-units.hpp"

using namespace cpp_units::literals;

int main() {
    auto v1 = 1_m;
    auto v2 = 20_mm;

    static_assert(std::is_same_v<decltype(v1), cpp_units::metres<std::intmax_t>>);

    return 0;
}
