#include <print>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <fstream>
#include <string>
#include <tuple>
#include <ranges>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include "santasHelper.hpp"

void print_map(std::map<int, std::vector<int>>& map) {
        for (auto [key, values] : map) {
        std::print("{}: ", key);
        for (auto v : values) std::print("{} ", v);
        std::println();
    }
}

void get_rules(std::ifstream& myfile, std::unordered_map<int, std::vector<int>>& rules) {
    std::string line;
    while (std::getline(myfile, line) && line != "" ) {
        int key = stoi(line.substr(0, 2));
        int value = stoi(line.substr(3, 2));
        rules[key].push_back(value);
    }
}

void get_pages(std::ifstream& myfile, std::vector<std::vector<int>>& pages) {
    std::string line;
    int page_line = 0;
    while (std::getline(myfile, line)) {
        pages.push_back(std::vector<int>());
        for (int i = 0; i < line.size(); i+=3) {
            pages[page_line].push_back(stoi(line.substr(i, 2)));
        }
        page_line++;
    }
}

std::tuple<std::unordered_map<int, std::vector<int>>, std::vector<std::vector<int>>> readInput(std::string input) {
    std::ifstream myfile(input);
    std::unordered_map<int, std::vector<int>> rules;  // unordered_map for faster access
    std::vector<std::vector<int>> pages;
    get_rules(myfile, rules);
    get_pages(myfile, pages);
    myfile.close();
    return std::tuple(rules, pages);
}

void order_pages_part_b(std::map<int, std::vector<int>>& rules, std::vector<std::vector<int>>& invalid_pages) {
    // maybe some day :)
}

void check_pages(std::unordered_map<int, std::vector<int>>& rules, std::vector<std::vector<int>>& pages) {
    int result = 0;
    std::vector<std::vector<int>> invalid_pages;

    for (std::vector<int> line : pages) {
        // check each page line
        for (auto [i, val] : std::ranges::enumerate_view(line)) {
            // generate a view of the line vector, where all values before i are taken
            auto previous_nmbrs = line | std::views::take(i);

            // Check if any of the rule list numbers is in the previous numbers
            bool contains_any = std::ranges::any_of(rules[val], [&](int x) {return std::find(previous_nmbrs.begin(), previous_nmbrs.end(), x) != previous_nmbrs.end();});
            if (contains_any) {
                // page invalid, go to next line
                invalid_pages.push_back(line);
                break;
            }
            // page valid
            if (i == line.size() - 1) {
                int middle = line.size() / 2;
                result += line[middle];
            }
        }
    }
    std::println("Result part a: {}", result);
    //order_pages_part_b(rules, invalid_pages);
}


int main () {
    std::println("{}", "######### Day 5 ##########");
    SantasHelper santasHelper;
    std::string dir = getcwd(NULL, 0);     
    auto [rules, pages] = readInput(dir + "/inputs/day5Input.txt");

    santasHelper.print(rules);
    santasHelper.print(pages);

    check_pages(rules, pages);
}

