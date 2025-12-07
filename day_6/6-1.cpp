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

    std::vector<std::vector<long long>> numbers(4);
    std::vector<char> operations;
    std::string line;
    
    // Read 4 lines of numbers
    for (int row = 0; row < 4; row++) {
        std::getline(stream, line);
        std::istringstream iss(line);
        long long num;
        while (iss >> num) {
            numbers[row].push_back(num);
        }
    }
    
    // Read line of operations
    std::getline(stream, line);
    std::istringstream iss(line);
    char op;
    while (iss >> op) {
        operations.push_back(op);
    }
    
    long long total = 0;
    
    // Process each column
    for (size_t col = 0; col < operations.size(); col++) {
        long long result = numbers[0][col];
        
        // Apply operations with the next three numbers
        for (int i = 1; i < 4; i++) {
            if (operations[col] == '*') {
                result *= numbers[i][col];
            } else if (operations[col] == '+') {
                result += numbers[i][col];
            }
        }
        
        total += result;
    }
    
    std::cout << "Total: " << total << std::endl;
    return 0;
}
