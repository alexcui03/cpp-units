/**
 * This file is part of C++ Units.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "constexpr_map.hpp"

namespace cpp_units {

template <int Symbol>
struct dimension: utils::constexpr_map<utils::constexpr_pair<Symbol, 1>> {};

template <typename Dimension1, typename Dimension2>
struct is_same_dimension {
    static constexpr bool value = utils::is_same_map_v<Dimension1, Dimension2>;
};

template <typename Dimension1, typename Dimension2>
constexpr bool is_same_dimension_v = is_same_dimension<Dimension1, Dimension2>::value;

template <typename Dimension1, typename Dimension2>
struct dimension_multiply {
    using type = Dimension2;
};

template <utils::NonEmptyConstexprMap Dimension1, typename Dimension2>
requires (!Dimension2::template has_v<Dimension1::pair::key>)
struct dimension_multiply<Dimension1, Dimension2>: dimension_multiply<typename Dimension1::next, Dimension2> {
    using type = dimension_multiply<typename Dimension1::next, Dimension2>::type::template set_t<Dimension1::pair::key, Dimension1::pair::value>;
};

template <utils::NonEmptyConstexprMap Dimension1, typename Dimension2>
requires Dimension2::template has_v<Dimension1::pair::key>
struct dimension_multiply<Dimension1, Dimension2>: dimension_multiply<typename Dimension1::next, Dimension2> {
    using type = dimension_multiply<typename Dimension1::next, Dimension2>::type::template set_t<Dimension1::pair::key,
        dimension_multiply<typename Dimension1::next, Dimension2>::type::template get_v<Dimension1::pair::key> + Dimension1::pair::value>;
};

template <typename Dimension1, typename Dimension2>
using dimension_multiply_t = dimension_multiply<Dimension1, Dimension2>::type;

}
