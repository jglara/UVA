#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;
int main()
{

  unsigned int N;
  cin >> N;
  for (;N>0;--N) {

    // Read train length
    unsigned int len(0);
    cin >> len;

    vector<unsigned int> train; train.reserve(len);
    copy_n(istream_iterator<unsigned int>(cin),
           len,
           back_inserter(train));

    unsigned int swaps(0);
    if (len>1) {
      for(auto i=train.end()-1; i!=train.begin(); --i) {
        for(auto j=train.begin(); j!=i; ++j) {

          if (*j>*(j+1)) {
            ++swaps;
            swap(*j,*(j+1));
          }
        }
      }
    }

    cout << "Optimal train swapping takes " << swaps << " swaps.\n";


  }


  return 0;

}
