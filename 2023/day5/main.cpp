#include <array>
#include <cctype>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Range {
  long int dest;
  long int src;
  long int len;

  Range() : dest{0}, src{0}, len{0} {};
  Range(long int d, long int s, long int l) : dest{d}, src{s}, len{l} {};

  bool in_src_range(long int n) const { return (n >= src && n < src + len); }
  bool in_dest_range(long int n) const { return (n >= dest && n < dest + len); }

  long int map_to_dest(long int n) const { return dest + (n - src); }
  long int map_to_src(long int n) const { return src + (n - dest); }
};

struct SeedRange {
  long int start;
  long int len;

  SeedRange() : start{0}, len{0} {};
  SeedRange(long int s, long int l) : start{s}, len{l} {};

  bool in_range(long int n) const { return (n >= start && n < start + len); }
};

class Almanac {
public:
  vector<long int> seeds;
  vector<SeedRange> seed_ranges;
  array<vector<Range>, 7> mappings;
  Almanac(istream &f) { parse_almanac(f); };

  int lowest_seed_loc() {
    long int lowest = -1;
    for (const auto seed : seeds) {
      auto trans = seed;
      for (const auto &map : mappings) {
        for (const auto &rng : map) {
          if (!rng.in_src_range(trans))
            continue;
          trans = rng.map_to_dest(trans);
          break;
        }
      }
      lowest = (lowest == -1 || trans < lowest) ? trans : lowest;
    }
    return lowest;
  }

  int lowest_range_loc() {
    for (long int loc = 0; loc >= 0; ++loc) {
      auto trans = loc;
      for (const auto &map : mappings | views::reverse) {
        for (const auto &rng : map) {
          if (!rng.in_dest_range(trans))
            continue;
          trans = rng.map_to_src(trans);
          break;
        }
      }
      for (const auto &seed_rng : seed_ranges) {
        if (seed_rng.in_range(trans))
          return loc;
      }
    }
    return -1;
  }

private:
  void parse_almanac(istream &f) {
    string line;
    int first = 0, map_idx = 0;
    while (getline(f, line) && map_idx < 7) {
      if (++first == 1) {
        parse_seeds(line);
        set_ranges_from_seeds(seeds);
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
    long int s;
    while (list >> s) {
      seeds.push_back(s);
    }
  }

  void set_ranges_from_seeds(vector<long int> &s) {
    for (size_t i = 0; i < s.size() - 1; i += 2) {
      seed_ranges.emplace_back(s[i], s[i + 1]);
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
    vector<long int> vals;
    vals.reserve(3);

    long int val;
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
  // cout << "\nSeed ranges:\n";
  // for (const auto &rng : alm.seed_ranges) {
  //   cout << "start: " << rng.start << " length: " << rng.len << '\n';
  // }
  // for (const auto &map : alm.mappings) {
  //   cout << "Mapping:\n";
  //   for (const auto &rng : map) {
  //     cout << rng.dest << ' ' << rng.src << ' ' << rng.len << '\n';
  //   }
  // }

  cout << "Lowest location for seed (part 1): " << alm.lowest_seed_loc()
       << '\n';
  cout << "Lowest location for seed ranges (part 2): " << alm.lowest_range_loc()
       << '\n';
}
