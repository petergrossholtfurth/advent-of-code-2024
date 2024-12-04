#include <iostream>
#include "day3.hpp"
#include <fstream>
#include <string>

/*
xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))
find the multiplications with mul(X,Y) and calculate the result
X and Y can be between 1 and 3 digits
*/


void day3() {
	std::string line;
	std::ifstream myfile("day3Input.txt");
	long long int result = 0;
	size_t pos = 0;
	size_t lastDoOrDontPos = 2;  // 0 nothing, 1 dont, 2 do

	while (std::getline(myfile, line)) {
		pos = line.find("mul(");
		while (pos != std::string::npos) {
			// mul(123,12  3  )
			// 0123456789 10 11
			// pos = 0
			// comma = 7
			// close = 11

			size_t comma = line.find(",", pos);

			if ((comma - (pos + 4)) > 3) {
				pos = line.find("mul(", pos + 4);
				continue; // number too long
			}
			else {
				std::string first = line.substr(pos + 4, comma - (pos + 4));
				size_t close = line.find(")", comma);
				if ((close - (comma + 1)) > 3) {
					pos = line.find("mul(", pos + 4);
					continue; // number too long
				} 
				else {
					// Found correct mul
					// check most recent do() or don't()
					size_t doPos = line.rfind("do()", pos);
					size_t dontPos = line.rfind("don't()", pos);

					if (doPos != std::string::npos) {
						// found do
						if (dontPos != std::string::npos) {
							// Found both, check which was last
							if (doPos > dontPos) {
								lastDoOrDontPos = 2; // do
							}
							else {
								lastDoOrDontPos = 1; // dont
							}
						}
						else {
							// Only found do
							lastDoOrDontPos = 2; // do
						}
					}
					else {
						// no doPos found
						if (dontPos != std::string::npos) {
							// but dontPos found
							lastDoOrDontPos = 1;
						}
						else {
							// nothing found, store last value, i.e. dont update variable
						}
					}
					
					if (lastDoOrDontPos == 2) {
						std::string second = line.substr(comma + 1, close - (comma + 1));
						int firstNum = std::stoi(first);
						int secondNum = std::stoi(second);
						result += firstNum * secondNum;
					}
				}
			}
			pos = line.find("mul(", pos + 4);
		}
	}

	myfile.close();
	std::cout << "Result: " << result << std::endl;
}