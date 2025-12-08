#include <functional>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include <print>

int main() {
    std::vector<std::vector<int>> homework;
	std::vector<char> ops;
    std::string line;
    bool first_line = true;
    
    while (std::getline(std::cin, line)) {
        // Check if we've hit the non-number (last) line
        if (line.find_first_of("*+") != std::string::npos) {
            std::istringstream iss(line);
            char op;
            while (iss >> op) {
                ops.push_back(op);
            }
        }
        
        std::istringstream iss(line);
        int num;
        size_t col = 0;
        
        while (iss >> num) {
            if (first_line) {
                // First line: create new columns
                homework.push_back({num});
            } else {
                // Subsequent lines: append to existing columns
                if (col < homework.size()) {
                    homework[col].push_back(num);
                }
            }
            col++;
        }
        
        first_line = false;
    }

	size_t num_cols = homework.size();
	unsigned long long int answer = 0;

	for (size_t i = 0; i < num_cols; i++) {
		if (ops[i] == '*') {
			answer += std::accumulate(homework[i].begin(), homework[i].end(), 1UL, std::multiplies<unsigned long int>());
		}
		else {
			answer += std::accumulate(homework[i].begin(), homework[i].end(), 0);
		}
	}
	std::println("The answer is: {}", answer);
}
