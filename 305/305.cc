#include <iostream>
#include <vector>
#include <string>

int main()
{

  std::string line;
  while (std::getline(std::cin, line)) {
    unsigned int K= atoi(line.c_str());
    unsigned int N= K*2;

    if (K==0) {
      return 0;
    }

    for (unsigned int M=1;;++M) {
      // std::cout << "\nTest " << M << ": ";
      // test M
      std::vector<bool> people(N,true);
      unsigned int index((M-1)%N);
      unsigned int dead(0);
      while (index >= K && dead<K) {
        //std::cout << " " << index;
        people[index] = false;
        ++dead;
        
        // find next guy to die
        for (unsigned int i=0; i <M; i++) {
          do {
            index = (index + 1) % N;
          } while(!people[index]);
        }
      }
      if (dead == K) {
        std::cout << M << "\n";
        break;
      }
    }

    


  }

  return 0;
}
