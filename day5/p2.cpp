#include <algorithm>
#include <print>
#include <iostream>
#include <string>
#include <unordered_set>
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
std::vector<Range> read_input() {
	std::string line;
	std::vector<Range> ranges;
	std::vector<Range> merged;

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
	// Sort and merge ranges
	std::sort(ranges.begin(), ranges.end(),
		[](Range a, Range b)
		{
		   return a.start < b.start;
		});
	// Merging loop
	for (auto& r : ranges) {
		if (merged.empty() || merged.back().end < r.start -1) {
			// New range (no overlap)
			merged.push_back(r);
		}
		else if (merged.back().end < r.end) {
			// Update range if it is bigger
			merged.back().end = r.end;
		}
		else {
			// Do nothing, current range already represented
			continue;
		}
	}
	return merged;
}


int main() {
	std::vector<Range> merged_ranges = read_input();

	unsigned long int num_fresh = 0;
	for (const auto& r : merged_ranges) {
		num_fresh += (r.end - r.start + 1);
	}
	std::println("The answer is: {}", num_fresh);
}
