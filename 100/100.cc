#include <iostream>
#include <algorithm>
#include <unordered_map>

std::unordered_map<unsigned int, unsigned int> lengths;

unsigned int calcCycleLength(unsigned int n)
{
  if (lengths[n]) return lengths[n];

  if (n%2) {
    lengths[n] = calcCycleLength((n*3)+1)+1;
  } else {
    lengths[n] = calcCycleLength(n/2)+1;
  }

  return lengths[n];

}

int main(void)
{
  lengths[1] = 1;
  
  unsigned int I(0),J(0);
  while (std::cin >> I >> J) {

    unsigned int max(0);
    unsigned int ini=std::min(I,J);
    unsigned int fin=std::max(I,J);
    for (unsigned int i=ini; i<=fin; i++) {
      unsigned int clen = calcCycleLength(i);
      if (clen >max) max = clen;
    }

    std::cout << I << " " << J << " " << max << '\n';

    std

  }

}
