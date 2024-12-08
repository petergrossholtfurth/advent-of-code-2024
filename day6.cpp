#include "santasHelper.hpp"
#include <print>
#include <vector>
#include <unistd.h>
#include <fstream>
#include <ranges>

SantasHelper santasHelper = SantasHelper();

std::vector<std::vector<char>> read_input(std::string path) {
    std::ifstream myfile(path);

    std::vector<std::vector<char>> map;

    if (myfile.is_open()) {
        std::string line;
        while (getline(myfile, line)) {
            std::vector<char> row;
            for (char c : line) {
                row.push_back(c);
            }
            map.push_back(row);
        }
    }

    myfile.close();
    return map;
}

void count_distinct_positions(std::vector<std::vector<char>> map) {
    int y{0}, x{0}, count{0};
    std::string direction{"up"};
    // The maximum values y and x can have
    int max_y = map.size() - 1;
    int max_x = map[0].size() - 1;
    // Find starting position
    for (auto [i, v] : map | std::views::enumerate) {
        for (auto [j, ele] : v | std::views::enumerate) {
            if (ele == '^') {
                y = i; x = j;
            }
        }
    }

    while (true) {
        if (direction == "up") {
            if (y == 0) {
                break;
            }
            if (map[y-1][x] == '#') {
                direction = "right";
            } else if (map[y-1][x] == '.' || map[y-1][x] == 'x') {
                // mark as visited
                map[y][x] = 'x';
                // move one up, x stays the same
                map[--y][x] = '^';
            }
        }
        else if (direction == "right") {
            if (x == max_x) {
                break;
            }
            if (map[y][x+1] == '#') {
                direction = "down";
            } else if (map[y][x+1] == '.' || map[y][x+1] == 'x') {
                // mark as visited
                map[y][x] = 'x';
                // move one right, y stays the same
                map[y][++x] = '>';
            }
        }
        else if (direction == "down") {
            if (y == max_y) {
                break;
            }
            if (map[y+1][x] == '#') {
                direction = "left";
            } else if (map[y+1][x] == '.' || map[y+1][x] == 'x') {
                // mark as visited
                map[y][x] = 'x';
                // move one down, x stays the same
                map[++y][x] = 'v';
            }
        }
        else if (direction == "left") {
            if (x == 0) {
                break;
            }
            if (map[y][x-1] == '#') {
                direction = "up";
            } else if (map[y][x-1] == '.' || map[y][x-1] == 'x') {
                // mark as visited
                map[y][x] = 'x';
                // move one left, y stays the same
                map[y][--x] = '<';
            }
        }
    }

    for (auto v : map) {
        for (auto ele : v) {
            if (ele == 'x') {
                count++;
            }
        }
    }
    
    santasHelper.print(map);

    // add last position as we don't mark it as visited but leave the loop
    count++;

    std::println("Count: {}", count);

}



int main () {
    std::println("{}", "######### Day 6 ##########");
    std::string dir{getcwd(NULL, 0)};     
    auto map = read_input(dir + "/inputs/day6Input.txt");

    count_distinct_positions(map);
}