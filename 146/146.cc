#include <iostream>
#include <algorithm>

int main()
{

  std::string line;
  while (std::getline(std::cin, line)) {

    if (line[0] == '#') {
      break;
    }

    if (std::next_permutation(line.begin(), line.end())) {
      std::cout << line << "\n";
    } else {
      std::cout << "No Successor\n";
    }

  }

  return 0;

}
