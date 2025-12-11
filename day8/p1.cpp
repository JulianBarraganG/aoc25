#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <print>
#include <queue>
#include <string>
#include <vector>

int main() {

	// First read in all elements
	std::string line;
	std::vector<std::array<int, 3>> positions;
	while (std::getline(std::cin, line)) {
		std::istringstream iss(line);
		std::array<int, 3> pos;
		char comma;

		iss >> pos[0] >> comma >> pos[1] >> comma >> pos[2];
		positions.push_back(pos);
	}

	size_t N = positions.size();
	if (N < 2) {
		std::println("Need at least 2 positions");
		return 1;
	}

		std::priority_queue<double, std::vector<double>, std::less<double>> minHeap;

	for (size_t i = 0; i < N - 1; i++) {
		for (size_t j = i + 1; j < N; j++) {
			std::array<int, 3> pos1 = positions[i];
			std::array<int, 3> pos2 = positions[j];
			double distance = std::sqrt(
				std::pow(pos1[0]-pos2[0], 2) 
				+ std::pow(pos1[1]-pos2[1], 2) 
				+ std::pow(pos1[2]-pos2[2], 2)
			);
			if (minHeap.size() < 3) {
				minHeap.push(distance);
			}
			else if (distance < minHeap.top()) {
				minHeap.pop();
				minHeap.push(distance);
			}
		}
	}
	// Print the three min heap results
	std::vector<double> results;
	while (!minHeap.empty()) {
		std::println("{}", minHeap.top());
		minHeap.pop();
	}


	return 0;
}
