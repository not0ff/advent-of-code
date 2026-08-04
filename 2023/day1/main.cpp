#include <cctype>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

int part1(std::ifstream &file);
int part2(std::ifstream &file);

int main() {
  std::ifstream file("./inputs/input.txt");
  std::cout << "Part 1: " << part1(file) << std::endl;
  file.clear();
  file.seekg(0);
  std::cout << "Part 2: " << part2(file) << std::endl;
  return 0;
}

int part1(std::ifstream &file) {
  std::string line;
  int sum = 0;
  while (std::getline(file, line)) {
    std::vector<char> digits;
    for (char c : line) {
      if (std::isdigit(c)) {
        digits.push_back(c);
      }
    }
    std::string num = {digits.front(), digits.back()};
    sum += std::stoi(num);
  }
  return sum;
}

int part2(std::ifstream &file) {
  std::string line;
  int sum = 0;
  while (std::getline(file, line)) {
    std::vector<char> digits;
    for (uint i = 0; i < line.length(); i++) {
      if (std::isdigit(line[i])) {
        digits.push_back(line[i]);
        continue;
      }
      const std::vector<std::string> nums = {"one",   "two",   "three",
                                             "four",  "five",  "six",
                                             "seven", "eight", "nine"};
      for (uint j = 0; j < nums.size(); j++) {
        if (line.substr(i).starts_with(nums.at(j))) {
          digits.push_back(std::to_string(j + 1)[0]);
        }
      }
    }
    std::string num = {digits.front(), digits.back()};
    sum += std::stoi(num);
  }
  return sum;
}
