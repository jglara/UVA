#include <iostream>
#include <array>
#include <vector>
#include <sstream>
#include <algorithm>

const unsigned int NCARDS=52;

std::array<std::string,NCARDS+1> CARDS = {
  "",
  "2 of Clubs",
  "3 of Clubs",
  "4 of Clubs",
  "5 of Clubs",
  "6 of Clubs",
  "7 of Clubs",
  "8 of Clubs",
  "9 of Clubs",
  "10 of Clubs",
  "Jack of Clubs",
  "Queen of Clubs",
  "King of Clubs",
  "Ace of Clubs",
//
  "2 of Diamonds",
  "3 of Diamonds",
  "4 of Diamonds",
  "5 of Diamonds",
  "6 of Diamonds",
  "7 of Diamonds",
  "8 of Diamonds",
  "9 of Diamonds",
  "10 of Diamonds",
  "Jack of Diamonds",
  "Queen of Diamonds",
  "King of Diamonds",
  "Ace of Diamonds",
  //
  "2 of Hearts",
  "3 of Hearts",
  "4 of Hearts",
  "5 of Hearts",
  "6 of Hearts",
  "7 of Hearts",
  "8 of Hearts",
  "9 of Hearts",
  "10 of Hearts",
  "Jack of Hearts",
  "Queen of Hearts",
  "King of Hearts",
  "Ace of Hearts",
  //
  "2 of Spades",
  "3 of Spades",
  "4 of Spades",
  "5 of Spades",
  "6 of Spades",
  "7 of Spades",
  "8 of Spades",
  "9 of Spades",
  "10 of Spades",
  "Jack of Spades",
  "Queen of Spades",
  "King of Spades",
  "Ace of Spades",
};


int main(void)
{
  std::string line;
  
  // Read input
  std::getline(std::cin, line);
  unsigned int cases = atoi(line.c_str());

  // empty line
  std::getline(std::cin, line);
  while (cases--) {

    // Read Shuffles
    std::getline(std::cin, line);
    unsigned int shuffles = atoi(line.c_str());
    
    std::vector< std::array<unsigned int,NCARDS+1> > vecShuffles;
    for (auto s = 0; s < shuffles; s++) {

      std::array<unsigned int,NCARDS+1> shuffle;
      shuffle [0]=0;
      unsigned int cards(1);
      while (cards <= NCARDS) {
        std::getline(std::cin, line);
        std::stringstream linestr(line);

        while (linestr >> shuffle[cards]) {
          ++ cards;
        }
      }

      vecShuffles.push_back(shuffle);
    }

    // Read order of shuffles
    std::array<unsigned int,NCARDS+1> cards;
    for (auto i =1; i<NCARDS+1; i++) {
      cards[i]=i;
    }

    unsigned int i_shuffle;
    std::getline(std::cin, line);
    while ((i_shuffle = atoi(line.c_str())) > 0) {
      std::array<unsigned int,NCARDS+1> old_cards(cards);
      for (auto i =1; i<NCARDS+1; i++) {
        cards [ i ] =  old_cards [ (vecShuffles [ i_shuffle-1 ][ i ]) ];
      }
      std::getline(std::cin, line);
    };

    // print final output
    for (auto i =1; i<NCARDS+1; i++) {
      std::cout << CARDS [ cards[i] ] << '\n';
    }

    if (cases!=0) {
      std::cout << '\n';
    }

  }

}
