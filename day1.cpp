#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "day1.hpp"

/* 
Input:
3   4
4   3
2   5
1   3
3   9
3   3
Pair smallest left with smallest right
Pair second smallest left with second smallest right
...
Get distance between pairs
Sum all distances
*/

void readInput(std::vector<int>& v1, std::vector<int>& v2) {
	std::ifstream file("day1Input.txt");
	std::string line;
	while (std::getline(file, line)) {
		std::cout << line << std::endl;
		std::size_t pos = line.find(" ");
		v1.push_back(std::stoi(line.substr(0, pos)));
		v2.push_back(std::stoi(line.substr(pos + 1)));
	}
	std::cout << "Done reading input" << std::endl;
	file.close();
}

int calculateSimilarity(std::vector<int>& leftList, std::vector<int>& rightList) {
	int sum = 0;
	for (int leftNumber : leftList) {
		sum += leftNumber * std::count(rightList.begin(), rightList.end(), leftNumber);
	}
	return sum;
}

void day1() {
	std::vector<int> leftList;
	std::vector<int> rightList;
	readInput(leftList, rightList);

	std::sort(leftList.begin(), leftList.end());
	std::sort(rightList.begin(), rightList.end());

	std::cout << leftList.size() << " " << rightList.size() << std::endl;
	std::cout << leftList[0] << " " << rightList[0] << std::endl;

	int sum = 0;
	for (int i = 0; i < leftList.size(); i++) {
		sum += abs(leftList[i] - rightList[i]);
	}

	std::cout << "Sum of distances: " << sum << std::endl;
	std::cout << "Similarity: " << calculateSimilarity(leftList, rightList) << std::endl;
}

