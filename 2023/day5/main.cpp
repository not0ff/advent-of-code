#include <array>
#include <cctype>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Range {
  long long int dest;
  long long int src;
  long long int len;

  Range() : dest{0}, src{0}, len{0} {};
  Range(long long int d, long long int s, long long int l)
      : dest{d}, src{s}, len{l} {};

  bool in_range(long long int n) const {
    return (n >= src && n <= src + len - 1);
  }

  long long int map_to_dest(long long int n) const { return dest + (n - src); }
};

class Almanac {
public:
  vector<long long int> seeds;
  array<vector<Range>, 7> mappings;
  Almanac(istream &f) { parse_almanac(f); };

  int lowest_seed_loc() {
    long long int lowest = -1;
    for (const auto seed : seeds) {
      auto trans = seed;
      for (const auto &map : mappings) {
        for (const auto &rng : map) {
          if (!rng.in_range(trans))
            continue;
          trans = rng.map_to_dest(trans);
          break;
        }
      }
      lowest = (lowest == -1 || trans < lowest) ? trans : lowest;
    }
    return lowest;
  }

private:
  void parse_almanac(istream &f) {
    string line;
    int first = 0, map_idx = 0;
    while (getline(f, line) && map_idx < 7) {
      if (++first == 1) {
        parse_seeds(line);
        continue;
      }
      if (line.find("map") == string::npos)
        continue;
      parse_map(f, map_idx);
      ++map_idx;
    }
  }
  void parse_seeds(string &line) {
    istringstream list(line.substr(7));
    long long int s;
    while (list >> s) {
      seeds.push_back(s);
    }
  }

  void parse_map(istream &f, int i) {
    string line;
    while (getline(f, line) && isdigit(line[0])) {
      mappings[i].push_back(parse_range(line));
    }
  }

  Range parse_range(string &line) {
    istringstream list(line);
    vector<long long int> vals;
    vals.reserve(3);

    long long int val;
    while (list >> val) {
      vals.push_back(val);
    }
    return Range(vals[0], vals[1], vals[2]);
  }
};

int main() {
  ifstream file("inputs/input.txt");
  Almanac alm(file);
  // cout << "Seeds:";
  // for (const auto &s : alm.seeds) {
  //   cout << ' ' << s;
  // }
  // cout << endl;
  // for (const auto &map : alm.mappings) {
  //   cout << "Mapping:\n";
  //   for (const auto &rng : map) {
  //     cout << rng.dest << ' ' << rng.src << ' ' << rng.len << '\n';
  //   }
  // }

  cout << "Lowest location for seed: " << alm.lowest_seed_loc() << '\n';
}
