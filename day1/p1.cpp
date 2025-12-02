#include <csignal>
#include <print>
#include <string>
#include <iostream>

int main() {
	// Variables
	int result = 0;
	int dial_val = 50;
	int sign = 0;

	// Read input line by line as strings
	for(std::string line; std::getline(std::cin, line);) {

		// Determine the turn direction
		if (line.at(0) == 'L') { // compare to literal character (not string) ' vs "
			sign = -1;
		} else if (line[0] == 'R') {
			sign = 1;
		} else { return 1; } // return 1 if not 'L' or 'R'

		// Turn the dial
		int turn_x_times = std::stoi(line.substr(1));
		if (turn_x_times == 100) { result++; continue; }
		dial_val += sign*turn_x_times;

		// Enforce the ring behavior
		while (dial_val < 0) {
			dial_val += 100;
		}
		while (dial_val >= 100) {
			dial_val -= 100;
		}
		// Finally, check if we are at 0
		if (dial_val == 0) { 
			result++;
		}
	}
	std::println("Result: {}", result);
	return 0;
}
