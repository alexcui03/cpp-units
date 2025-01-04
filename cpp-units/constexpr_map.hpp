/**
 * This file is part of C++ Units.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <type_traits>

namespace cpp_units::utils {

// type-traits for constexpr_pair and constexpr_map

// same_pair_key<Pair1, Pair2> -> check if Pair1 and Pair2 has same key type and key.
template <typename Pair1, typename Pair2>
struct is_same_pair_key {
    static constexpr bool value = Pair1::key == Pair2::key;
};

template <typename Pair1, typename Pair2>
constexpr bool is_same_pair_key_v = is_same_pair_key<Pair1, Pair2>::value;

// same_pair<Pair1, Pair2> -> check if Pair1 and Pair2 has same type and same key-value.
template <typename Pair1, typename Pair2>
struct is_same_pair {
    static constexpr bool value = Pair1::key == Pair2::key && Pair1::value == Pair2::value;
};

template <typename Pair1, typename Pair2>
constexpr bool is_same_pair_v = is_same_pair<Pair1, Pair2>::value;

// unique_key_in_pair_list<Pair, Rest...> -> check if Pair is not in Rest.
template <typename Pair, typename... Rest>
struct is_unique_key_in_pair_list {
    static constexpr bool value = true;
};

template <typename Pair, typename Pair2, typename... Rest>
struct is_unique_key_in_pair_list<Pair, Pair2, Rest...>: is_unique_key_in_pair_list<Pair, Rest...> {
    static constexpr bool value = !is_same_pair_key_v<Pair, Pair2> && is_unique_key_in_pair_list<Pair, Rest...>::value;
};

template <typename Pair, typename... Rest>
constexpr bool is_unique_key_in_pair_list_v = is_unique_key_in_pair_list<Pair, Rest...>::value;

// NonEmptyConstexprMap<Map> -> check if Map::next exists.
template <typename Map>
concept NonEmptyConstexprMap = requires {
    typename Map::next;
};

// pair_in_map<Pair, Map> -> check if Map contains Pair.
template <typename Pair, typename Map>
struct is_pair_in_map {
    static constexpr bool value = false;
};

template <typename Pair, NonEmptyConstexprMap Map>
struct is_pair_in_map<Pair, Map>: is_pair_in_map<Pair, typename Map::next> {
    static constexpr bool value = is_same_pair_v<Pair, typename Map::pair> || is_pair_in_map<Pair, typename Map::next>::value;
};

template <typename Pair, typename Map>
constexpr bool is_pair_in_map_v = is_pair_in_map<Pair, Map>::value;

// map_contains<Map1, Map2> -> check if all Pairs in Map1 are in Map2.
template <typename Map1, typename Map2>
struct is_map_contains {
    static constexpr bool value = true;
};

template <NonEmptyConstexprMap Map1, typename Map2>
struct is_map_contains<Map1, Map2>: is_map_contains<typename Map1::next, Map2> {
    static constexpr bool value = is_pair_in_map_v<typename Map1::pair, Map2> && is_map_contains<typename Map1::next, Map2>::value;
};

template <typename Map1, typename Map2>
constexpr bool is_map_contains_v = is_map_contains<Map1, Map2>::value;

// same_map<Map1, Map2> -> check if Map1 and Map2 are the same map.
template <typename Map1, typename Map2>
struct is_same_map {
    static constexpr bool value = is_map_contains_v<Map1, Map2> && is_map_contains_v<Map2, Map1>;
};

template <typename Map1, typename Map2>
constexpr bool is_same_map_v = is_same_map<Map1, Map2>::value;

// definition of constexpr_pair

template <auto Key, auto Value>
struct constexpr_pair {
    using key_type = decltype(Key);
    using value_type = decltype(Value);
    static constexpr key_type key = Key;
    static constexpr value_type value = Value;
};

// definition of constexpr_map

template <typename... Pairs>
struct constexpr_map;

template <>
struct constexpr_map<> {
    template <auto Key>
    struct has {
        static constexpr auto value = false;
    };

    template <auto Key>
    static constexpr bool has_v = has<Key>::value;
};

template <typename Pair, typename... Rest>
struct constexpr_map<Pair, Rest...>: constexpr_map<Rest...> {};

template <typename Pair, typename... Rest>
requires is_unique_key_in_pair_list_v<Pair, Rest...>
struct constexpr_map<Pair, Rest...>: constexpr_map<Rest...> {
    using pair = Pair;
    using next = constexpr_map<Rest...>;

    // has<Key>
    template <auto Key>
    struct has {
        static constexpr bool value = Pair::key == Key || next::template has<Key>::value;
    };

    template <auto Key>
    static constexpr bool has_v = has<Key>::value;

    // get<Key>
    template <auto Key>
    struct get {
        static constexpr auto value = next::template get<Key>::value;
    };

    template <auto Key>
    requires (Pair::key == Key)
    struct get<Key> {
        static constexpr Pair::value_type value = Pair::value;
    };

    template <auto Key>
    static constexpr auto get_v = get<Key>::value;

    // set<Key, Value> -> map
    template <auto Key, auto Value>
    struct set {
        using type = constexpr_map<Pair, Rest..., constexpr_pair<Key, Value>>;
    };

    template <auto Key, auto Value>
    using set_t = set<Key, Value>::type;
};

}
