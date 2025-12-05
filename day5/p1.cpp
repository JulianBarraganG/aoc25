#include <print>
#include <iostream>
#include <string>
#include <vector>

struct Range {
	unsigned long int start;
	unsigned long int end;
};

/* Reads a line from stdin and parses it into a vector of Ranges.
Each range is expected to be in the format "start-end", and ranges are
comma-separated.
Example input: "100-200,300-400"
*/
void read_input(
	std::vector<Range>& ranges,
	std::vector<unsigned long int>& ingredients
) {
	std::string line;
	unsigned long int id;

	// First read in the 
	while (std::getline(std::cin, line)) {
		if (line.empty()) {
			break;
		}
		int dash_idx = line.find('-');
		ranges.push_back({
			std::stoul(line.substr(0, dash_idx)),
			std::stoul(line.substr(dash_idx + 1))
		});
	}
	
	while (std::cin >> id) {
		ingredients.push_back(id);
	}
}

int main() {
	std::vector<Range> ranges;
	std::vector<unsigned long int> ingredients;

	read_input(ranges, ingredients);
	
	std::vector<bool> counted(ingredients.size(), false);
	int fresh_ingredients = 0;

	for (const auto& r : ranges) {
		for (size_t i = 0; i < ingredients.size(); i++) {
			if (!counted[i] && ingredients[i] >= r.start && ingredients[i] <= r.end) {
				fresh_ingredients++;
				counted[i] = true;
			}
		}
	}
	std::println("The answer is: {}", fresh_ingredients);
}
