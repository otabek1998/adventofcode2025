#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

bool isInvalidID(long long num) {
    std::string s = std::to_string(num);
    int len = s.length();
    
    // Must have even length to be repeated twice
    if (len % 2 != 0) return false;
    
    int half = len / 2;
    // Check if first half equals second half
    for (int i = 0; i < half; ++i) {
        if (s[i] != s[half + i]) {
            return false;
        }
    }
    return true;
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
