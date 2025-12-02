#include <print>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

int mod_hundred(int a) {
    return ((a % 100) + 100) % 100;
}

int calculate_result(const std::vector<std::string>& commands) {
    int result = 0;
    int dial_val = 50;
    int sign = 0;
    
    for(const auto& line : commands) {
        // Convert string to integer
        if (line.at(0) == 'L') {
            sign = -1;
        } else if (line[0] == 'R') {
            sign = 1;
        } else { 
			throw std::invalid_argument("Invalid prefix: " + line);
        }
        
        // Get number of turns
        int turn_x_times = std::stoi(line.substr(1));
        if (turn_x_times == 100) { result++; continue; }
        bool was_zero = (dial_val == 0); // remember if we were at 0 before turning
        
        // Remove laps
        int laps = std::abs(turn_x_times / 100);
        turn_x_times -= 100*laps;
        result += laps;
        
        // Turn the dial
        dial_val += sign*turn_x_times;
        if (dial_val < 0 || dial_val > 99) {
            dial_val = mod_hundred(dial_val);
            if (!was_zero && dial_val != 0) { result++; }
        }
        
        // Check if we are exactly 0
        if (dial_val == 0) { result++; }
    }
    
    return result;
}

int main() {

    // Otherwise, read from stdin (can be piped from file)
    std::vector<std::string> commands;
    for(std::string line; std::getline(std::cin, line);) {
        commands.push_back(line);
    }
    
    int result = calculate_result(commands);
    std::println("Result: {}", result);
    
    return 0;
}
