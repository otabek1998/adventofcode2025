#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

bool isInvalidID(long long num) {
    std::string s = std::to_string(num);
    int len = s.length();
    
    // Try all possible pattern lengths (from 1 to len/2)
    // If the number can be formed by repeating a pattern at least twice
    for (int pattern_len = 1; pattern_len <= len / 2; ++pattern_len) {
        // Check if total length is divisible by pattern length
        if (len % pattern_len != 0) continue;
        
        // Check if the entire string is made of this pattern repeated
        bool matches = true;
        for (int i = pattern_len; i < len; ++i) {
            if (s[i] != s[i % pattern_len]) {
                matches = false;
                break;
            }
        }
        
        if (matches) {
            return true;  // Found a repeating pattern
        }
    }
    
    return false;
}

int main() {
    std::ifstream stream("day_2/input.txt");

    if (!stream) {
        std::cout << "No file found" << std::endl;
        return 0;
    }

    long long total = 0;
    std::string line;

    while (std::getline(stream, line)) {
        std::stringstream ss(line);
        std::string range;
        
        while (std::getline(ss, range, ',')) {
            // Parse range "start-end"
            size_t dash_pos = range.find('-');
            if (dash_pos == std::string::npos) continue;

            long long start = std::stoll(range.substr(0, dash_pos));
            long long end = std::stoll(range.substr(dash_pos + 1));

            // Find all invalid IDs in range [start, end]
            for (long long id = start; id <= end; ++id) {
                if (isInvalidID(id)) {
                    total += id;
                }
            }
        }
    }

    std::cout << "Sum of invalid IDs: " << total << std::endl;
    return 0;
}
