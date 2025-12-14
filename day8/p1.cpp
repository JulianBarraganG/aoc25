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
    std::vector<int> parent;
    
public:
	std::vector<int> rank;
    UnionFind(size_t n) : parent(n), rank(n, 0) {
        for (size_t i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
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
    
    bool isConnected(int x, int y) {
        return find(x) == find(y);
    }

    // Get sizes of all circuits
    std::vector<int> getComponentSizes(size_t n) {
        std::unordered_map<int, int> componentSize;
        
        // Count size of each component
        for (size_t i = 0; i < n; i++) {
            int root = find(i);
            componentSize[root]++;
        }
        
        // Extract sizes into vector
        std::vector<int> sizes;
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

	// First read in all elements
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

    // Connect the shortest X pairs
	size_t num_iter= 1000;

	UnionFind circuits(N);

	for (size_t i = 0; i < num_iter && !minHeap.empty(); i++) {
		Cable cable = minHeap.top();
		minHeap.pop();
		circuits.unite(cable.i, cable.j);
	}
    
    // Get all component sizes
    std::vector<int> sizes = circuits.getComponentSizes(N);
    
    // Sort in descending order
    std::ranges::sort(sizes, std::greater<>());
    
    // Multiply the three largest
    if (sizes.size() >= 3) {
        long long result = static_cast<long long>(sizes[0]) * sizes[1] * sizes[2];
        std::println("\nAnswer: {} * {} * {} = {}", 
                    sizes[0], sizes[1], sizes[2], result);
    }

    return 0;
}
