#include <iostream>

int main(void)
{

  unsigned int T; // number of test cases
  std::cin >> T;

  for (unsigned int i=1;i<=T;i++) {
    unsigned int students;

    std::cin >> students;
    unsigned int max_vel=0;
    unsigned int vel(0);
    while (students --) {
      std::cin >> vel;
      if (vel>max_vel) max_vel=vel;
    }

    std::cout << "Case " << i << ": " << max_vel <<'\n';
  }

}
