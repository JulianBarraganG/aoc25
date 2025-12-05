#include <cstdio>
#include <print>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

struct Range {
	unsigned long int start;
	unsigned long int end;
};

/* Reads a line from stdin and parses it into a vector of Ranges.
Each range is expected to be in the format "start-end", and ranges are
comma-separated.
Example input: "100-200,300-400"
*/
vector<Range> read_ranges() {
	vector<Range> ranges;

	string line; // buffer for line
	getline(cin, line); // read from sdtin to buffer

	istringstream ss(line);
	string token; // buffer for each comma separated token


	while (getline(ss, token, ',')) {
		int dash_idx = token.find('-');
		ranges.push_back({
			stoul(token.substr(0, dash_idx)),
			stoul(token.substr(dash_idx + 1))
		});
	}

	return ranges;
}

/* Checks if the given query string consists of a repeating pattern.
*/
bool repeating_pattern(string& query) {
	size_t len = query.size();
	// Whatever pattern must divide the len of the query
	for (size_t pat_len = 1; pat_len <= len / 2; pat_len++) {
		if (len % pat_len != 0) continue; // e.g. 4 % 3 = 1, and a pattern of len 3 cannot make symmetry
		// For dividers, check if pattern consistently repeats
		string pattern = query.substr(0, pat_len);
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
	vector<Range> ranges = read_ranges();
	vector<unsigned long int> invalid_ids;
	string str_i;
	string fst_half;
	string snd_half;


	// Loop over every range, and for every range loop through
	for (const auto& r : ranges) {
		for (unsigned long int i = r.start; i <= r.end; i++) {
			str_i = to_string(i);
			if (repeating_pattern(str_i)) {
				invalid_ids.push_back(i);
			}
		}
	}
	unsigned long long int id_sum = accumulate(
		invalid_ids.begin(),
		invalid_ids.end(),
		0ULL
	);
	println("The answer is: {}", id_sum);
}
