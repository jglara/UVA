#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <memory>

using namespace std;

////////////////////////////////////////
class UF {
  vector<unsigned int> nodes_;

  // return pair with root element of a and distance from root to a
  pair<unsigned int, unsigned int> root(unsigned int a) {
    auto i=a;
    auto length=0;
    for (; nodes_[i] != i; i = nodes_[i]) {
      length++;
    }
    return make_pair(i,length);
  }


public:

  UF(unsigned int nodes) :nodes_(nodes) {
    unsigned int n=0;
    generate(nodes_.begin(), nodes_.end(), [&n] () { return n++; });
  }

  void join(unsigned int a, unsigned int b) {
    auto r1 = root(a);
    auto r2 = root(b);

    if (r1.first !=  r2.first) {
      if (r1.second < r2.second) {
        nodes_[r1.first] = r2.first;
      } else {
        nodes_[r2.first] = r1.first;
      }
    }

  }

  bool check(unsigned int a, unsigned int b) {
    return root(a).first == root(b).first;
  }

};

////////////////////////////////////////
class CommandHandler {
  UF uf_;
  unsigned int count_[2] = {0,0};
  
public:
  CommandHandler(unsigned int nodes) : uf_(nodes) { }
  void join(unsigned int a,unsigned int b) {
    uf_.join(a,b);
  }

  void query(unsigned int a,unsigned int b) {
    count_[uf_.check(a,b)] ++ ;
  }

  friend ostream &operator<<(ostream &ostr, const CommandHandler &chnd); 
};

ostream &operator<<(ostream &ostr, const CommandHandler &chnd) {
  return ostr << chnd.count_[1] << "," << chnd.count_[0];
}

////////////////////////////////////////
class Command
{
public:
  virtual void handle(CommandHandler &hnd)=0;

};

class Connect : public Command {
  unsigned int a_;
  unsigned int b_;
public:
  Connect(unsigned int a, unsigned int b): a_(a), b_(b) { }
  void handle(CommandHandler &hnd) {
    hnd.join(a_,b_);
  }

};

class Query : public Command {
  unsigned int a_;
  unsigned int b_;
public:
  Query(unsigned int a, unsigned int b): a_(a), b_(b) { }
  void handle(CommandHandler &hnd) {
    hnd.query(a_,b_);
  }

};
////////////////////////////////////////
unique_ptr<Command> parse(const string &line) {
      stringstream sstr(line);
      char command;
      unsigned int node1, node2;
      sstr >> command >> node1 >> node2;

      if (command == 'c') {
        return unique_ptr<Command>(new Connect(node1-1,node2-1));
      } else {
        return unique_ptr<Command>(new Query(node1-1,node2-1));
      };
}


////////////////////////////////////////////////////////////////////////////////
int main()
{

  unsigned int tests(0);
  cin >> tests;
  for (;tests>0;--tests) {

    unsigned int nodes(0);
    cin >> nodes;
    CommandHandler chnd(nodes);

    string line;
    getline(cin,line);
    while (getline(cin,line)) {
      if (line.empty()) break;
//      cout << line << "\n";

      parse(line)->handle(chnd);
    }

    cout << chnd << "\n";

    if (tests > 1) {
      cout << "\n";
    }

  }

  return 0;
}
