#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main() {
    std::ifstream stream("day_5/input.txt");

    if (!stream) {
        std::cout << "No file found" << std::endl;
        return 0;
    }

    std::vector<std::pair<long long, long long>> ranges;
    std::vector<long long> ingredient_ids;
    std::string line;
    bool reading_ranges = true;

    // Read ranges and ingredient IDs
    while (std::getline(stream, line)) {
        if (line.empty()) {
            reading_ranges = false;
            continue;
        }

        if (reading_ranges) {
            // Parse range like "3-5"
            size_t dash_pos = line.find('-');
            long long start = std::stoll(line.substr(0, dash_pos));
            long long end = std::stoll(line.substr(dash_pos + 1));
            ranges.push_back({start, end});
        } else {
            // Parse ingredient ID
            ingredient_ids.push_back(std::stoll(line));
        }
    }

    int fresh_count = 0;

    // Check each ingredient ID
    for (long long id : ingredient_ids) {
        bool is_fresh = false;
        
        // Check if ID falls in any range
        for (const auto& range : ranges) {
            if (id >= range.first && id <= range.second) {
                is_fresh = true;
                break;
            }
        }
        
        if (is_fresh) {
            fresh_count++;
        }
    }

    std::cout << "Fresh ingredients: " << fresh_count << std::endl;
    return 0;
}
