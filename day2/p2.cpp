#include <cstdio>
#include <print>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <numeric>

struct Range {
	unsigned long int start;
	unsigned long int end;
};

/* Reads a line from stdin and parses it into a vector of Ranges.
Each range is expected to be in the format "start-end", and ranges are
comma-separated.
Example input: "100-200,300-400"
*/
std::vector<Range> read_ranges() {
	std::vector<Range> ranges;

	std::string line; // buffer for line
	std::getline(std::cin, line); // read from sdtin to buffer

	std::istringstream ss(line);
	std::string token; // buffer for each comma separated token


	while (std::getline(ss, token, ',')) {
		int dash_idx = token.find('-');
		ranges.push_back({
			std::stoul(token.substr(0, dash_idx)),
			std::stoul(token.substr(dash_idx + 1))
		});
	}

	return ranges;
}

/* Checks if the given query string consists of a repeating pattern.
*/
bool repeating_pattern(std::string& query) {
	size_t len = query.size();
	// Whatever pattern must divide the len of the query
	for (size_t pat_len = 1; pat_len <= len / 2; pat_len++) {
		if (len % pat_len != 0) continue; // e.g. 4 % 3 = 1, and a pattern of len 3 cannot make symmetry
		// For dividers, check if pattern consistently repeats
		std::string pattern = query.substr(0, pat_len);
		bool matching = true;

		for (size_t i = pat_len; i < len; i +=pat_len) {
			if (pattern != query.substr(i, pat_len)) {
				matching = false;
				break;
	  		}
	  	}
		// Might not be true for this pattern, but true for whole pattern
		// e.g. 45 pattern in 450450 will break, but we must continue to pat_len = 3 to find this
		if (matching) return true;
	}

	// Iterated through all possible pattern lengths, but found no repeating ones
	return false;

}

int main() {
	std::vector<Range> ranges = read_ranges();
	std::vector<unsigned long int> invalid_ids;
	std::string str_i;
	std::string fst_half;
	std::string snd_half;


	// Loop over every range, and for every range loop through
	for (const auto& r : ranges) {
		for (unsigned long int i = r.start; i <= r.end; i++) {
			str_i = std::to_string(i);
			if (repeating_pattern(str_i)) {
				invalid_ids.push_back(i);
			}
		}
	}
	unsigned long long int id_sum = std::accumulate(
		invalid_ids.begin(),
		invalid_ids.end(),
		0ULL
	);
	std::println("The answer is: {}", id_sum);
}
