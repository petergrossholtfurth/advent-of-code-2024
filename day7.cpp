#include "santasHelper.hpp"
#include <string>
#include <unistd.h>
#include <map>
#include <vector>
#include <fstream>

SantasHelper santasHelper{};

std::map<int, std::vector<int>> read_input(std::string path) {
    std::ifstream myfile(path);
    std::map<int, std::vector<int>> map;
    std::string line;
    while (std::getline(myfile, line)) {
        auto idx = line.find(':');
        int key = stoi(line.substr(0, idx));
        std::vector<int> values;
        map[key] = values;
    }
    return map;
}

int main () {
    std::println("{}", "######### Day 7 ##########");
    std::string dir{getcwd(NULL, 0)};     
    auto map = read_input(dir + "/inputs/testInput.txt");
    santasHelper.print(map);
}