/**
 * This file is part of C++ Units.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdlib>
#include <algorithm>

namespace cpp_units::utils {

template <std::size_t Length>
struct constexpr_string {
    char data[Length];

    consteval constexpr_string(const char (&string)[Length]) {
        std::copy_n(string, Length, data);
    }
};

template <std::size_t Length1, std::size_t Length2>
consteval bool operator==(const constexpr_string<Length1> &lhs, const constexpr_string<Length2> &rhs) {
    if constexpr (Length1 != Length2) {
        return false;
    }
    return std::equal(lhs.data, lhs.data + Length1, rhs.data);
}

}
