#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ifstream stream("day_1/input.txt");

    if (!stream) {
        std::cout << "No file found" << std::endl;
        return 0;
    }

    int result = 0;
    int curr_position = 50;
    std::string next_action{};

    while (stream >> next_action) {
        int offset = std::stoi(next_action.substr(1));
        
        // Count zeros crossed during rotation
        int direction = (next_action[0] == 'R') ? 1 : -1;
        for (int i = 0; i < offset; ++i) {
            curr_position = (curr_position + direction + 100) % 100;
            if (curr_position == 0) {
                result += 1;
            }
        }
    }

    std::cout << "Total times dial pointed at 0: " << result << std::endl;
    return 0;
}
