#include <iostream>
#include <algorithm>

unsigned int calcCycleLength_helper(unsigned int n, unsigned int length)
{
  if (n==1) return length;

  if (n%2 == 1) {
    // n is odd
    return calcCycleLength_helper((3*n)+1,length+1);
  } else {
    // n is even
    return calcCycleLength_helper((n/2), length+1);
  }

}

unsigned int calcCycleLength(unsigned int n)
{
  return calcCycleLength_helper(n,1);
}

int main(void)
{
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

  }

}
