#include <iostream>
#include <print>
#include <string>
#include <vector>
#include <stdexcept>

bool accesible(const std::vector<std::vector<char>>& grid, size_t i, size_t j) {
	// Make a vector of 8 adjecent positions
	std::vector<char> adj = { 
		grid[i-1][j-1], // NW
		grid[i-1][j],   // N
		grid[i-1][j+1], // NE
		grid[i][j-1],   // W
		grid[i][j+1],   // E
		grid[i+1][j-1], // SW
		grid[i+1][j],   // S
		grid[i+1][j+1]  // SE
	};
	int sum = 0;
	for (char c : adj) {
		if (c == '@') {
			sum++;
		}
	}
	if (sum < 4) {
		return true;
	}
	else {
		return false;
	}
};

int main() {
	// Not most performant. Each internal vector gets own heap alloc
	// flat arrays or mdspan better options, but this is intuitive
	// and generic across all C++ version 11+
	std::vector<std::vector<char>> grid;

	for (std::string line; std::getline(std::cin, line);) {
		std::vector<char> row(line.begin(), line.end());
		row.insert(row.begin(), '.');
		row.push_back('.');
		grid.push_back(row);
	}
	size_t cols = grid[0].size();

	grid.insert(grid.begin(), std::vector<char>(cols, '.'));
	grid.push_back(std::vector<char>(cols, '.'));

	int answer = 0;
	for (size_t i = 1; i < grid.size() - 1; i++) {
		for (size_t j = 1; j < grid[i].size() - 1; j++) {
			if (grid[i][j] == '@') {
				if (accesible(grid, i, j)) {
					answer++;
				}
			}
		}
	}
	std::println("The answer is: {}", answer);
}
