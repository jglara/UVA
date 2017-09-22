#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

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

  unsigned int N;
  cin >> N;
  cin.ignore(100,'\n');
  for (;N>0;--N) {

    // Read train length
    unsigned int len(0);
    cin >> len;
    cin.ignore(100,'\n');

    vector<unsigned int> train; train.reserve(len);
    copy_n(istream_iterator<unsigned int>(cin),
           len,
           back_inserter(train));
    cin.ignore(100,'\n');

    auto swaps = count_inversions(train.begin(), train.end());

    cout << "Optimal train swapping takes " << swaps << " swaps.\n";


  }


  return 0;

}
