/*
 Input 
The first line of input will contain number of test cases T.
For each test case:
The first part of the description will be of the pirate land. There could be up to N (1 ≤ N ≤ 1024000)
pirates. Each pirate is either assigned to Buccaneer or Barbary Pirate. Buccaneer pirates are described
by ‘1’ (ONE) and Barbary pirates are described by ‘0’ (ZERO). You have to build a string of the
pirates description. Each case starts with an integer M (M ≤ 100), where M pair lines follow. In each
pair of lines (we call it a set), first has an integer T (T ≤ 200) and next one has a nonempty string
Pirates (consisting of 0 and 1, 0 for Barbary, 1 for Buccaneer, has maximum length of 50). For each
pair concatenate the string Pirates, T times. Concatenate all the resulting M sets of strings to build
the pirate description. The final concatenated string describes the pirates from index 0 to end (N − 1
for N pirates).
Now the next part of the input will contain queries. First line of next part has an integer Q
describing number of queries. Each subsequence Q (1 ≤ Q ≤ 1000) lines describe each query. Each
query has a string F or E or I or S and two integers, a and b denoting indexes. The meaning of the
query string are follows:
F a b, means, mutate the pirates from index a to b to Buccaneer Pirates.
E a b, means, mutate the pirates from index a to b to Barbary Pirates.
I a b, means, mutate the pirates from index a to b to inverse pirates.
S a b, means, “God’s query” God is asking a question: “Tell me, how many Buccaneer pirates are
there from index a to b?”
(a ≤ b, 0 ≤ a < n, 0 ≤ b < n, index range are inclusive)

Output
For each test print the case number as the sample output suggests. Then for each of God’s query,
output the query number, colon (:) and a space and the answer to the query as the sample suggest.

*/

#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;


class Interval {
  unsigned int l_;
  unsigned int r_;

public:
  Interval(unsigned int l, unsigned int r): l_(l), r_(r) {
    if (r_ < l_) r_ = l_;
  }

  unsigned int l() const { return l_;}
  unsigned int r() const { return r_;}

  unsigned int mid() const {
    return l_+(r_-l_)/2;
  };

  unsigned int size() const {
    return r_ - l_;
  }

  Interval intersect (const Interval &i) const {
    return Interval(std::max(i.l_, l_), std::min(i.r_, r_));
  }

  friend bool operator==(const Interval &a, const Interval &b);

};

bool operator==(const Interval &a, const Interval &b)
{
  return (a.l_ == b.l_) and (a.r_ == b.r_);
}

////////////////////////////////////////
class PirateMagic {
  vector<unsigned int> ranges_;
  unsigned int n_;

  unsigned int next_power(unsigned int n) {
    unsigned int k=1;
    while (k<n) {
      k *= 2;
    } 
    return k;
  }

  struct RangeNode {
    unsigned int pos_;
    Interval interval_;

    RangeNode(unsigned int pos, Interval i) : pos_(pos), interval_(i) { }

    RangeNode left() const {
      return RangeNode(pos_*2+1, Interval(interval_.l(), interval_.mid()));
    };

    RangeNode right() const {
      return RangeNode (pos_*2+2, Interval(interval_.mid(), interval_.r()));
    };

  };

  RangeNode root() const {
    return RangeNode(0, Interval(0,n_));
  }

  ////////////////////
  template <class RandomIt>
  void compile(const RangeNode &n, RandomIt first, RandomIt last) {

    unsigned int d=distance(first,last);
    if (d == 0) {
      ;
    } else if (d == 1) {
      ranges_[n.pos_] = *first;
    } else {
      // recurse
      RangeNode rleft(n.left());
      RangeNode rright(n.right());
      compile(rleft, first, first+d/2);
      compile(rright, first+d/2, last);

      ranges_[n.pos_] = ranges_[rleft.pos_] + ranges_[rright.pos_];
    }

  }

  ////////////////////
  unsigned int query_helper(const RangeNode &n, const Interval &i) const {
    Interval i_n= i.intersect(n.interval_);

    if (i_n.size() == 0) {
      return 0;
    } else if (i_n == n.interval_) {
      return ranges_[n.pos_];
    } else {
      return query_helper( n.left(), i_n) + query_helper( n.right(), i_n);
    }
  }

  ////////////////////
  template <class UnaryFunction>
  void change_helper(const RangeNode &n, const Interval &i, UnaryFunction f) {

    if (n.interval_.size() == 1) {
      //cout << "Ch: (" << static_cast<int>(ranges_[n.pos_]) << ")" << i_n.l() <<" <- " << f(ranges_[n.pos_]) << "\n"; 
      ranges_[n.pos_] = f(ranges_[n.pos_]);

    } else {
      // recurse
      RangeNode rleft(n.left());
      RangeNode rright(n.right());
      Interval il(rleft.interval_.intersect(i));
      Interval ir(rright.interval_.intersect(i));

      if (il.size()>0) {
        change_helper(rleft, il, f);
      }

      if (ir.size()>0) {
        change_helper(rright, ir, f);
      }

      ranges_[n.pos_] = ranges_[rleft.pos_] + ranges_[rright.pos_];

    }
  }
 

public:

  template <class RandomIt>
  void assign(RandomIt first, RandomIt last) {
    // copy(first, last, ostream_iterator<unsigned int>(cout, ""));cout << "\n";

    ranges_.clear();
    n_= distance(first,last);
    ranges_.resize(2*next_power(n_)-1);

    compile(root(), first, last);
  }

  unsigned int query(const Interval &i) const {
    return query_helper(root(), i);
  };

  template <class UnaryFunction>
  void change(const Interval &i, UnaryFunction f) {
    change_helper(root(), i, f);
  }

  friend istream &operator>>(istream &istr, PirateMagic &pm);

};


istream &operator>>(istream &istr, PirateMagic &pm) {
  unsigned int m_pairs(0);
  vector<unsigned char> initialState;
  istr >> m_pairs;
  // Read the initial state
  for (;m_pairs>0;--m_pairs) {
    unsigned int T(0);
    string str;
    istr >> T >> str;
    for (;T>0;--T) {
      transform(str.begin(), str.end(), back_inserter(initialState), [] (char c) { return c - '0'; } );
    }
  }

  pm.assign(initialState.begin(), initialState.end());

  return istr;
};


////////////////////////////////////////
class PirateCommand {
  char type_;
  Interval t_;
public:
  PirateCommand() :type_('N'), t_(0,0) { }
  PirateCommand(char type, unsigned int a, unsigned int b) : type_(type), t_(a,b) { }
  char type() const { return type_;}
  const Interval &interval() const {return t_;}

  friend istream& operator>>(istream& istr, PirateCommand &cmd);
};

istream& operator>>(istream& istr, PirateCommand &cmd)
{
  char type;
  unsigned int a(0);
  unsigned int b(0);

  istr >> type >> a >> b;
  cmd.type_ = type;
  cmd.t_ = Interval(a,b+1);

  return istr;

}

////////////////////////////////////////
class CommandHandler {
  unsigned int query_;
public:
  CommandHandler() : query_(0) { }

  void process(PirateMagic &pm, const PirateCommand &cmd) {
    // cout << " t: " << cmd.type() << " a= " << cmd.interval().l() << " b= " << cmd.interval().r() <<"\n";

    switch (cmd.type()) {
    case 'F':
      pm.change(cmd.interval(), [] (unsigned char i) { return 1;});
      break;
    case 'E':
      pm.change(cmd.interval(), [] (unsigned char i) { return 0;});
      break;
    case 'I':
      pm.change(cmd.interval(), [] (unsigned char i) { return (i+1)%2;});
      break;
    case 'S':
      query_++;
      cout << "Q" << query_ << ": " << pm.query(cmd.interval()) << "\n";
      break;

    };
  };


};

int main()
{
  unsigned int testcases(0);
  cin >> testcases;
  for (unsigned int testcase=1;testcase <=testcases;testcase++) {

    // read the initialState
    PirateMagic pm;
    cin >> pm;

    CommandHandler hnd;

    cout << "Case "<< testcase << ":\n";
    // Read the commands
    unsigned int T(0);
    cin >> T;
    for (auto it=istream_iterator<PirateCommand>(cin);
         ;
         it++) {

      hnd.process(pm,*it);
      if (--T==0) break;

    }

  }

}
