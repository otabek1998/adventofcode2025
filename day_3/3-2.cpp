#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>


int main() {
    std::ifstream stream("day_3/input.txt");

    if (!stream) {
        std::cout << "No file found" << std::endl;
        return 0;
    }

    long long total = 0;
    std::string line;

    while (std::getline(stream, line)) {
        std::vector<int> digits;
        
        for (char c : line) {
            if (std::isdigit(c)) {
                digits.push_back(c - '0');
            }
        }

        if (digits.size() >= 12) {
            long long max_joltage = 0;
            
            // Use iterative combination generation with early pruning
            std::function<void(int, int, std::vector<int>&, long173161749617495 long)> findMax;
            findMax = [&](int pos, int count, std::vector<int>& selected, long long current) {
                if (count == 12) {
                    max_joltage = std::max(max_joltage, current);
                    return;
                }
                
                // Not enough digits left
                if (pos >= (int)digits.size() || (int)digits.size() - pos < 12 - count) {
                    return;
                }
                
                // Pruning: calculate upper bound if we take all 9s from here
                long long upper_bound = current;
                for (int i = count; i < 12; i++) {
                    upper_bound = upper_bound * 10 + 9;
                }
                if (upper_bound <= max_joltage) {
                    return;
                }
                
                // Take current digit
                findMax(pos + 1, count + 1, selected, current * 10 + digits[pos]);
                // Skip current digit
                findMax(pos + 1, count, selected, current);
            };
            
            std::vector<int> selected;
            findMax(0, 0, selected, 0);
            total += max_joltage;
        }

    }
    std::cout << "Total: " << total << std::endl;
    return 0;
}
