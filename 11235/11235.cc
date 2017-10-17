/**
Input
The input consists of several test cases. Each test case starts with a line containing two integers n and
q (1 ≤ n, q ≤ 100000). The next line contains n integers a1, . . . , an (−100000 ≤ ai ≤ 100000, for each
i ∈ {1, ..., n}) separated by spaces. You can assume that for each i ∈ {1, . . . , n − 1}: ai ≤ ai+1. The
following q lines contain one query each, consisting of two integers i and j (1 ≤ i ≤ j ≤ n), which
indicate the boundary indices for the query.
The last test case is followed by a line containing a single ‘0’.

Output
For each query, print one line with one integer: The number of occurrences of the most frequent value
within the given range.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include <sstream>

using namespace std;

////////////////////////////////////////
class RangeQuery
{

  vector< pair<int, unsigned int> > values_;

  typedef struct {
    vector< pair<int, unsigned int> >::iterator first;
    vector< pair<int, unsigned int> >::iterator last;
    unsigned int count;
  } range_t;

  vector<range_t> ranges_;

  unsigned int next_power(unsigned int n) {
    unsigned int k=1;
    while (k<=n) {
      k *= 2;
    }

    return k;
  }


public:
  RangeQuery(){
    values_.push_back(make_pair(numeric_limits<int>::min(), 0));
  }

  ////////////////////////////////////////
  void push_back(int val) {
    if (val == values_.back().first) {
      values_.back().second ++;
    } else {
      values_.push_back(make_pair(val, values_.back().second+1 ));
    }
  }

  ////////////////////////////////////////
  void compile() {
    unsigned int size= (2 * next_power(values_.size()) ) - 1;
    ranges_.resize(size);

    compile_range(0, values_.begin()+1, values_.end());
  }

  ////////////////////////////////////////////////////////////////////////////////
  void compile_range(
    unsigned int rangePos,
    const vector< pair<int, unsigned int> >::iterator first,
    const vector< pair<int, unsigned int> >::iterator last)
    {
      auto dist = distance(first, last);

      ranges_[rangePos].first = first;
      ranges_[rangePos].last = last;

      if (dist == 0) {
        ranges_[rangePos].count = 0;
      } if (dist == 1) {
        ranges_[rangePos].count = first->second - ((first-1)->second);
      } else {
        auto range1= (rangePos * 2) + 1;
        auto range2= (rangePos * 2) + 2;
        compile_range(range1, first, (first + dist/2));
        compile_range(range2, (first + dist/2), last);
        ranges_[rangePos].count = max (ranges_[range1].count , ranges_[range2].count);
      }
    }

  ////////////////////////////////////////////////////////////////////////////////
  int max_count(unsigned int left, unsigned int right) {
    return max_count(0,left,right);
  }
 
  int max_count(unsigned int rangePos, unsigned int left, unsigned int right) {
    auto range_left = ((ranges_[rangePos].first) - 1)->second ;
    auto range_right = (ranges_[rangePos].last-1)->second;

    left = max(left, range_left);
    right = min(right, range_right);


    if (left >= right) {
      return 0;
    } if ((range_left == left) && (range_right == right)) {
      return ranges_[rangePos].count;
    } else if (distance(ranges_[rangePos].first, ranges_[rangePos].last) == 1 ) {
      // Leaf
      return right-left;
    } else {
      return max( max_count((2*rangePos)+1, left, right),
                  max_count((2*rangePos)+2, left, right));
    }
  }
    

};


////////////////////////////////////////

int main()
{

  unsigned int n(0),q(0);

  for (;;) {
    scanf("%u", &n);
    scanf("%u", &q);

    if (n == 0) break;

    // Read N values
    RangeQuery rq;
    for (;n>0;--n) {
      int val;
      scanf("%d", &val);
      rq.push_back(val);
    }

    rq.compile();

    // Read Q queries
    for (;q>0;--q) {
      unsigned int left, right;
      scanf("%u", &left);
      scanf("%u", &right);

      // print the answer
//      cout << "l=" << left << ":" << right<< "=" ;
      printf("%u\n",rq.max_count(left-1,right));
    }

  }
  

}
