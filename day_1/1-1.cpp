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
    if (next_action[0] == 'R')
    {
      curr_position = (curr_position + offset) % 100;
    }
    else
    {
      curr_position = (curr_position - offset) % 100;
      if (curr_position < 0)
      {
        curr_position += 100;
      }
    }
    if (curr_position == 0)
    {
      result += 1;
    }
  }

  std::cout << result << std::endl;

  return 0;
}