/*
Input
The input consists of N cases. The first line of the input contains only positive integer N. Then follow
the cases. Each case consists of exactly two lines. At the first line, there are two integers m and k,
1 ≤ k ≤ m ≤ 500. At the second line, there are integers p1, p2, . . . , pm separated by spaces. All these
values are positive and less than 10000000.
Output
For each case, print exactly one line. The line must contain the input succession p1, p2, . . . pm divided
into exactly k parts such that the maximum sum of a single part should be as small as possible. Use
the slash character (‘/’) to separate the parts. There must be exactly one space character between any
two successive numbers and between the number and the slash.
If there is more than one solution, print the one that minimizes the work assigned to the first scriber,
then to the second scriber etc. But each scriber must be assigned at least one book.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <cstdint>
#include <limits>
#include <tuple>
#include <map>
#include <sstream>

using namespace std;

////////////////////////////////////////
class BookCopyAssigner {

public:
  
  template <class InputIt>
  uint32_t assign(uint16_t k,InputIt first, InputIt last) {
    memo_.clear();
    return assign(k,first,last,0);
  }

private:
  template <class InputIt>
  uint32_t assign(uint16_t k,InputIt first, InputIt last, uint16_t from) {

    auto it = memo_.find(make_pair(k,from));
    if (it != memo_.end()) {
//      cout << "using memo " << get<0>(it->first) << "," <<get<1>(it->first)  << "," << get<2>(it->first)  << "=" << it->second << "\n";
      return it->second;
    }

    uint32_t ret_val(0);

    if (k==1) {
      ret_val = accumulate(first+from, last, 0);
      memo_[make_pair(k,from)] = ret_val;
    } else {
      uint32_t global_max_pages(numeric_limits<uint32_t>::max());

      auto k_1= 1;
      auto k_2= k - 1;
      uint32_t pages_k_1=first[from];
      for (uint16_t it=from+k_1; first+it+k_2 <= last; ++it) {

        if (pages_k_1 >global_max_pages) break;

        auto pages_k_2 = assign(k_2, first, last, it);
        memo_[make_pair(k_2,it)] = pages_k_2;
        uint32_t max_pages = max(pages_k_1, pages_k_2);

        if (max_pages<global_max_pages) {
          global_max_pages = max_pages;
        }
        pages_k_1 += first[it];
      }

      ret_val= global_max_pages;
    }

//    cout << "memoizing " << k <<"," << from << "," << to << "=" <<ret_val << "\n";
    return ret_val;

  }

private:
  map< pair<uint16_t, uint16_t>, uint32_t >memo_;

};


////////////////////////////////////////
int main()
{

  uint16_t n_cases(0);
  for(cin >> n_cases ; n_cases>0; --n_cases) {
    uint16_t m(0), k(0);
    cin >> m >> k;

    vector<uint32_t> pages_book; pages_book.reserve(m);
    copy_n(istream_iterator<uint32_t>(cin), m, back_inserter(pages_book));

    // find the min. max, number of pages
    BookCopyAssigner bca;
    auto max_pages = bca.assign(k, pages_book.begin(), pages_book.end());

//    cout << "pages = [" <<max_pages << "]\n";

    uint32_t acum_pages(0);
    uint16_t k_rest(k);

    vector<uint32_t> buf;
    for (auto it= pages_book.rbegin(); it != pages_book.rend(); ++it) {
      if (acum_pages + *it > max_pages) {
        buf.push_back(0);
        acum_pages = 0;
        k_rest--;
      } else if (distance(it, pages_book.rend()) < k_rest) {
        buf.push_back(0);
        acum_pages = 0;
        k_rest--;
      }

      buf.push_back(*it);
      acum_pages+=*it;

    }

    for_each(buf.rbegin(), prev(buf.rend()), [] (uint32_t pages) {
        if (pages == 0) {
          cout << "/ ";
        } else {
          cout << pages << " ";
        }
      });
    cout << buf.front() << "\n";
  }

}
