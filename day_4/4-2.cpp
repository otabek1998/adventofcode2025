#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int countAdjacentPapers(const std::vector<std::string>& grid, int i, int j) {
    int rows = grid.size();
    int cols = grid[0].size();
    int count = 0;
    
    // 8 directions: N, NE, E, SE, S, SW, W, NW
    int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
    
    for (int k = 0; k < 8; k++) {
        int ni = i + dx[k];
        int nj = j + dy[k];
        
        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
            if (grid[ni][nj] == '@') {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    std::ifstream stream("day_4/input.txt");

    if (!stream) {
        std::cout << "No file found" << std::endl;
        return 0;
    }

    std::vector<std::string> grid;
    std::string line;

    // Read the grid
    while (std::getline(stream, line)) {
        grid.push_back(line);
    }

    int total_removed = 0;
    bool changed = true;

    // Keep removing until no more can be removed
    while (changed) {
        changed = false;
        std::vector<std::pair<int, int>> to_remove;
        
        int rows = grid.size();
        int cols = grid[0].size();
        
        // Find all accessible rolls in this iteration
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == '@') {
                    int adjacent = countAdjacentPapers(grid, i, j);
                    if (adjacent < 4) {
                        to_remove.push_back({i, j});
                    }
                }
            }
        }
        
        // Remove all accessible rolls
        if (!to_remove.empty()) {
            changed = true;
            for (auto& pos : to_remove) {
                grid[pos.first][pos.second] = '.';
            }
            total_removed += to_remove.size();
        }
    }

    std::cout << "Total removed: " << total_removed << std::endl;
    return 0;
}
