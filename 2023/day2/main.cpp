#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split_on(std::string str, char delim);
int part1(std::ifstream &file);
int part2(std::ifstream &file);
int game_power(std::string rounds);
bool game_possible(std::string rounds);

int main() {
  std::ifstream file("./inputs/input.txt");
  std::cout << "Sum of possible ids: " << part1(file) << std::endl;
  file.clear();
  file.seekg(0);
  std::cout << "Sum of set powers: " << part2(file) << std::endl;
}

int part1(std::ifstream &file) {
  std::string line;
  int sum = 0;
  while (std::getline(file, line)) {
    auto game = split_on(line, ':');
    if (game_possible(game.back())) {
      auto h = game.front();
      sum += std::stoi(h.substr(h.find(' ')));
    }
  }
  return sum;
}

int part2(std::ifstream &file) {
  std::string line;
  int sum = 0;
  while (std::getline(file, line)) {
    auto rounds = line.substr(line.find(':') + 2);
    sum += game_power(rounds);
  }
  return sum;
}

int game_power(std::string rounds) {
  int min_cubes[3] = {0}; // Minimum number of 0-red, 1-green, 2-blue cubes
  for (const auto &round : split_on(rounds, ';')) {
    for (const auto &pull : split_on(round, ',')) {
      auto t = split_on(pull, ' ');
      int count = std::stoi(t.front());
      std::string color = t.back();
      if (color == "red")
        min_cubes[0] = std::max(min_cubes[0], count);
      if (color == "green")
        min_cubes[1] = std::max(min_cubes[1], count);
      if (color == "blue")
        min_cubes[2] = std::max(min_cubes[2], count);
    }
  }
  return min_cubes[0] * min_cubes[1] * min_cubes[2];
}

bool game_possible(std::string rounds) {
  for (const auto &round : split_on(rounds, ';')) {
    for (const auto &pull : split_on(round, ',')) {
      auto t = split_on(pull, ' ');
      int count = std::stoi(t.front());
      std::string color = t.back();
      if (color == "red" && count > 12)
        return false;
      if (color == "green" && count > 13)
        return false;
      if (color == "blue" && count > 14)
        return false;
    }
  }
  return true;
}

std::vector<std::string> split_on(std::string str, char delim) {
  std::stringstream ss(str);
  std::vector<std::string> list;
  while (ss.good()) {
    std::string substr;
    std::getline(ss, substr, delim);
    substr.erase(substr.find_last_not_of(' ') + 1);
    substr.erase(0, substr.find_first_not_of(' '));
    list.push_back(substr);
  }
  return list;
}
