#pragma once
#include <vector>
#include <map>
#include "concepts.hpp"

class SantasHelper {
    public: 
        // Constructor
        SantasHelper();
        // Destructor
        ~SantasHelper();
        // Copy Constructor
        SantasHelper(const SantasHelper &santasHelper);
        // Move Constructor
        SantasHelper(SantasHelper &&santasHelper);
        // Copy Assignment Operator
        SantasHelper& operator=(const SantasHelper &santasHelper);
        // Move Assignment Operator
        SantasHelper& operator=(SantasHelper &&santasHelper);

        template<typename T>
        void print(T t);

private:
        template<typename T1, typename T2>
        void print_map(std::map<T1, T2> m);

        template<typename T1, typename T2>
        void print_unordered_map(std::unordered_map<T1, T2> m);

        template<typename T>
        void print_vector(std::vector<T> v);

        template<typename T1, typename T2>
        requires concepts::Iterable<T2>
        void print_map_with_iterable_value(std::map<T1, T2> m);

        template<typename T>
        void print_map_with_val_to_val(std::map<T, T> m);

        template<typename T>
        void print_1d_vector(std::vector<T> v);

        template<typename T>
        requires concepts::Iterable<T>
        void print_2d_vector(std::vector<T> v);

        template<typename T>
        requires concepts::is_string<T>
        void print_string_vector(std::vector<T> v);


};

// Template definitions need to be in the header file
#include "santasHelper.cpp"

