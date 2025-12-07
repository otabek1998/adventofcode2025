#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main() {
    std::ifstream stream("day_6/input.txt");

    if (!stream) {
        std::cout << "No file found" << std::endl;
        return 0;
    }

    std::vector<std::string> lines;
    std::string line;
    
    // Read all lines as strings to preserve character positions
    while (std::getline(stream, line)) {
        lines.push_back(line);
    }
    
    long long total = 0;
    
    int height = lines.size();
    int width = lines[0].size();

    std::vector<long long> nums = { 0, 0 };
    
    // Read right-to-left (cephalopod math)
    for (int col = width - 1; col >= 0; --col) {
        bool found_operation = false;
        
        for (int row = 0; row < height; ++row) {
            char c = lines[row][col];
            
            if (c == '+') {
                long long result = 0;
                for (long long num : nums) {
                    result += num;
                }
                total += result;
                nums = { 0 };
                found_operation = true;
            } else if (c == '*') {
                long long result = 1;
                for (size_t i = 1; i < nums.size(); ++i) {
                    result *= nums[i];
                }
                total += result;
                nums = { 0 };
                found_operation = true;
            } else if (isdigit(c)) {
                nums.back() = nums.back() * 10 + (c - '0');
            }
        }
        
        // If no operation found, start a new number for next column
        if (!found_operation) {
            nums.push_back(0);
        }
    }
    
    std::cout << "Total: " << total << std::endl;
    return 0;
}
