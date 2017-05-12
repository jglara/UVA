#include <string.h>
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

static const int CARDS=13;

int main(void)
{
  std::string hand;

  while(std::getline(std::cin, hand)) {
    std::stringstream handstr(hand);
    std::map<char,unsigned int> suits_counter;
    std::unordered_set<char> suits_stop;
    std::vector<card_t> cards;

    card_t card;
    for (auto i=0;i<CARDS;i++) {
      handstr >> card.rank >> card.suit;

       ++suits_counter[card.suit];
      if (strchr("AKQJ", card.rank)) {
        cards.push_back(card);
      }

    }

    // count points
    unsigned int points_rank(0);
    unsigned int points_suit(0);

    ////////////////////////////////////////
    // point ranks
    for (auto c : cards) {

      switch (c.rank) {
      case 'A':
      // #1
        points_rank +=4;
        suits_stop.insert(c.suit);
        break;

      case 'K':
      // #1 & #2
        if (suits_counter[c.suit] == 1) {
          points_rank+=2;
        } else {
          points_rank+=3;
          suits_stop.insert(c.suit);
        }
        break;

      // #1 #3
      case 'Q':
        if (suits_counter[c.suit] <= 2) {
          points_rank+=1;
        } else {
           points_rank+=2;
           suits_stop.insert(c.suit);
        }
        break;

      // #1 #4
      case 'J':
        if (suits_counter[c.suit] > 3) {
          ++ points_rank;
        }
        break;
      default:
        ;
      }
    }

    ////////////////////////////////////////
    // point suits
    for (auto s : suits_counter) {
      // #5
      switch (s.second) {
      case 2:
        points_suit += 1;
        break;
      case 1:
        points_suit += 2;
        break;
      case 0:
        points_suit += 2;
        break;
      default:
        ;
      }
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Assess bid

    if (points_rank + points_suit < 14) {
      std::cout << "PASS\n" ;
    } else if ((points_rank >= 16) and (suits_stop.size() == 4)) {
      std::cout << "BID NO-TRUMP\n";
    } else {
      std::cout << "BID " << (std::max_element(suits_counter.rbegin(), suits_counter.rend(),
                                               [](const std::pair<char,unsigned int> &a,
                                                  const std::pair<char,unsigned int> &b) { return a.second < b.second; } ))->first
                << '\n';

    }
  }

}
