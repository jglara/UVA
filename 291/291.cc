#include <iostream>
#include <array>
#include <bitset>
#include <stack>

using namespace std;




int main()
{

  array< bitset<5>,5 >sh {
    bitset<5>{"10110"},
    bitset<5>{"10101"},
    bitset<5>{"11011"},
    bitset<5>{"10100"},
    bitset<5>{"01111"}
  };

  string path;
  stack< pair<int,int> > st; // each element is the current node + last visited node
  st.push( make_pair(0,0) );
  path.push_back('1');

  while (!st.empty()) {
    int node= st.top().first;
    int &lastVisitedPath = st.top().second;

    bool backtrack(true);

    // cout << path <<  "+"
    //      << static_cast<char>( node + '1') <<  " "
    //      << "\n";

    if (path.size() == 9) {
      cout << path << "\n";


    } else if (sh[node].any()) {
      for (; lastVisitedPath<5; lastVisitedPath++) {
        if (sh[node][lastVisitedPath]) {
          sh[node][lastVisitedPath] = false;
          sh[lastVisitedPath][node] = false;
          st.push(make_pair(lastVisitedPath,0));
          path.push_back('1'+lastVisitedPath);
          backtrack=false;
          break;
        }
      }
    }

    // backtrack
    if (backtrack) {
      path.pop_back();
      st.pop();

      if (st.empty()) break;
      
      sh[st.top().first][st.top().second] = true;
      sh[st.top().second][st.top().first] = true;
      st.top().second++;
    }

  }


  return 0;
}
