#pragma once
#include <type_traits>

namespace concepts {
    template<typename T>
    concept Iterable = requires(T& t) {
        t.begin();
        t.end();
        t.begin() != t.end();
        ++std::declval<decltype(t.begin())&>();  // increment ++
        *t.begin();
    };

    template<typename T>
    concept is_string = std::is_same<T, std::string>::value || std::is_same<T, const char*>::value;

    template<typename T>
    concept is_vector = requires {
        typename T::value_type;
        typename T::allocator_type;
        requires std::same_as<T, std::vector<typename T::value_type, typename T::allocator_type>>;
    };

    template<typename T>
    concept is_map = requires {
        typename T::key_type;
        typename T::mapped_type;
        requires std::same_as<T, std::map<typename T::key_type, typename T::mapped_type, typename T::key_compare, typename T::allocator_type>>;
    };

    template<typename T>
    concept is_unordered_map = requires {
        typename T::key_type;
        typename T::mapped_type;
        typename T::hasher;
        typename T::key_equal;
        typename T::allocator_type;
        requires std::same_as<T, std::unordered_map<typename T::key_type, typename T::mapped_type, typename T::hasher, typename T::key_equal, typename T::allocator_type>>;
    };
}