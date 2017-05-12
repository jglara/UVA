#include <iostream>
#include <string>
#include <array>
#include <stdlib.h>
#include <string.h>

const unsigned int NCARDS=52;
std::array<std::string, NCARDS> pile;

int main(void)
{
  unsigned int cases(0);

  std::cin >> cases;

  for (auto n=0;n<cases;n++) {
    unsigned int i=0;
    // read first 25 cards
    std::string c;

    for(;i<NCARDS-25;i++) {
      std::cin >> c;
      pile[i] = c;
    }
    i --;

    // apply algorithm
    unsigned int acum(0);
    for (auto j=0;j<3;j++) {
      unsigned int value(10);
      if (strchr("23456789",pile[i][0])) {
        value = (pile[i][0] - '0');
      }
      i -= ((10-value)+1);
      acum+=value;
    }

    // read the rest 25 cards and add them to the pile
    for(auto j=0;j<25;j++) {
      std::cin >> c;
      pile[++i] = c;
    }

    // find Y-th card in the pile
    std::cout << "Case " << n+1 << ": " << pile[acum-1] << '\n';

  }


}
