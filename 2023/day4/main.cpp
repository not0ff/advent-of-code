#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

using namespace std;

int part1(ifstream &file);

int main() {
  ifstream file("./inputs/input.txt");
  cout << "Total points won: " << part1(file) << '\n';
}

int part1(ifstream &file) {
  string line;
  auto sum = 0;

  while (getline(file, line)) {
    string nums = line.substr(line.rfind(':') + 1);
    auto sep_idx = nums.rfind('|');
    stringstream found_s(nums.substr(0, sep_idx));
    stringstream winning_s(nums.substr(sep_idx + 1));

    string n;
    unordered_set<int> found, winning;
    while (getline(found_s, n, ' ')) {
      if (!n.empty())
        found.insert(stoi(n));
    }
    while (getline(winning_s, n, ' ')) {
      if (!n.empty())
        winning.insert(stoi(n));
    }

    auto points = 0;
    for (const auto i : found) {
      if (auto it = winning.find(i); it != winning.end())
        points = (points == 0) ? 1 : points * 2;
    }
    sum += points;
  }
  return sum;
}
