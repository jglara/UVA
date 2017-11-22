/*
  INPUT

  The graph is given as a set of nodes denoted by numbers
1 . . . n, n ≤ 100, and a set of undirected edges denoted by
pairs of node numbers (n1, n2), n1 ̸= n2.
The input file contains m graphs. The number m is given on the first line. The first line of each
graph contains n and k, the number of nodes and the number of edges, respectively. The following k
lines contain the edges given by a pair of node numbers, which are separated by a space.

OUTPUT

The output should consists of 2m lines, two lines for each graph found in the input file. The first line
of should contain the maximum number of nodes that can be colored black in the graph. The second
line should contain one possible optimal coloring. It is given by the list of black nodes, separated by a
blank.

*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iterator>

using namespace std;

class ColoringState {
  const vector< vector<int> > &graph_;

  unordered_set<int> unpainted_;
  unordered_set<int> blacks_;

  unordered_set<int>::iterator nextNode_;

  ColoringState(const ColoringState &state, int node) : graph_(state.graph_), unpainted_(state.unpainted_), blacks_(state.blacks_) {
    unpainted_.erase(node);

    blacks_.insert(node);

    for_each(graph_[node].begin(), graph_[node].end(), [this] (int node) {unpainted_.erase(node);});

    nextNode_ = unpainted_.begin();
  }

public:
  ColoringState(const vector< vector<int> > &graph) : graph_(graph) {
    for (int node=0; node< graph.size(); ++node) {
      if (!graph[node].empty()) {
        unpainted_.insert(node);
      }
    }
    nextNode_ = unpainted_.begin();
  }

  ColoringState(const ColoringState &other) : graph_(other.graph_), unpainted_(other.unpainted_), blacks_(other.blacks_), nextNode_(unpainted_.begin()) { }
  ColoringState &operator=(const ColoringState &other) {
    if (this == &other) return *this;

    unpainted_ = other.unpainted_;
    blacks_ = other.blacks_;
    nextNode_ = unpainted_.begin();

    return *this;
  }

  bool nextState() const {
    return (nextNode_ != unpainted_.end());
  }

  ColoringState getNextState() {
    ColoringState nextState(*this, *nextNode_);
    nextNode_++;

    return nextState;
  }

  const unordered_set<int> &blacks() const { return blacks_;}



};

ColoringState backtrack(ColoringState state) {

  if (!state.nextState()) {
    return state;
  }

  ColoringState best(state);
  while(state.nextState()) {
    ColoringState next= backtrack(state.getNextState());
    if (next.blacks().size() > best.blacks().size()) {
      best = next;
    }
  }

  return best;
}

const unsigned int MAX_NODES=100;
int main()
{

  int m_graphs(0);

  cin >> m_graphs;
  for (;m_graphs>0; --m_graphs) {
    int n_nodes(0);
    int k_edges(0);
    cin >> n_nodes >> k_edges;

    vector< vector<int> >graph(MAX_NODES, vector<int>());
    for(;k_edges>0; --k_edges) {
      int from(0);
      int to(0);

      cin >> from >> to;
      graph[from].push_back(to);
      graph[to].push_back(from);
    }

    ColoringState initial(graph);
    ColoringState maxCS=backtrack(initial);

    // print the solution
    cout << maxCS.blacks().size() << "\n";
    if (!maxCS.blacks().empty()) {
      copy(maxCS.blacks().begin(), maxCS.blacks().end(), ostream_iterator<int>(cout, " "));
      cout << "\n";
    }

    // if (m_graphs>1) {
    //   cout << "\n";
    // }

  }

}
