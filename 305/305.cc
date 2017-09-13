#include <iostream>
#include <vector>
#include <string>

class Joseph {
  unsigned int N_;
  unsigned int M_;
  std::vector<bool> people_;
  unsigned int index_;
  unsigned int dead_;
  
public:
  Joseph(unsigned int N,unsigned int M):
    N_(N), M_(M),
    people_(N,true), index_(N-1),
    dead_(0)
    { }

  void count1() {
    do {
      index_ = (index_ + 1) % N_;
    } while (!people_[index_]);
  }

  unsigned int killNext() {
    unsigned int times(M_ % (N_ -dead_));
    if (times == 0) {
      times = N_ - dead_;
    }

    for (unsigned int i=0; i<times; i++) {
      count1();
    }
    people_[index_] = false;
    dead_++;

    return index_;
  }

  unsigned int dead() const {return dead_;}

};

int main()
{

  std::vector<unsigned int> solutions(13+1,0);
  
  std::string line;
  while (std::getline(std::cin, line)) {
    unsigned int K= atoi(line.c_str());
    unsigned int N= K*2;

    if (K==0) {
      return 0;
    } else if (solutions[K] != 0) {
      std::cout << solutions[K] << "\n";
      continue;
    }

    for (unsigned int M=K+1;;++M) {
      //std::cout << "\nTest " << M << ": ";
      // test M
      Joseph joseph(N,M);

      unsigned int killed(0);
      do {
        killed = joseph.killNext();
        //std::cout << " " << killed;
        if (killed < K) break;
      } while (joseph.dead() < K);

      if (killed >= K) {
        std::cout << M << "\n";
        solutions[K] = M;
        break;
      }
    }


  }

  return 0;
}
