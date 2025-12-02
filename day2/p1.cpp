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
			if (str_i.size() % 2 != 0) { continue; } // can only check even length sequences for match
			fst_half = str_i.substr(0, str_i.size() / 2);
			snd_half = str_i.substr(str_i.size() / 2);
			if (fst_half == snd_half) {
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
