#include "santasHelper.hpp"
#include <print>
#include <vector>
#include <type_traits>
#include "concepts.hpp"
#include <string>

// All template functions need to be defined in the header file
// to make templates instantiable

template<typename T>
void SantasHelper::print(T t) {
    if constexpr (concepts::is_map<T>) {
        SantasHelper::print_map(t);
    } else if constexpr (concepts::is_unordered_map<T>) {
        SantasHelper::print_unordered_map(t);
    } else if constexpr (concepts::is_vector<T>) {
        SantasHelper::print_vector(t);
    } else if constexpr (concepts::is_simple_printable<T>) {
        std::println("{}", t);
    } else {
        std::println("Type not supported");
    }
}


// ---------------------------------------------------------------------------------------

template<typename T1, typename T2>
void SantasHelper::print_map(std::map<T1, T2> m) {
    constexpr bool is_iterable = concepts::Iterable<T2>;
    if constexpr (is_iterable) {
        SantasHelper::print_map_with_iterable_value(m);
    } else {
        SantasHelper::print_map_with_val_to_val(m);
    }
}

template<typename T1, typename T2>
void SantasHelper::print_unordered_map(std::unordered_map<T1, T2> m) {
    constexpr bool is_iterable = concepts::Iterable<T2>;
    std::map<T1, T2> map(m.begin(), m.end());  // convert unordered_map to map to be able to use the same print function
    if constexpr (is_iterable) {
        SantasHelper::print_map_with_iterable_value(map);
    } else {
        SantasHelper::print_map_with_val_to_val(map);
    }
}

template<typename T>
void SantasHelper::print_vector(std::vector<T> v) {
    // constexpr important so that the compiler can evaluate the if statement at compile time
    if constexpr (std::is_same<T, std::string>::value || std::is_same<T, const char*>::value) {
        SantasHelper::print_string_vector(v);
        return;
    }
    if constexpr (concepts::Iterable<T>) {
        SantasHelper::print_2d_vector(v);
    } else {
        SantasHelper::print_1d_vector(v);
    }
}

template<typename T1, concepts::Iterable T2>
// requires concepts::Iterable<T2> is just the same as if we define the type of T2 like above
void SantasHelper::print_map_with_iterable_value(std::map<T1, T2> m) {
    for (auto [key, values] : m) {
        std::print("{}: ", key);
        for (auto v : values) std::print("{} ", v);
        std::println();
    }
}

template<typename T>
void SantasHelper::print_map_with_val_to_val(std::map<T, T> m) {
    for (auto [key, value] : m) {
        std::print("{}: {}\n", key, value);
    }
}

template <typename T>
void SantasHelper::print_1d_vector(std::vector<T> v) {
    for (auto i : v) {
        std::print("{} ", i);
    }
    std::println();
}

template<typename T>
requires concepts::Iterable<T>
void SantasHelper::print_2d_vector(std::vector<T> v) {
    // Don't print spaces between characters if the vector contains characters
    if constexpr (std::is_same<T, std::vector<char>>::value) {
        for (const auto& i : v) {
            for (const auto& j : i) {
                std::print("{}", j);
            }
        std::println();
        }
    }
    else {
        for (const auto& i : v) {
            for (const auto& j : i) {
                std::print("{} ", j);
            }
            std::println();
        }
    }
}

template<typename T>
requires concepts::is_string<T>
void SantasHelper::print_string_vector(std::vector<T> v) {
    for (auto i : v) {
        std::print("{}", i);
    }
    std::println();
}