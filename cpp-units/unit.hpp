/**
 * This file is part of C++ Units.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <ratio>
#include <type_traits>

#include "utils/utils.hpp"
#include "dimension.hpp"

namespace cpp_units {

template <typename Dimension, typename Type, typename Ratio = std::ratio<1, 1>>
class unit {
    Type _value;
public:
    using dimension = Dimension;
    using type = Type;
    using ratio = Ratio;

    constexpr unit() = default;
    explicit constexpr unit(const Type &value): _value(value) {}
    explicit constexpr unit(Type &&value): _value(value) {}
    constexpr unit(const unit &type) = default;
    constexpr unit(unit &&type) = default;

    // Specialization for dimensionless quantity.
    constexpr unit(const Type &value) requires is_same_dimension_v<Dimension, dimensionless>: _value(value) {}
    constexpr unit(Type &&value) requires is_same_dimension_v<Dimension, dimensionless>: _value(value) {}
    constexpr operator Type() const requires is_same_dimension_v<Dimension, dimensionless> { return _value; }

    constexpr inline Type value() const { return _value; }

    constexpr unit<Dimension, Type, Ratio> operator+() const {
        return unit<Dimension, Type, Ratio>(+_value);
    }

    constexpr unit<Dimension, Type, Ratio> operator-() const {
        return unit<Dimension, Type, Ratio>(-_value);
    }
};

// Operators
template <typename Dim1, typename Type1, typename Ratio1, typename Dim2, typename Type2, typename Ratio2>
requires is_same_dimension_v<Dim1, Dim2>
constexpr auto operator+(const unit<Dim1, Type1, Ratio1> &lhs, const unit<Dim2, Type2, Ratio2> &rhs) {
    using CommonRatio = utils::common_ratio_t<Ratio1, Ratio2>;
    using CommonType = std::common_type_t<Type1, Type2>;
    using Divide1 = std::ratio_divide<Ratio1, CommonRatio>;
    using Divide2 = std::ratio_divide<Ratio2, CommonRatio>;
    return unit<Dim1, CommonType, CommonRatio>(
        static_cast<CommonType>(lhs.value()) * Divide1::num / Divide1::den +
        static_cast<CommonType>(rhs.value()) * Divide2::num / Divide2::den
    );
}

template <typename Dim1, typename Type1, typename Ratio1, typename Dim2, typename Type2, typename Ratio2>
requires is_same_dimension_v<Dim1, Dim2>
constexpr auto operator-(const unit<Dim1, Type1, Ratio1> &lhs, const unit<Dim2, Type2, Ratio2> &rhs) {
    using CommonRatio = utils::common_ratio_t<Ratio1, Ratio2>;
    using CommonType = std::common_type_t<Type1, Type2>;
    using Divide1 = std::ratio_divide<Ratio1, CommonRatio>;
    using Divide2 = std::ratio_divide<Ratio2, CommonRatio>;
    return unit<Dim1, CommonType, CommonRatio>(
        static_cast<CommonType>(lhs.value()) * Divide1::num / Divide1::den -
        static_cast<CommonType>(rhs.value()) * Divide2::num / Divide2::den
    );
}

template <typename Dim1, typename Type1, typename Ratio1, typename Dim2, typename Type2, typename Ratio2>
constexpr auto operator*(const unit<Dim1, Type1, Ratio1> &lhs, const unit<Dim2, Type2, Ratio2> &rhs) {
    using CommonType = std::common_type_t<Type1, Type2>;
    return unit<dimension_multiply_t<Dim1, Dim2>, CommonType, std::ratio_multiply<Ratio1, Ratio2>>(
        static_cast<CommonType>(lhs.value()) * static_cast<CommonType>(rhs.value())
    );
}

template <typename Dim1, typename Type1, typename Ratio1, typename Dim2, typename Type2, typename Ratio2>
constexpr auto operator/(const unit<Dim1, Type1, Ratio1> &lhs, const unit<Dim2, Type2, Ratio2> &rhs) {
    using CommonType = std::common_type_t<Type1, Type2>;
    return unit<dimension_divide_t<Dim1, Dim2>, CommonType, std::ratio_divide<Ratio1, Ratio2>>(
        static_cast<CommonType>(lhs.value()) / static_cast<CommonType>(rhs.value())
    );
}

// Operators for dimensionless quantities.
template <typename Dim, typename Type, typename Ratio, typename ValueType>
requires is_same_dimension_v<Dim, dimensionless>
inline constexpr auto operator+(const unit<Dim, Type, Ratio> &lhs, const ValueType &rhs) {
    return lhs + unit<dimensionless, ValueType>(rhs);
}

template <typename Dim, typename Type, typename Ratio, typename ValueType>
requires is_same_dimension_v<Dim, dimensionless>
inline constexpr auto operator+(const ValueType &lhs, const unit<Dim, Type, Ratio> &rhs) {
    return unit<dimensionless, ValueType>(lhs) + rhs;
}

template <typename Dim, typename Type, typename Ratio, typename ValueType>
requires is_same_dimension_v<Dim, dimensionless>
inline constexpr auto operator-(const unit<Dim, Type, Ratio> &lhs, const ValueType &rhs) {
    return lhs - unit<dimensionless, ValueType>(rhs);
}

template <typename Dim, typename Type, typename Ratio, typename ValueType>
requires is_same_dimension_v<Dim, dimensionless>
inline constexpr auto operator-(const ValueType &lhs, const unit<Dim, Type, Ratio> &rhs) {
    return unit<dimensionless, ValueType>(lhs) - rhs;
}

template <typename Dim, typename Type, typename Ratio, typename ValueType>
inline constexpr auto operator*(const unit<Dim, Type, Ratio> &lhs, const ValueType &rhs) {
    return lhs * unit<dimensionless, ValueType>(rhs);
}

template <typename Dim, typename Type, typename Ratio, typename ValueType>
inline constexpr auto operator*(const ValueType &lhs, const unit<Dim, Type, Ratio> &rhs) {
    return unit<dimensionless, ValueType>(lhs) * rhs;
}

template <typename Dim, typename Type, typename Ratio, typename ValueType>
inline constexpr auto operator/(const unit<Dim, Type, Ratio> &lhs, const ValueType &rhs) {
    return lhs / unit<dimensionless, ValueType>(rhs);
}

template <typename Dim, typename Type, typename Ratio, typename ValueType>
inline constexpr auto operator/(const ValueType &lhs, const unit<Dim, Type, Ratio> &rhs) {
    return unit<dimensionless, ValueType>(lhs) / rhs;
}

}
