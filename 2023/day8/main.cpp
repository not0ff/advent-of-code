#include <cstdio>
#include <fstream>
#include <ios>
#include <iostream>
#include <istream>
#include <limits>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Network {
public:
  std::vector<char> path;
  std::unordered_map<std::string, std::pair<std::string, std::string>> network;

  Network(std::istream &f) { parse_network(f); }

  int traverse() {
    int steps{0}, i{0};
    std::string node = "AAA";
    while (node != "ZZZ") {
      const auto instr = path[i % path.size()];
      node = (instr == 'L') ? network[node].first : network[node].second;
      ++steps;
      ++i;
    }
    return steps;
  }

private:
  void parse_network(std::istream &f) {
    std::string line;
    std::getline(f, line);
    parse_instr(line);
    f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (getline(f, line)) {
      parse_node(line);
    }
  }

  void parse_instr(const std::string &line) {
    path.reserve(line.size());
    for (const auto c : line)
      path.push_back(c);
  }

  void parse_node(const std::string &line) {
    char key[4], left[4], right[4];
    if (std::sscanf(line.c_str(), "%3s = (%3s, %3s)", key, left, right) == 3)
      network.emplace(key, std::make_pair(left, right));
  }
};

int main() {
  std::fstream file("inputs/input.txt");
  Network network(file);
  std::cout << "Steps to reach ZZZ (part 1): " << network.traverse() << '\n';
}
