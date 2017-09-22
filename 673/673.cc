#include <iostream>
#include <string>
#include <stack>
#include <iterator>

using namespace std;

template <class ForwardIt>
bool checkLine(ForwardIt first, ForwardIt last)
{
  stack<char> st;
  for(auto it=first;it!=last;++it) {
    switch (*it) {
    case '(':
      st.push(')');
      break;
    case '[':
      st.push(']');
      break;
    case ')':
    case ']':
      if (st.empty() || (st.top() != *it)) {
        return false;
      }
      st.pop();
      break;
    default:
      ;
    }
  }

  return st.empty();

}

int main()
{
  unsigned int N(0);
  cin >> N;
  cin.ignore(100,'\n');

  for (;N>0;--N) {
    string line;
    getline(cin,line);
    if (checkLine(line.begin(), line.end())) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return 0;

}
