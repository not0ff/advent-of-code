#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Races {
public:
  vector<pair<int, int>> races;
  Races(istream &f) : races(parse_races(f)) {};

  int wins_product() {
    int prod = 1;
    for (const auto &race : races) {
      const auto wins = race_wins(race);
      prod *= wins;
    }
    return prod;
  }

private:
  vector<pair<int, int>> parse_races(istream &f) {
    string line;

    getline(f, line);
    const auto times = parse_line(line);
    getline(f, line);
    const auto dists = parse_line(line);

    assert(times.size() == dists.size());
    vector<pair<int, int>> races(times.size());
    for (size_t i = 0; i < races.size(); ++i)
      races[i] = make_pair(times[i], dists[i]);

    return races;
  }

  vector<int> parse_line(string &line) {
    istringstream ss(line.substr(10));
    vector<int> nums;
    int n;
    while (ss >> n)
      nums.push_back(n);

    return nums;
  }
  int race_wins(const pair<int, int> &race) {
    auto [time, dist] = race;

    float h_delta = sqrt(pow(time, 2) - 4 * dist);
    float h_min = (time - h_delta) / 2;
    float h_max = (time + h_delta) / 2;
    return ceil(h_max) - floor(h_min) - 1;
  }
};

int main() {
  ifstream file("./inputs/input.txt");
  Races races(file);
  cout << "Product of possible wins: " << races.wins_product() << '\n';
}
