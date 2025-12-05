#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream stream("day_5/input.txt");

    if (!stream) {
        std::cout << "No file found" << std::endl;
        return 0;
    }

    std::vector<std::pair<long long, long long>> ranges;
    std::string line;

    // Read only the ranges (ignore everything after blank line)
    while (std::getline(stream, line)) {
        if (line.empty()) {
            break; // Stop at blank line
        }

        // Parse range like "3-5"
        size_t dash_pos = line.find('-');
        long long start = std::stoll(line.substr(0, dash_pos));
        long long end = std::stoll(line.substr(dash_pos + 1));
        ranges.push_back({start, end});
    }

    // Sort ranges by start position
    std::sort(ranges.begin(), ranges.end());

    // Merge overlapping ranges and count total IDs
    long long total_count = 0;
    long long current_start = ranges[0].first;
    long long current_end = ranges[0].second;

    for (size_t i = 1; i < ranges.size(); i++) {
        if (ranges[i].first <= current_end + 1) {
            // Overlapping or adjacent ranges - merge them
            current_end = std::max(current_end, ranges[i].second);
        } else {
            // Non-overlapping range - count current range and start new one
            total_count += (current_end - current_start + 1);
            current_start = ranges[i].first;
            current_end = ranges[i].second;
        }
    }
    
    // Add the last range
    total_count += (current_end - current_start + 1);

    std::cout << "Total fresh IDs: " << total_count << std::endl;
    return 0;
}
