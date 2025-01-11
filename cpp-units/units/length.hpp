/**
 * This file is part of C++ Units.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "../utils.hpp"
#include "../dimension.hpp"

namespace cpp_units {

template <typename Type, typename Ratio = std::ratio<1, 1>>
using length = unit<dimension<'L'>, Type, Ratio>;

template <typename Type> using kilometres = length<Type, std::kilo>;
template <typename Type> using metres = length<Type>;
template <typename Type> using millimetres = length<Type, std::milli>;

inline namespace literals {

CPP_UNITS_DECLARE(kilometres, km)
CPP_UNITS_DECLARE(metres, m)
CPP_UNITS_DECLARE(millimetres, mm)

}

}
