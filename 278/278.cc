#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>

unsigned int getMaxPiecesRook(unsigned int N, unsigned int M)
{
  return std::min(N,M);
}

unsigned int getMaxPiecesKnight(unsigned int N, unsigned int M)
{
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

unsigned int getMaxPiecesKing(unsigned int N, unsigned int M)
{
  return ((N/2) + (N%2)) * ((M/2) +(M%2)) ;
}

unsigned int getMaxPiecesQueen(unsigned int N, unsigned int M)
{
  return std::min(N,M);;
}

typedef unsigned int (*getMaxPiecesFun)(unsigned int N, unsigned int M);

std::unordered_map<char,getMaxPiecesFun> mapPieceFun ={
  {'r', getMaxPiecesRook},
  {'k', getMaxPiecesKnight},
  {'K', getMaxPiecesKing},
  {'Q', getMaxPiecesQueen},
};

int main(void)
{

  unsigned int cases(0);
  std::cin >> cases;

  std::string line;
  std::getline(std::cin, line);

  while(cases --) {
    do {
      std::getline(std::cin, line);
    } while (line.size()==0);
    std::stringstream sline(line);

    char piece;
    unsigned int N;
    unsigned int M;

    sline >> piece >> N >> M;

    std::cout << mapPieceFun[piece](N,M) << '\n';


  }

}
