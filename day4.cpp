#include <iostream>
#include <print>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#define LINE_LENGTH 140

/* IDEA 
Only use string find method to search for XMAS or reverse SAMX
Search left and right XMAS with searching those two strings
Search up and down by rotating matrix by 90 degree and search horizontally again
Search diagonally by rotating -45 and 45 degree and again search horizontally 

(
Matrix:
XMAS
SMAX
XMAM
XAMS
-> Horizontal matrix -45 degree
S
AX
MAM
XMAS -> found diagonal xmas 
SMM
XA
X

-> Horizontal matrix 45 degree
X
SM
XMA
XMAS -> found other diagonal xmas
AAX
MM
S	
)
*/

void printMatrix(const std::vector<std::vector<char>>& matrix) {
	for (const auto& row : matrix) {
		for (const auto& element : row) {
			std::cout << element;  // Print each character followed by a space
		}
		std::cout << std::endl;  // Move to the next line after each row
	}
	std::cout << std::endl;
}

std::vector<char> make_vector_from_line(std::string& line) {
	std::vector<char> v;
	for (int i = 0; i < line.length(); i++) {
		v.push_back(line[i]);
	}
	return v;
}

std::string make_line_from_vector(std::vector<char>& v) {
	return std::string(v.begin(), v.end());
}

void rotate90Clockwise(std::vector<std::vector<char>>& matrix) {
	int n = matrix.size();

	// Step 1: Transpose the matrix
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			std::swap(matrix[i][j], matrix[j][i]);
		}
	}

	// Step 2: Reverse each row
	for (int i = 0; i < n; ++i) {
		std::reverse(matrix[i].begin(), matrix[i].end());
	}
}

std::vector<std::vector<char>> rotate45Degrees(const std::vector<std::vector<char>>& matrix) {
	std::map<char, std::vector<char>> diagonals;

	// Traverse the matrix and group elements by diagonal
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix[i].size(); ++j) {
			diagonals[i + j].push_back(matrix[i][j]);
		}
	}

	// Store result
	std::vector<std::vector<char>> result;
	for (auto& diagonal : diagonals) {
		result.push_back(diagonal.second);
	}

	return result;
}

std::vector<std::vector<char>> rotateMinus45Degrees(const std::vector<std::vector<char>>& matrix) {
	std::map<int, std::vector<char>> diagonals;
	std::size_t n = matrix.size();
	std::size_t m = matrix[0].size();

	// Group elements by diagonal difference (i - j)
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			diagonals[i - j].push_back(matrix[i][j]);
		}
	}

	// Build the result in the original matrix
	std::vector<std::vector<char>> result;
	for (auto& diagonal : diagonals) {
		result.push_back(diagonal.second);
	}

	return result;
}

int count_number_of_occurences_of_XMAS_and_SMAX(std::string & line) {
	int xmas_counter = 0;
	std::string::size_type pos = 0;
	pos = line.find("XMAS", pos);
	while (pos != std::string::npos) {
		++xmas_counter;
		pos = line.find("XMAS", pos + 3);
	}
	pos = line.find("SAMX", 0);
	while (pos != std::string::npos) {
		++xmas_counter;
		pos = line.find("SAMX", pos + 3);
	}
	return xmas_counter;
}

int map_top_right(int li, int limin2, int pos) {
	int top_right_pos;
	if (limin2 < li) {
		top_right_pos = pos;
	}
	else if (limin2 == li) {
		top_right_pos = pos + 1;
	}
	else {
		top_right_pos = pos + 2;
	}
	return top_right_pos;
}

int map_bottom_left(int li, int liplus2, int pos) {
	int bottom_left_pos;
	if (liplus2 < li) {
		bottom_left_pos = pos;
	}
	else if (liplus2 == li) {
		bottom_left_pos = pos + 1;
	}
	else {
		bottom_left_pos = pos + 2;
	}
	return bottom_left_pos;
}

int find_xmas_part_b(std::vector<std::vector<char>>& matrix) {
	std::vector<std::vector<char>> rotatedMatrix = rotateMinus45Degrees(matrix);
	int xmas_counter = 0;
	std::string::size_type pos = 0;
	
	for (int i = 2; i < rotatedMatrix.size() - 2; i++) {
		pos = 0;
		std::string line = make_line_from_vector(rotatedMatrix[i]);
		pos = line.find("SAM");
		int len_of_line_i = line.length(); 
		int len_of_line_i_plus_2 = make_line_from_vector(rotatedMatrix[i+2]).length(); 
		int len_of_line_i_min_2 = make_line_from_vector(rotatedMatrix[i-2]).length(); 
		int bottom_left_pos;
		int top_right_pos;
		/* 
		.M.S
		..A.
		.M.S
		....
		Again rotated matrix
		S (line lenght 1)
		..
		MAS -> Found MAS (line length 3)
		Now map what the top right S and botom M indizes are, the can differ from the found pos because the line lengths are different
		*/

		while (pos != std::string::npos) {
			bottom_left_pos = map_bottom_left(len_of_line_i, len_of_line_i_plus_2, pos);
			top_right_pos = map_top_right(len_of_line_i, len_of_line_i_min_2, pos);

			if ((rotatedMatrix[i - 2][top_right_pos] == 'M' && rotatedMatrix[i + 2][bottom_left_pos] == 'S') ||
			(rotatedMatrix[i - 2][top_right_pos] == 'S' && rotatedMatrix[i + 2][bottom_left_pos] == 'M')) 
			 	xmas_counter++;
			
			pos = line.find("SAM", pos + 3);
		}

		pos = line.find("MAS");

		while (pos != std::string::npos) {
			bottom_left_pos = map_bottom_left(len_of_line_i, len_of_line_i_plus_2, pos);
			top_right_pos = map_top_right(len_of_line_i, len_of_line_i_min_2, pos);

			if ((rotatedMatrix[i - 2][top_right_pos] == 'M' && rotatedMatrix[i + 2][bottom_left_pos] == 'S') ||
			(rotatedMatrix[i - 2][top_right_pos] == 'S' && rotatedMatrix[i + 2][bottom_left_pos] == 'M')) 
				xmas_counter++;
			
			pos = line.find("MAS", pos + 3);
		}
	}

	return xmas_counter;
}


int main() {
	long int xmas_counter = 0;

	std::ifstream myfile("day4Input.txt");

	std::string line;
	std::vector<std::vector<char>> matrix;
	while (std::getline(myfile, line)) {
		matrix.push_back(make_vector_from_line(line));
	}
	
	// Find horizontal XMAS and SMAX
	for (int i = 0; i < LINE_LENGTH; i++) {
		std::string line = make_line_from_vector(matrix[i]);
		xmas_counter += count_number_of_occurences_of_XMAS_and_SMAX(line);
	};

	// Switch rows and columns (turn 90)
	std::vector<std::vector<char>> originalMatrix = matrix;
	rotate90Clockwise(matrix);
		
	// Find horizontal XMAS and SMAX, but now its basically the up and down of the original matrix
	for (int i = 0; i < LINE_LENGTH; i++) {
		std::string line = make_line_from_vector(matrix[i]);
		xmas_counter += count_number_of_occurences_of_XMAS_and_SMAX(line);
	};
	
	// Create "diagonal" matrix, turn already turned matrix -45
	std::vector<std::vector<char>> rotatedMatrix = rotateMinus45Degrees(matrix);
	// Find horizontal XMAS and SMAX, but now its basically from down left to up right and reverse
	for (int i = 0; i < rotatedMatrix.size(); i++) {
		std::string line = make_line_from_vector(rotatedMatrix[i]);
		xmas_counter += count_number_of_occurences_of_XMAS_and_SMAX(line);
	};

	// Create "diagonal" matrix, turn original matrix -45
	std::vector<std::vector<char>> otherRotatedMatrix = rotateMinus45Degrees(originalMatrix);
	// Find horizontal XMAS and SMAX, but now its basically from down left to up right and reverse
	for (int i = 0; i < otherRotatedMatrix.size(); i++) {
		std::string line = make_line_from_vector(otherRotatedMatrix[i]);
		xmas_counter += count_number_of_occurences_of_XMAS_and_SMAX(line);
	};

	std::cout << "XMAS COUNTER: " << xmas_counter << std::endl;

	int xmas = find_xmas_part_b(originalMatrix);
	std::cout << "X-MAS COUNTER PART B: " << xmas << std::endl;
	return 0;
}