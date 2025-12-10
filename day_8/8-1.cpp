#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

struct Point {
    long long x, y, z;
};

struct Edge {
    int i, j;
    long long dist_sq;
    
    bool operator<(const Edge& other) const {
        return dist_sq < other.dist_sq;
    }
};

class UnionFind {
    std::vector<int> parent;
    std::vector<int> size;
    
public:
    UnionFind(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            if (size[x] < size[y]) std::swap(x, y);
            parent[y] = x;
            size[x] += size[y];
        }
    }
    
    std::vector<int> get_component_sizes() {
        std::vector<int> components;
        for (int i = 0; i < parent.size(); i++) {
            if (find(i) == i) {
                components.push_back(size[i]);
            }
        }
        return components;
    }
};

int main() {
    std::ifstream stream("day_8/input.txt");

    if (!stream) {
        std::cout << "No file found" << std::endl;
        return 0;
    }

    std::vector<Point> points;
    std::string line;
    
    while (std::getline(stream, line)) {
        Point p;
        char comma;
        std::istringstream iss(line);
        iss >> p.x >> comma >> p.y >> comma >> p.z;
        points.push_back(p);
    }
    
    std::cout << "Number of junction boxes: " << points.size() << std::endl;
    
    // Calculate all pairwise distances
    std::vector<Edge> edges;
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            long long dx = points[i].x - points[j].x;
            long long dy = points[i].y - points[j].y;
            long long dz = points[i].z - points[j].z;
            long long dist_sq = dx*dx + dy*dy + dz*dz;
            edges.push_back({i, j, dist_sq});
        }
    }
    
    // Sort edges by distance
    std::sort(edges.begin(), edges.end());
    
    // Connect the 1000 shortest pairs
    UnionFind uf(points.size());
    for (int k = 0; k < 1000 && k < edges.size(); k++) {
        uf.unite(edges[k].i, edges[k].j);
    }
    
    // Get component sizes
    std::vector<int> sizes = uf.get_component_sizes();
    std::sort(sizes.rbegin(), sizes.rend());
    
    std::cout << "Number of circuits: " << sizes.size() << std::endl;
    std::cout << "Top 3 sizes: " << sizes[0] << ", " << sizes[1] << ", " << sizes[2] << std::endl;
    
    long long result = (long long)sizes[0] * sizes[1] * sizes[2];
    std::cout << "Result: " << result << std::endl;
    
    return 0;
}
