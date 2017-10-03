/*
Input
The input will contain several test cases, each of them as described below. Consecutive
test cases are separated by a single blank line.
The input is organized as follows:
• A line containing the number N of computer sites, with 1 ≤ N ≤ 1000000, and where each
computer site is referred by a number i, 1 ≤ i ≤ N.
• The set T of previously chosen high-speed lines, consisting of N − 1 lines, each describing a
high-speed line, and containing the numbers of the two computer sites the line connects and the
monthly cost of using this line. All costs are integers.
• A line containing the number K of new additional lines, 1 ≤ K ≤ 10.
• K lines, each describing a new high-speed line, and containing the numbers of the two computer
sites the line connects and the monthly cost of using this line. All costs are integers.
• A line containing the number M of originally available high-speed lines, with N − 1 ≤ M ≤
N(N − 1)/2.
• M lines, each describing one of the originally available high-speed lines, and containing the numbers
of the two computer sites the line connects and the monthly cost of using this line. All costs
are integers.

Output
For each test case, the output must follow the description below. The outputs of two
consecutive cases will be separated by a blank line.
The output file must have one line containing the original cost of connecting the N computer sites
with T high-speed lines and another line containing the new cost of connecting the N computer sites
with M + K high-speed lines. If the new cost equals the original cost, the same value is written twice.


*/
  
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <queue>

using namespace std;

////////////////////////////////////////
struct Edge {
  unsigned int from_;
  unsigned int to_;
  unsigned int weight_;

  Edge(unsigned int from, unsigned int to, unsigned int weight) : from_(from), to_(to), weight_(weight) { }
  Edge() : from_(0), to_(0), weight_(0) { }
  Edge &operator=(const Edge &e) {
    from_ = e.from_;
    to_ = e.to_;
    weight_ = e.weight_;

    return *this;
  }

  Edge reverse() const {
    return Edge(to_, from_, weight_);
  }
  
  friend bool operator==(const Edge &rhs, const Edge &lhs);
  friend bool operator<(const Edge &rhs, const Edge &lhs);
  friend istream & operator>>(istream &istr, Edge &rhs);
  friend ostream & operator<<(ostream &ostr, const Edge &rhs);

};

bool operator==(const Edge &rhs, const Edge &lhs) {
  return (rhs.to_ == lhs.to_) && (rhs.weight_ == lhs.weight_);
}

bool operator<(const Edge &rhs, const Edge &lhs)
{
  return rhs.weight_ < lhs.weight_;
}

istream & operator>>(istream &istr, Edge &rhs)
{
     istr >> rhs.from_ >> rhs.to_ >> rhs.weight_;

     return istr;
}


ostream & operator<<(ostream &ostr, const Edge &rhs)
{
  ostr << rhs.from_ << " "
       << rhs.to_ << " "
       << rhs.weight_;

  return ostr;
}


int main()
{

  unsigned int n_computer_sites(0); // number of computer sites
  while (cin >> n_computer_sites) {
    if (n_computer_sites == 0) break;

    unordered_map<unsigned int, unsigned int> weights;
    unsigned int mst_cost(0);
    while(n_computer_sites-->1) {
      Edge e;
      cin >> e;
      mst_cost += e.weight_;
      if ((weights[e.to_]==0) or (weights[e.to_] > e.weight_)) {
        weights[e.to_] = e.weight_;
      }

      if ((weights[e.from_]==0) or (weights[e.from_] > e.weight_)) {
        weights[e.from_] = e.weight_;
      }

    }

    cout << mst_cost << "\n";

    // Read K new lines
    unsigned int k_new_lines(0);
    cin >> k_new_lines;
    priority_queue<Edge> new_lines;
    while(k_new_lines-->0) {
      Edge e;
      cin >> e;
      new_lines.push(e);
    }

    // Read M original lines
    unsigned int m_lines(0);
    cin >> m_lines;
    unordered_multimap<unsigned int, Edge> old_lines;
    while(m_lines-->0) {
      Edge e;
      cin >> e;

      old_lines.insert(make_pair(e.from_, e));
      old_lines.insert(make_pair(e.to_, e.reverse()));
    }


    while (!new_lines.empty()) {
      const Edge &e(new_lines.top());
      new_lines.pop();

      // if there is a new way to reach a node, update it
      if (weights[e.to_] > e.weight_) {
        mst_cost -= (weights[e.to_] - e.weight_);
        weights[e.to_] = e.weight_;


        // add the reachable nodes to the list of edges to inspect
        auto range=old_lines.equal_range(e.to_);
        for_each(range.first, range.second,
                 [&new_lines](const pair<unsigned int, Edge> &key_value) {
                   new_lines.push(key_value.second);
                 }
          );
      }
      
    }

    cout << mst_cost << "\n\n";


  }
}
