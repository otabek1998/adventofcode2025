#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

struct Point {
    long long x, y;
};

int main() {
    std::ifstream stream("day_9/input.txt");

    if (!stream) {
        std::cout << "No file found" << std::endl;
        return 0;
    }

    std::vector<Point> red_tiles;
    std::string line;
    
    while (std::getline(stream, line)) {
        Point p;
        char comma;
        std::istringstream iss(line);
        iss >> p.x >> comma >> p.y;
        red_tiles.push_back(p);
    }
    
    long long max_area = 0;
    int best_i = -1, best_j = -1;
    
    // Try all pairs of red tiles as opposite corners
    for (size_t i = 0; i < red_tiles.size(); i++) {
        for (size_t j = i + 1; j < red_tiles.size(); j++) {
            long long x1 = red_tiles[i].x;
            long long y1 = red_tiles[i].y;
            long long x2 = red_tiles[j].x;
            long long y2 = red_tiles[j].y;
            
            // Check if they can form opposite corners (different x and y)
            if (x1 != x2 && y1 != y2) {
                long long width = (x2 > x1) ? (x2 - x1 + 1) : (x1 - x2 + 1);
                long long height = (y2 > y1) ? (y2 - y1 + 1) : (y1 - y2 + 1);
                long long area = width * height;
                if (area > max_area) {
                    max_area = area;
                    best_i = i;
                    best_j = j;
                }
            }
        }
    }

    std::cout << "Largest rectangle area: " << max_area << std::endl;
    
    return 0;
}
