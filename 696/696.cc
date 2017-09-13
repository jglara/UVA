#include <iostream>
#include <algorithm>

unsigned int getMaxPiecesKnight(unsigned int N, unsigned int M)
{
  if (N == 0) {
    return 0;
  } else if (N == 1) {
    return M;
  } else if (N==2) {
    int q_c = (M/2);
    int q_t = (M/2) + (M%2);
    int total = 4*( (1+q_c)/2) + 2*(q_t % 2)*(M%2);
    return total;
  } else if (N==3) {
    if (M == 3) {
      return 5;
    } else if (M == 4) {
      return 6;
    }
  }

  unsigned int total = (2 * (N/2) * (M/2));

  if (N%2) {
    total += (M/2);
  }

  if (M%2) {
    total += (N/2);
  }

  if ((N%2) && (M%2)) {
    ++total;
  }

  return total;
}

int main(void) {

  int N,M;

  while(std::cin >> N >> M) {
    if ((N==0) && (M==0)) {
      return 0;
    }

    std::cout << getMaxPiecesKnight(std::min(N,M), std::max(N,M)) << " knights may be placed on a " << N << " row " << M << " column board.\n";
  }

}
