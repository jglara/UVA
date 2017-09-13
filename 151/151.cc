#include <iostream>
#include <vector>

int main()
{

  std::string str;
  while(std::getline(std::cin, str)) {
    unsigned int N=atoi(str.c_str());

    if (N == 0) {
      return 0;
    } else {
      static const unsigned int LAST_REGION=13-1;

      for (unsigned int M=1;;++M) {
        //std::cout << "\nTest " << M << ": ";
        // test M
        std::vector<bool> regions(N,true);
        unsigned int index(0);
        unsigned int poweredOff(0);
        while (index != LAST_REGION) {
          //std::cout << " " << index+1;
          regions[index] = false;
          ++poweredOff;

          // find next region
          for (unsigned int i=0; i <M; i++) {
            do {
              index = (index + 1) % N;
            } while(!regions[index]);
          }
        }
        if (poweredOff == N-1) {
          std::cout << M << "\n";
          break;
        }
      }


    }
  }

  return 0;
}
