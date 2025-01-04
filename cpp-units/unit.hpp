/**
 * This file is part of C++ Units.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <ratio>
#include <type_traits>

#include "utils.hpp"

namespace cpp_units {

template <typename Dimension, typename Type, typename Ratio = std::ratio<1, 1>>
class unit {
    Type _value;
public:
    using type = Type;
    using ratio = Ratio;

    constexpr unit() = default;
    explicit constexpr unit(const Type &value): _value(value) {};
    explicit constexpr unit(Type &&value): _value(value) {};
    constexpr unit(const unit &type) = default;
    constexpr unit(unit &&type) = default;

    constexpr Type value() const { return _value; }

    constexpr unit<Dimension, Type, Ratio> operator+() const {
        return unit<Dimension, Type, Ratio>(+_value);
    }

    constexpr unit<Dimension, Type, Ratio> operator-() const {
        return unit<Dimension, Type, Ratio>(-_value);
    }

    template <typename OtherType, typename OtherRatio>
    constexpr unit<Dimension, std::common_type_t<Type, OtherType>, utils::common_ratio_t<Ratio, OtherRatio>>
        operator+(const unit<Dimension, OtherType, OtherRatio> &rhs) const {
        using CommonRatio = utils::common_ratio_t<Ratio, OtherRatio>;
        using Result = unit<Dimension, std::common_type_t<Type, OtherType>, CommonRatio>;
        using Divide1 = std::ratio_divide<Ratio, CommonRatio>;
        using Divide2 = std::ratio_divide<OtherRatio, CommonRatio>;
        return Result(_value * Divide1::num / Divide1::den + rhs.value() * Divide2::num / Divide2::den);
    }

    template <typename OtherType, typename OtherRatio>
    constexpr unit<Dimension, std::common_type_t<Type, OtherType>, std::common_ratio_t<Ratio, OtherRatio>>
        operator-(const unit<Dimension, OtherType, OtherRatio> &rhs) const {
        using CommonRatio = std::common_ratio_t<Ratio, OtherRatio>;
        using Result = unit<Dimension, std::common_type_t<Type, OtherType>, CommonRatio>;
        using Divide1 = std::ratio_divide<Ratio, CommonRatio>;
        using Divide2 = std::ratio_divide<OtherRatio, CommonRatio>;
        return Result(_value * Divide1::num / Divide1::den - rhs.value() * Divide2::num / Divide2::den);
    }
};

}
