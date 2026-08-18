#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

struct Card {
  int wins = 0;
  int points = 0;

  Card(string line) { parse_card(line); }
  void parse_card(string &line);
};

vector<Card> parse_cards(istream &file);
int cards_won(vector<int> &cache, const vector<Card> &cards, size_t idx);

int main() {
  ifstream file("./inputs/input.txt");
  auto cards = parse_cards(file);

  vector<int> cache(cards.size(), -1);
  auto total_cards = 0;
  auto points = 0;

  for (size_t idx = 0; idx < cards.size(); ++idx) {
    points += cards[idx].points;
    total_cards += cards_won(cache, cards, idx);
  }
  cout << "Part 1(points won): " << points << '\n';
  cout << "Part 2(total cards won): " << total_cards << '\n';
}

int cards_won(vector<int> &cache, const vector<Card> &cards, size_t idx) {
  if (idx >= cards.size())
    return 0;
  if (cache[idx] != -1)
    return cache[idx];

  auto won = 0;
  for (auto i = 1; i <= cards[idx].wins; ++i) {
    won += cards_won(cache, cards, idx + i);
  }

  return cache[idx] = won + 1;
}

vector<Card> parse_cards(istream &file) {
  vector<Card> cards;
  string line;
  while (getline(file, line)) {
    cards.emplace_back(Card(line));
  }
  return cards;
}

void Card::parse_card(string &line) {
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

  for (const auto i : found) {
    if (auto it = winning.find(i); it != winning.end()) {
      ++wins;
      points = (points == 0) ? 1 : points * 2;
    }
  }
}
