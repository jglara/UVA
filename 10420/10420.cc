#include <iostream>
#include <string>
#include <limits>
#include <map>
#include <unordered_set>

int main(void)
{

  unsigned int lines(0);
  std::cin >> lines;
  std::string country;
  std::string name;

  std::map<std::string, std::unordered_set<std::string> > conquests;
  
  while(lines--) {
    std::cin >> country;
    std::getline(std::cin, name);
    conquests[country].insert (name);
  }

  for(const auto& conquest : conquests) {
    std::cout << conquest.first << " " << conquest.second.size() << '\n';
  }

  return 0;

}
