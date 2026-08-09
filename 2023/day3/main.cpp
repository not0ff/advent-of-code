#include <array>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <pthread.h>
#include <string>
#include <sys/types.h>
#include <utility>
#include <variant>
#include <vector>

using namespace std;

class Part {
public:
  int id;
  variant<int, char> value;
  Part(int i, variant<int, char> v) : id{i}, value{v} {}
  bool is_symbol() {
    return holds_alternative<char>(value) && get<char>(value) != empty_symbol;
  }
  bool is_star() { return is_symbol() && (get<char>(value) == '*'); }

private:
  static constexpr char empty_symbol = '.';
};

class Schematic {
public:
  vector<vector<shared_ptr<Part>>> matrix;
  Schematic(ifstream &f) { init_matrix(f); }
  int gear_ratios();
  int count_parts();

private:
  void init_matrix(ifstream &f);
  shared_ptr<Part> at(int x, int y);
  int gear_ratio(int x, int y);
  bool symbol_adj(int x, int y);
  int size_x() { return static_cast<int>(matrix.size()); }
  int size_y() { return static_cast<int>(matrix.at(0).size()); }
  static constexpr array<pair<int, int>, 8> neigbours = {
      {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}};
};

int main() {
  ifstream file("./inputs/input.txt");
  Schematic schem(file);
  cout << "Part 1(sum of part numbers): " << schem.count_parts() << endl;
  cout << "Part 2(sum of gear ratios): " << schem.gear_ratios() << endl;
}

void Schematic::init_matrix(ifstream &f) {
  int id = 0;
  string line;
  while (getline(f, line)) {
    vector<shared_ptr<Part>> row;
    size_t i = 0;
    while (i < line.size()) {
      if (!isdigit(line[i])) {
        auto part_ptr = make_shared<Part>(++id, variant<int, char>{line[i]});
        row.push_back(part_ptr);
        ++i;
        continue;
      }
      auto start = i;
      int num = 0;
      while (i < line.size() && isdigit(line[i])) {
        num = num * 10 + (line[i] - '0');
        ++i;
      }
      auto part_ptr = make_shared<Part>(++id, variant<int, char>{num});
      for (auto end = i, j = start; j < end; ++j) {
        row.push_back(part_ptr);
      }
    }
    matrix.push_back(row);
  }
}

int Schematic::gear_ratio(int x, int y) {
  int last_id = -1;
  vector<int> nums;
  for (const auto &[dx, dy] : neigbours) {
    auto part = at(x + dx, y + dy);
    if (!part)
      continue;
    if (auto num = get_if<int>(&part->value)) {
      if (last_id != part->id) {
        nums.push_back(*num);
        last_id = part->id;
      }
    }
  }
  return (nums.size() == 2 ? nums[0] * nums[1] : 0);
}

int Schematic::gear_ratios() {
  auto sum = 0;
  for (auto x = 0; x < size_x(); ++x) {
    for (auto y = 0; y < size_y(); ++y) {
      auto part_ptr = at(x, y);
      if (part_ptr->is_star())
        sum += gear_ratio(x, y);
    }
  }
  return sum;
}

bool Schematic::symbol_adj(int x, int y) {
  for (const auto &[dx, dy] : neigbours) {
    auto part = at(x + dx, y + dy);
    if (!part)
      continue;
    if (part->is_symbol())
      return true;
  }
  return false;
}

int Schematic::count_parts() {
  auto sum = 0;
  for (auto x = 0; x < size_x(); ++x) {
    auto y = 0;
    while (y < size_y()) {
      auto part_ptr = at(x, y);
      if (const auto &num = get_if<int>(&part_ptr->value)) {
        bool is_adj = false;
        for (auto ptr = part_ptr; ptr == part_ptr; ++y, ptr = at(x, y)) {
          if (!symbol_adj(x, y))
            continue;
          is_adj = true;
        }
        if (is_adj)
          sum += *num;
      }
      ++y;
    }
  }
  return sum;
}

shared_ptr<Part> Schematic::at(int x, int y) {
  if (x >= static_cast<int>(size_x()) || y >= static_cast<int>(size_y()) ||
      x < 0 || y < 0) {
    return shared_ptr<Part>{};
  }
  return matrix[static_cast<size_t>(x)][static_cast<size_t>(y)];
}
