#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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

    int rows = grid.size();
    int cols = grid[0].size();
    int accessible_count = 0;

    // 8 directions: N, NE, E, SE, S, SW, W, NW
    int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

    // Check each position
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Only check if it's a roll of paper
            if (grid[i][j] == '@') {
                int adjacent_papers = 0;

                // Check all 8 adjacent positions
                for (int k = 0; k < 8; k++) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];

                    // Check if position is valid and contains paper
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                        if (grid[ni][nj] == '@') {
                            adjacent_papers++;
                        }
                    }
                }

                // Accessible if fewer than 4 adjacent papers
                if (adjacent_papers < 4) {
                    accessible_count++;
                }
            }
        }
    }

    std::cout << "Accessible rolls: " << accessible_count << std::endl;
    return 0;
}
