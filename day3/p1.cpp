#include <print>
#include <iostream>
#include <string>

struct Max {
	size_t idx;
	int value;
	std::string digit;
};

int main() {
	// Read from input, line by line as string
	int total_joltage = 0;
	for (std::string line; std::getline(std::cin, line); ) {
		Max max1{0, 0, "0"}; // highest
		Max max2{
			line.size() - 1,
			std::stoi(line.substr(line.size() - 1)),
			line.substr(line.size() - 1)
		}; // second highest (initialized to last digit)
		for (size_t i = 0; i < line.size() - 1; i++) {
			std::string digit = line.substr(i, 1);
			int query = std::stoi(digit);
			if (query > max1.value) {
				max1.idx = i;
				max1.value = query;
				max1.digit = digit;
			}
		}
		// Just a shortcut
		if (max1.value == max2.value || max1.value == max2.value - 1) {
			total_joltage += std::stoi(max1.digit + max2.digit);
			continue;
		}
		for (size_t j = max1.idx + 1; j < line.size() - 1; j++) {
			std::string digit = line.substr(j, 1);
			int query = std::stoi(digit);
			if (query > max2.value) {
				max2.value = query;
				max2.idx = j;
				max2.digit = digit;
			}
		}
		total_joltage += std::stoi(max1.digit.append(max2.digit));
	}
	std::println("The answer is: {}", total_joltage);
}
