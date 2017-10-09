#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace std;

int main()
{
  unsigned int testcases(0);
  cin >> testcases;
  for(;testcases>0;--testcases) {

    unsigned int places(0);
    cin >> places;

    static const unsigned int MAX_PLACES=1000;
    vector<unsigned int> best_places;
    unsigned int min_neigh(MAX_PLACES);

    string line;
    getline(cin,line);
    for (unsigned int i=0;i <places;i++) {
      getline(cin, line);

      unsigned int neighbours = accumulate(line.begin(), line.end(), 1, [] (unsigned int acum, char c) {
          if (c == ' ') {
            return acum+1;
          } else {
            return acum;
          }
        });

      if (neighbours< min_neigh) {
        min_neigh=neighbours;
        best_places.clear();
        best_places.push_back(i+1);
      } else if (neighbours== min_neigh) {
        best_places.push_back(i+1);
      }

    }

    copy(best_places.begin(), --best_places.end(),
         ostream_iterator<unsigned int>(cout, " "));

    cout << best_places.back() << "\n";

  }

  return 0;
};
