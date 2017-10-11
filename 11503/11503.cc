#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

////////////////////////////////////////
class UF {
  vector< pair<unsigned int, unsigned int> > nodes_;
  unordered_map<string,unsigned int> names_;

  // return pair with root element of a and distance from root to a
  pair<unsigned int, unsigned int> root(unsigned int a) {
    auto i=a;
    for (; nodes_[i].first != i; i = nodes_[i].first) {
    }
    return nodes_[i];
  }

  unsigned int getId(const string n) {
    auto it = names_.find(n);

    if (it == names_.end()) {
      auto id=names_.size();
      names_[n] = id;
      return id;
    } else {
      return it->second;
    }
  }

public:

  UF(unsigned int nodes) :nodes_(nodes) {
    unsigned int n=0;
    generate(nodes_.begin(), nodes_.end(), [&n] () { return make_pair(n++,1); });
  }

  unsigned int join(const string &n1, const string &n2) {
    auto r1 = root(getId(n1));
    auto r2 = root(getId(n2));

    auto id1 = r1.first;
    auto id2 = r2.first;
    auto w1 = r1.second;
    auto w2 = r2.second;

    if (id1 !=  id2) {
      if (w1 < w2) {
        nodes_[id1].first = id2;
        nodes_[id2].second = w1 + w2;
      } else {
        nodes_[id2].first = id1;
        nodes_[id1].second = w1 + w2;
      }
      return w1 + w2;
    } else {
      return w1;
    }


  }

};


////////////////////////////////////////////////////////////////////////////////
int main()
{

  unsigned int tests(0);
  cin >> tests;
  for (;tests>0;--tests) {
    unsigned int links(0);
    cin >> links;
    UF uf(links*2);

    for (;links>0;--links) {
      string name1, name2;
      cin >> name1 >> name2;
      cout << uf.join(name1,name2) << "\n";
    }

  }
  return 0;
}
