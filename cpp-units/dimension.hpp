/**
 * This file is part of C++ Units.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "constexpr_map.hpp"

namespace cpp_units {

// is_dimension_contains<Dimension1, Dimension2> -> check if all Pairs in Dimension1 are in Dimension1, except zeros.
template <typename Dimension1, typename Dimension2>
struct is_dimension_contains {
    static constexpr bool value = true;
};

template <utils::NonEmptyConstexprMap Dimension1, typename Dimension2>
struct is_dimension_contains<Dimension1, Dimension2>: is_dimension_contains<typename Dimension1::next, Dimension2> {
    static constexpr bool value = Dimension1::pair::value == 0 ||
        (utils::is_pair_in_map_v<typename Dimension1::pair, Dimension2> && is_dimension_contains<typename Dimension1::next, Dimension2>::value);
};

template <typename Dimension1, typename Dimension2>
constexpr bool is_dimension_contains_v = is_dimension_contains<Dimension1, Dimension2>::value;

// is_same_dimension<Dimension1, Dimension2> -> check if Dimension1 and Dimension2 are same.
template <typename Dimension1, typename Dimension2>
struct is_same_dimension {
    static constexpr bool value = is_dimension_contains_v<Dimension1, Dimension2>
        && is_dimension_contains_v<Dimension2, Dimension1>;
};

template <typename Dimension1, typename Dimension2>
constexpr bool is_same_dimension_v = is_same_dimension<Dimension1, Dimension2>::value;

// dimension_multiply<Dimension1, Dimension2> -> get Dimension1 * Dimension2.
template <typename Dimension1, typename Dimension2>
struct dimension_multiply {
    using type = Dimension1;
};

template <typename Dimension1, utils::NonEmptyConstexprMap Dimension2>
requires (!Dimension1::template has_v<Dimension2::pair::key>)
struct dimension_multiply<Dimension1, Dimension2>: dimension_multiply<Dimension1, typename Dimension2::next> {
    using type = dimension_multiply<Dimension1, typename Dimension2::next>::type::template set_t<Dimension2::pair::key, Dimension2::pair::value>;
};

template <typename Dimension1, utils::NonEmptyConstexprMap Dimension2>
requires Dimension1::template has_v<Dimension2::pair::key>
struct dimension_multiply<Dimension1, Dimension2>: dimension_multiply<Dimension1, typename Dimension2::next> {
    using type = dimension_multiply<Dimension1, typename Dimension2::next>::type::template set_t<Dimension2::pair::key,
        dimension_multiply<Dimension1, typename Dimension2::next>::type::template get_v<Dimension2::pair::key> + Dimension2::pair::value>;
};

template <typename Dimension1, typename Dimension2>
using dimension_multiply_t = dimension_multiply<Dimension1, Dimension2>::type;

// dimension_divide<Dimension1, Dimension2> -> get Dimension1 / Dimension2.
template <typename Dimension1, typename Dimension2>
struct dimension_divide {
    using type = Dimension1;
};

template <typename Dimension1, utils::NonEmptyConstexprMap Dimension2>
requires (!Dimension1::template has_v<Dimension2::pair::key>)
struct dimension_divide<Dimension1, Dimension2>: dimension_divide<Dimension1, typename Dimension2::next> {
    using type = dimension_multiply<Dimension1, typename Dimension2::next>::type::template set_t<Dimension2::pair::key, -Dimension2::pair::value>;
};

template <typename Dimension1, utils::NonEmptyConstexprMap Dimension2>
requires Dimension1::template has_v<Dimension2::pair::key>
struct dimension_divide<Dimension1, Dimension2>: dimension_divide<Dimension1, typename Dimension2::next> {
    using type = dimension_divide<Dimension1, typename Dimension2::next>::type::template set_t<Dimension2::pair::key,
        dimension_divide<Dimension1, typename Dimension2::next>::type::template get_v<Dimension2::pair::key> - Dimension2::pair::value>;
};

template <typename Dimension1, typename Dimension2>
using dimension_divide_t = dimension_divide<Dimension1, Dimension2>::type;

template <int Symbol>
struct dimension: utils::constexpr_map<utils::constexpr_pair<Symbol, 1>> {};

using dimensionless = dimension_divide_t<dimension<0>, dimension<0>>;

}
