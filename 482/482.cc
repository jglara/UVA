#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>


int main()
{
  std::string line;
  // Read number of cases
  std::getline(std::cin, line);
  unsigned int n=atoi(line.c_str());

  // Loop over cases
  for (;n>0;--n) {
    // read empty line
    std::getline(std::cin, line);

    // read permutation line
    std::vector<unsigned int> permutation;
    {
      std::getline(std::cin, line);
      std::istringstream sstr(line);

      std::copy(std::istream_iterator<unsigned int>( sstr ),
                std::istream_iterator<unsigned int>(),
                std::back_insert_iterator< std::vector<unsigned int> >(permutation));
    }

    // read float line and insert in the right position
    std::vector< std::string > numbers(permutation.size());
    {
      std::getline(std::cin, line);
      std::istringstream sstr(line);
      auto itPermutation(permutation.begin());
      auto itEnd(permutation.end());

      std::for_each(std::istream_iterator< std::string >( sstr ),
                    std::istream_iterator< std::string >(),
                    [&numbers, &itPermutation, &itEnd] (std::string n) {
                      if (itPermutation != itEnd) {
                        numbers[ (*itPermutation) - 1] = n; ++itPermutation;
                      }
                    }
        );
    }

    // print numbers
    std::copy_if(numbers.begin(), numbers.end(), std::ostream_iterator<std::string>( std::cout, "\n" ),
                 [] (std::string n) { return !n.empty(); });

    if (n>1) {std::cout << "\n";}

  };
  

}
