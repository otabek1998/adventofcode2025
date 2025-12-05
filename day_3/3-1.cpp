#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>


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

        if (digits.size() >= 2) {
            int max_joltage = 0;
            for (size_t i = 0; i < digits.size() - 1; i++) {
                for (size_t j = i + 1; j < digits.size(); j++) {
                    int joltage = digits[i] * 10 + digits[j];
                    max_joltage = std::max(max_joltage, joltage);
                }
            }
            total += max_joltage;
        }

    }
    std::cout << "Total: " << total << std::endl;
    return 0;
}
