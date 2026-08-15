#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <ostream>
#include <ranges>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// hacky way to easily support both parts
bool PART_2 = false;

class Hand {
public:
  enum class HandType {
    high_card,
    one_pair,
    two_pair,
    three_of_kind,
    full_house,
    four_of_kind,
    five_of_kind,
  };

  array<char, 5> cards;
  int bid;
  HandType type;

  Hand(string &line) { parse_hand(line); }

  static bool compare_hands(const Hand &h1, const Hand &h2) {
    unordered_map<char, int> card_strength = {
        {'2', 1},  {'3', 2},  {'4', 3},  {'5', 4}, {'6', 5},
        {'7', 6},  {'8', 7},  {'9', 8},  {'T', 9}, {'J', 10},
        {'Q', 11}, {'K', 12}, {'A', 13},
    };
    if (PART_2)
      card_strength['J'] = 0;

    if (h1.type != h2.type)
      return h1.type < h2.type;
    for (size_t i = 0; i < h1.cards.size(); ++i) {
      if (h1.cards[i] == h2.cards[i])
        continue;
      return card_strength.at(h1.cards[i]) < card_strength.at(h2.cards[i]);
    }
    return false;
  }

  // friend ostream &operator<<(ostream &os, Hand const &hand) {
  //   os << "Type: " << (int)hand.type << ' ';
  //   os << "Cards: ";
  //   for (auto card : hand.cards)
  //     os << card;
  //   os << " Bid: " << hand.bid;
  //   return os;
  // }

private:
  void parse_hand(string &line) {
    for (size_t i = 0; i < cards.size(); ++i) {
      cards.at(i) = line.at(i);
    }
    bid = stoi(line.substr(cards.size() + 1));
    type = hand_type(cards);
  }

  HandType hand_type(array<char, 5> cards) {
    unordered_map<char, int> card_counts;
    int jokers = 0;
    for (const auto c : cards) {
      if (c == 'J' && PART_2)
        ++jokers;
      else
        card_counts[c]++;
    }

    const auto counts = card_counts | views::values;
    multiset<int, greater<int>> freqs(ranges::begin(counts),
                                      ranges::end(counts));

    auto it = freqs.begin();
    const int first = *it++ + jokers;
    const int second = *it;
    if (first == 5)
      return HandType::five_of_kind;
    if (first == 4)
      return HandType::four_of_kind;
    if (first == 3 && second == 2)
      return HandType::full_house;
    if (first == 3)
      return HandType::three_of_kind;
    if (first == 2 && second == 2)
      return HandType::two_pair;
    if (first == 2)
      return HandType::one_pair;
    return HandType::high_card;
  }
};

int run_game(istream &file);

int main() {
  ifstream file("inputs/input.txt");

  cout << "Part 1 winnings: " << run_game(file) << '\n';
  file.clear();
  file.seekg(0);

  PART_2 = true;
  cout << "Part 2 winnings: " << run_game(file) << '\n';
}

int run_game(istream &file) {
  vector<Hand> hands;
  string line;
  while (getline(file, line)) {
    hands.emplace_back(line);
  }
  sort(hands.begin(), hands.end(), Hand::compare_hands);

  int total = 0;
  for (size_t i = 0; i < hands.size(); ++i) {
    // cout << hands[i] << '\n';
    total += (i + 1) * hands[i].bid;
  }
  return total;
}
