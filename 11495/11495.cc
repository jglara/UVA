#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

using namespace std;

const vector<string> winner{
  "Carlos",
  "Marcelo"
};

template <class RandomIt>
unsigned int count_inversions(RandomIt first, RandomIt last)
{

  if (first == last) {
    return 0;
  } else if (distance(first,last) == 1) {
    return 0;
  }

  // Divide entry
  RandomIt mid = first + distance(first, last)/2;
  vector<typename RandomIt::value_type> tmp1(first,mid);
  vector<typename RandomIt::value_type> tmp2(mid,last);

  auto inv1= count_inversions(tmp1.begin(),tmp1.end());
  auto inv2= count_inversions(tmp2.begin(), tmp2.end());

  // copy(first, last, ostream_iterator<typename RandomIt::value_type>(cout, " "));
  // merge
  auto inv3=0U;
  RandomIt it1(tmp1.begin());
  RandomIt it2(tmp2.begin());
  
  while ((first!=last) && (it1!=tmp1.end()) && (it2!=tmp2.end())) {
    if (*it1 <= *it2) {
      *first++ = *it1++;
    } else {
      *first++= *it2++;
      inv3+=distance(it1,tmp1.end());
    }
  }

  while (it1!=tmp1.end()) {
    *first++ = *it1++;
  }

  while (it2!=tmp2.end()) {
    *first++ = *it2++;
  }

  // cout << ": " << inv1 << "+"  << inv2<<"+"<< inv3<<"\n";
  return inv1+inv2+inv3;

}

int main()
{
  unsigned int n(0);
  while ((cin >> n) && n >0) {
    vector<unsigned int> numbers; numbers.reserve(n);

    // Read n numbers from cin
    copy_n(istream_iterator<unsigned int>(cin),
           n,
           back_inserter(numbers));

    // Count inversions
    auto inv = count_inversions(numbers.begin(), numbers.end());

    // print winner = number of inversions %2
    cout << winner[inv%2] << "\n";

    // copy(numbers.begin(), numbers.end(), ostream_iterator<unsigned int>(cout, " "));
    // cout << "\n";


  }

  return 0;
}
