/**
 * This file is part of C++ Units.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>
#include <ratio>

#define CPP_UNITS_DECLARE_INTEGER(unit_type, name) \
    constexpr unit_type operator ""_##name (unsigned long long value) { \
        return unit_type(value); \
    }

#define CPP_UNITS_DECLARE_FLOAT(unit_type, name) \
    constexpr unit_type operator ""_##name (long double value) { \
        return unit_type(value); \
    }

#define CPP_UNITS_DECLARE(unit_template, name) \
    CPP_UNITS_DECLARE_INTEGER(unit_template<std::intmax_t>, name) \
    CPP_UNITS_DECLARE_FLOAT(unit_template<long double>, name)

namespace cpp_units::utils {

consteval std::intmax_t gcd(std::intmax_t x, std::intmax_t y) noexcept {
    if (x == 0 || y == 0) return 1;
    while (y) {
        const std::intmax_t t = x;
        x = y;
        y = t % y;
    }
    return x;
}

consteval std::intmax_t lcm(std::intmax_t x, std::intmax_t y) noexcept {
    return x / gcd(x, y) * y;
}

template <typename Ratio1, typename Ratio2>
struct common_ratio {
    using type = std::ratio<utils::gcd(Ratio1::num, Ratio2::num), utils::lcm(Ratio1::den, Ratio2::den)>;
};

template <typename Ratio1, typename Ratio2>
using common_ratio_t = common_ratio<Ratio1, Ratio2>::type;

}
