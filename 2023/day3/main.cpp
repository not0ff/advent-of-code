#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <vector>

const char EMPTY = '.';
const int neighbours[][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                             {0, 1},   {1, -1}, {1, 0},  {1, 1}};

class Schematic {
private:
  std::vector<std::string> matrix;
  void read_matrix(std::ifstream &file);

public:
  Schematic(std::ifstream &from_file) { this->read_matrix(from_file); }
  int len_x() { return static_cast<int>(this->matrix.size()); }
  int len_y() { return static_cast<int>(this->matrix.at(0).size()); }
  char at(int x, int y);
  bool near_symbol(int x, int y);
};

int main() {
  std::ifstream file("./inputs/input.txt");
  Schematic schem(file);

  int sum = 0;
  bool near_symbol = false;
  std::string curr_num = "";
  for (int x = 0; x < schem.len_x(); x++) {
    for (int y = 0; y < schem.len_y(); y++) {
      const auto c = schem.at(x, y);
      if (!std::isdigit(c)) {
        if (!curr_num.empty() && near_symbol) {
          sum += std::stoi(curr_num);
        }
        curr_num.clear();
        near_symbol = false;
      } else {
        curr_num += c;
        if (schem.near_symbol(x, y))
          near_symbol = true;
      }
    }
    if (!curr_num.empty() && near_symbol)
      sum += std::stoi(curr_num);
    curr_num.clear();
    near_symbol = false;
  }
  std::cout << "Sum: " << sum << std::endl;
  return 0;
}

void Schematic::read_matrix(std::ifstream &file) {
  std::string line;
  while (std::getline(file, line)) {
    this->matrix.push_back(line);
  }
}

char Schematic::at(int x, int y) {
  if (x >= static_cast<int>(this->matrix.size()) ||
      y >= static_cast<int>(this->matrix.at(0).size()) || x < 0 || y < 0) {
    return EMPTY;
  }
  return this->matrix.at(static_cast<size_t>(x)).at(static_cast<size_t>(y));
}

bool Schematic::near_symbol(int x, int y) {
  for (const auto &nb : neighbours) {
    auto c = this->at(x + nb[0], y + nb[1]);
    if (c != EMPTY && !std::isdigit(c))
      return true;
  }
  return false;
}
