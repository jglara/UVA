#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <unordered_set>
#include <algorithm>

typedef struct
{
  char rank;
  char suit;
} card_t;

int main(void)
{
  std::string hand;

  while(std::getline(std::cin, hand)) {
    std::stringstream handstr(hand);
    std::map<char,unsigned int> suits_counter;
    std::unordered_set<char> suits_stop;
    std::vector<card_t> cards;

    card_t card;
    while (handstr) {
      handstr >> card.rank >> card.suit;

      suits_counter[card.suit] ++;
      cards.push_back(card);

    }

    // count points
    unsigned int points1_4(0);
    unsigned int points5_7(0);

    ////////////////////////////////////////
    // point ranks
    for (auto c : cards) {

      // #1
      if ((c.rank == 'A')) {
        points1_4 +=4;

        suits_stop.insert(c.suit);
      }

      // #1 & #2
      if ((c.rank == 'K')) {
        if (suits_counter[c.suit] == 1) {
          points1_4+=2;
        } else {
           points1_4+=3;
        }

        // stop
        if (suits_counter[c.suit] >= 2) {
          suits_stop.insert(c.suit);
        }
      }

      // #1 #3
      if ((c.rank == 'Q')) {
        if (suits_counter[c.suit] <= 2) {
          points1_4+=1;
        } else {
           points1_4+=2;
        }

        // stop
        if (suits_counter[c.suit] >= 3) {
          suits_stop.insert(c.suit);
        }
      }

      // #1 #4
      if ((c.rank == 'J') and suits_counter[c.suit] <= 3) {
        ++ points1_4;
      }
    }

    ////////////////////////////////////////
    // point suits
    for (auto s : suits_counter) {
      // #5
      switch (s.second) {
      case 2:
        points5_7 += 1;
        break;
      case 1:
        points5_7 += 2;
        break;
      case 0:
        points5_7 += 2;
        break;
      default:
        ;
      }
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Asses bif

    if (points1_4 + points5_7 < 14) {
      std::cout << "PASS\n" ;
    } else if ((points1_4 >= 16) and (suits_stop.size() == 4)) {
      std::cout << "BID NO-TRUMP\n";
    } else {
      std::cout << "BID " << (std::max_element(suits_counter.rbegin(), suits_counter.rend(),
                                               [](const std::pair<char,unsigned int> &a,
                                                  const std::pair<char,unsigned int> &b) { return a.second < b.second; } ))->first
                << '\n';
    }
  }

}
