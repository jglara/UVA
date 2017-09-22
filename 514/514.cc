#include <iostream>
#include <vector>
#include <iterator>
#include <stack>
#include <algorithm>

using namespace std;


int main()
{
  bool first(true);
  unsigned int trainLen;
  while ((cin >> trainLen) && (trainLen > 0)) {
    // if (first) {
    //   first = false;
    // } else {
    //   cout << "\n";
    // }
    cin.ignore(10,'\n');
    while ((cin.peek() != '0')) {
      vector<unsigned int> expected; expected.reserve(trainLen);

      copy_n(istream_iterator<unsigned int>(cin),
             trainLen,
             back_inserter(expected));
      cin.ignore(10,'\n');

      stack<unsigned int> train;
      unsigned int pending(1);
      auto itExpected=expected.begin();
      for (;itExpected != expected.end();
           ++itExpected) {

        auto next=*itExpected;
        if (next==pending) {
          ++pending;
        } else if (next<pending) {
          // pop from top of the stack
          if (next == train.top()) {
            train.pop();
          } else {
            break; // FAIL!
          }
        } else if (next > pending) {
          // push on the stack
          while (next > pending) train.push(pending++);
          pending++;}

      }

      if (itExpected == expected.end()) {
        cout << "Yes\n";
      } else {
        cout << "No\n";
      }

    }
    cin.ignore(10,'\n');
    cout << "\n";

  }

}
