#include <iostream>
#include <iterator>
#include <algorithm>
#include <array>
#include <string>

using namespace std;

void print_division(int n) {
  string digits("0123456789");
  bool found(false);
  do {
    unsigned int abcde = stoi(digits.substr(0,5));
    unsigned int fghij = stoi(digits.substr(5,5));
    if (abcde == fghij * n) {
      found=true;
      cout << digits.substr(0,5) <<" / " << digits.substr(5,5) << " = " << n << "\n";
    }

  } while(next_permutation(digits.begin(), digits.end()));

  if (not found) {
    cout << "There are no solutions for " << n << "\n";
  }
  cout << "\n";
}

int main()
{

  for_each(istream_iterator<int>(cin),
           istream_iterator<int>(),
           [] (int val) {
             if (val != 0) {
               print_division(val);
             }
           });
  
}
