/**
 * This file is part of C++ Units.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <string>

namespace cpp_units {

template <char Symbol>
struct dimension {
    static const char symbol = Symbol;
};

}
