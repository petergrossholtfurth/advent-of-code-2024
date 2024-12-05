#include "day2.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

/*
Input
7 6 4 2 1
1 2 7 8 9
9 7 6 2 1
1 3 2 4 5
8 6 4 4 1
1 3 6 7 9

Safe Reports:
The levels are either all increasing or all decreasing.
Any two adjacent levels differ by at least one and at most three.

How many reports are safe?
*/

void readInput(std::vector<std::vector<int>>& input) {
	std::ifstream file("day2Input.txt");
	std::string line;
	while (std::getline(file, line)) {
		// how can i read the line and split it into numbers?
		std::vector<int> numbers;
		std::string number;
		for (int i = 0; i <= line.size(); i++) {
			if ((line[i] == ' ' || i == line.size()) && !number.empty()) {
				numbers.push_back(std::stoi(number));
				number = "";
			}
			else {
				number += line[i];
			}
		}
		input.push_back(numbers);
	}
	file.close();
}

void day2() {
	std::vector<std::vector<int>> input;
	readInput(input);
	
	int safeReports = 0;

	for (auto& v : input) { 
		int lastDirection = -1;
		bool isUnsafe = false;
		for (int i = 1; i < v.size(); i++) {
			int distance = v[i - 1] - v[i];
			if (distance == 0) {
				isUnsafe = true;
				break; // unsafe report
			}
			if (distance <= -1) {
				if (lastDirection == 0 || distance < -3) {
					isUnsafe = true;
					break;
				}
				// ascending report
				lastDirection = 1;
			}
			else if (distance >= 1) {
				if (lastDirection == 1 || distance > 3) {
					isUnsafe = true;
					break;
				}
				// descending report
				lastDirection = 0;
			}
			if (i == v.size() - 1) safeReports++;
		}
		if (isUnsafe) {
			isUnsafe = false;
			bool foundSafeReport = false;
			// Check if removing one level makes it safe
			for (int i = 0; i < v.size(); i++) {
				std::vector<int> temp = v;
				temp.erase(temp.begin() + i);
				int lastDirection = -1;
				bool isUnsafe = false;
				for (int i = 1; i < temp.size(); i++) {
					int distance = temp[i - 1] - temp[i];
					if (distance == 0) {
						break; // unsafe report
					}
					if (distance <= -1) {
						if (lastDirection == 0 || distance < -3) {
							break;
						}
						// ascending report
						lastDirection = 1;
					}
					else if (distance >= 1) {
						if (lastDirection == 1 || distance > 3) {
							break;
						}
						// descending report
						lastDirection = 0;
					}
					if (i == temp.size() - 1) {
						safeReports++;
						foundSafeReport = true;
						break;
					}
				}
				if (foundSafeReport) break;
			}
		}
	}

	std::cout << safeReports << std::endl;
}