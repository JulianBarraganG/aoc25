#include <array>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <print>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

/* Union-Find (Disjoint Set Union) data structure implementation 
* with path compression and union by rank.
* Basically Kruskal's MST algorithm with some
* puzzle specific functionality methods.
* @param n Number of elements
*/
class UnionFind {
private:
    std::vector<size_t> parent;
	std::vector<size_t> rank;
    
public:
    UnionFind(size_t n) : parent(n), rank(n, 0) {
        for (size_t i = 0; i < n; i++) {
			// For initialization, every node is its own parent
            parent[i] = i;
        }
    }
    
	/* Find the parent of `x`. Path compression by
	* recursevily updates parent until it becomes root of all children.
	*/
    size_t find(size_t x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    bool unite(size_t x, size_t y) {
        size_t rootX = find(x);
        size_t rootY = find(y);
        
        if (rootX == rootY) {
            return false; // Already in same group
        }
        
        // Union by rank
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
    
    bool isConnected(size_t x, size_t y) {
        return find(x) == find(y);
    }

    // Get sizes of all circuits
    std::vector<size_t> getComponentSizes() {
        std::unordered_map<size_t, size_t> componentSize;
        
        // Count size of each component
        for (size_t i = 0; i < parent.size(); i++) {
            size_t root = find(i);
            componentSize[root]++;
        }
        
        // Extract sizes into vector
        std::vector<size_t> sizes;
        for (const auto& [root, size] : componentSize) {
            sizes.push_back(size);
        }
        
        return sizes;
    }
};


struct Cable {
	size_t i, j;
	double dist;
	
	auto operator<=>(const Cable& other) const {
		return dist <=> other.dist;
	}
};

int main() {

	// Phase 1: First read in all elements
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

	// Phase 2: Read in a priority queue, to maintain min heap structure
	// This allows us to take (and pop) the pair to connect at "top" at all times.
	std::priority_queue<Cable, std::vector<Cable>, std::greater<>> minHeap;

	for (size_t i = 0; i < N - 1; i++) {
		for (size_t j = i + 1; j < N; j++) {
			std::array<int, 3> pos1 = positions[i];
			std::array<int, 3> pos2 = positions[j];
			double distance = std::sqrt(
				std::pow(pos1[0]-pos2[0], 2) 
				+ std::pow(pos1[1]-pos2[1], 2) 
				+ std::pow(pos1[2]-pos2[2], 2)
			);
			minHeap.push({i, j, distance});
		}
	}

    // Phase 3: Connect the shortest `num_iter` pairs
	size_t num_iter= 1000;

	UnionFind circuits(N);

	for (size_t i = 0; i < num_iter && !minHeap.empty(); i++) {
		Cable cable = minHeap.top();
		minHeap.pop();
		circuits.unite(cable.i, cable.j);
	}
    
    // Phase 4: Get all component sizes, sort and multiply top 3
    std::vector<size_t> sizes = circuits.getComponentSizes();
    
    // Sort in descending order using ranges (best modern practices) from algorithm
    std::ranges::sort(sizes, std::greater<>());
    
    // Multiply the three largest
    if (sizes.size() >= 3) {
        long long result = static_cast<long long>(sizes[0]) * sizes[1] * sizes[2];
        std::println("Answer: {} * {} * {} = {}", 
                    sizes[0], sizes[1], sizes[2], result);
    } else {
		std::println("Something went terribly wrong. Sizes was instantiated size N > 2. Christmas is ruined... :(");
	}

    return 0;
}
