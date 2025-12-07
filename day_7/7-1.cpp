#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ifstream stream("day_7/input.txt");

    if (!stream) {
        std::cout << "No file found" << std::endl;
        return 0;
    }

    std::vector<std::string> grid;
    std::string line;
    
    while (std::getline(stream, line)) {
        grid.push_back(line);
    }
    
    // Find starting position 'S'
    int start_row = -1;
    int start_col = -1;
    
    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[row].size(); col++) {
            if (grid[row][col] == 'S') {
                start_row = row;
                start_col = col;
                break;
            }
        }
        if (start_row != -1) break;
    }
    
    // Track number of paths at each column position
    std::vector<long long> paths(grid[0].size(), 0);
    paths[start_col] = 1;
    
    long long total_splits = 0;
    
    // Process each row going down
    for (int row = start_row + 1; row < grid.size(); row++) {
        std::vector<long long> new_paths(grid[0].size(), 0);
        
        for (int col = 0; col < grid[0].size(); col++) {
            if (paths[col] > 0) {
                if (grid[row][col] == '^') {
                    total_splits++;
                    if (col > 0) new_paths[col - 1] += paths[col];
                    if (col < grid[0].size() - 1) new_paths[col + 1] += paths[col];
                } else if (grid[row][col] == '.') {
                    // Continue straight down
                    new_paths[col] += paths[col];
                }
            }
        }
        
        paths = new_paths;
    }
    
    std::cout << "Number of splits: " << total_splits << std::endl;
    return 0;
}
