#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <print>
#include <queue>
#include <string>
#include <vector>

/* Union-Find (Disjoint Set Union) data structure implementation 
* with path compression and union by rank.
* Basically Kruskal's MST algorithm with some
* puzzle specific functionality methods.
* @param n Number of elements
*/
class UnionFind {
private:
	// Here, the parent vector holds the parent of each element
	// I.e. if all elements point to the same root, they are in the same set
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
    
    bool isConnected(size_t x, size_t y) {
        return find(x) == find(y);
    }

	/* Check if all elements are connected
	 * by verifying if they all share the same root.
	 */
	bool isFullyConnected() {
		size_t root = find(0);
		for (size_t i = 1; i < parent.size(); i++) {
			if (root != find(i)) {
				return false;
			}
		}
		return true;
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

	// Phase 1: Read in all elements
	std::string line;
	std::vector<std::array<int, 3>> positions;

	while (std::getline(std::cin, line)) {
		std::istringstream iss(line);
		std::array<int, 3> pos;
		char comma;

		iss >> pos[0] >> comma >> pos[1] >> comma >> pos[2];
		positions.push_back(pos);
	}

	size_t N = positions.size(); // Num junction boxes i.e. vertices

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

	// Phase 3: Connect all the junction boxes into circuits, 
	// and check if the circuit is fully connected
	UnionFind circuits(N);
	Cable cable;

	while (!minHeap.empty()) {
		cable = minHeap.top();
		minHeap.pop();
		circuits.unite(cable.i, cable.j);
		if (circuits.isFullyConnected()) {
			long result = static_cast<long>(positions[cable.i][0]) * positions[cable.j][0];
			std::println(
				"The answer is: {} * {} = {}", 
				positions[cable.i][0],
				positions[cable.j][0],
				result
			);
			break;
		}
	}
		
    return 0;
}
