#include <iostream>
#include <iterator>
#include <map>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

int main()
{
  unsigned int N(0);
  cin >> N;
  string name;
  getline(cin, name);
  getline(cin, name);
  for (;N>0;--N) {

    // read and store tree names

    unsigned int total(0);
    map<string, unsigned int> trees;
    while (getline(cin, name)) {
      if (name.empty()) break;
      ++trees[name];
      total++;
    }

    // calculate %& print averages
    for_each(trees.begin(),
              trees.end(),
              [total] (pair<string, unsigned int> key_value) {
               cout << key_value.first << " " << fixed << setprecision(4) << static_cast<double>(key_value.second) * 100.0 / total << "\n";
              });

    if (N>1) {
      cout << "\n";
    }

  }


}
