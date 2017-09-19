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
      for(auto i=1U; i<=len; ++i) {
        auto pos=find(train.begin(), train.end(), i);
        swaps+=distance(train.begin(),pos);
        train.erase(pos);
      }
    }

    cout << "Optimal train swapping takes " << swaps << " swaps.\n";


  }


  return 0;

}
