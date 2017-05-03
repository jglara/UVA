#include <iostream>

int main(void)
{

  bool in_quote(false);
  char c(0);
  while (std::cin.get(c)) {
    if (c == '"') {
      std::cout << ((in_quote)?"''":"``");
      in_quote = !in_quote;
    } else {
      std::cout << c;
    }

  }
  

}
