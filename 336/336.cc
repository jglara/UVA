#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

////////////////////////////////////////
class Graph {
  unordered_map<unsigned int, vector<unsigned int> >adj_;

public:
  typedef vector<unsigned int>::const_iterator constVertexIterator;
  void add(unsigned int from, unsigned int to)
    {
      if (from == to) {
        adj_[from];
      } else {
        adj_[from].push_back(to);
        adj_[to].push_back(from);
      }
    }

  unsigned int V() const {
    return adj_.size();
  }

  bool exists(unsigned int from) const {
    return (adj_.find(from) != adj_.end());
  }

  constVertexIterator adjBegin(unsigned int from) const {
      return adj_.at(from).begin();
  }

  constVertexIterator adjEnd(unsigned int from) const {
    return adj_.at(from).end();
  }

};

////////////////////////////////////////
unsigned int find_nodes_from(const Graph &g, unsigned int from, unsigned int ttl)
{

  queue< pair<unsigned int, unsigned int> >pending;
  unordered_set< unsigned int > visited;

  pending.push(make_pair(from,ttl));

  while(!pending.empty()) {
    unsigned int vertex = pending.front().first;
    unsigned int ttl= pending.front().second;

    if (g.exists(vertex) && visited.find(vertex) == visited.end()) {
      visited.insert(vertex);
      if (ttl>0) {
        for_each(g.adjBegin(vertex), g.adjEnd(vertex), [&pending, ttl](unsigned int vertex)
                 {
                   pending.push( make_pair(vertex, ttl-1));
                 });
      }

    }

    pending.pop();
  }

  return visited.size();
}

////////////////////////////////////////
int main()
{

  unsigned int NC(0);
  unsigned int i(0);
  while (cin >> NC) {
    if (NC == 0) break;

    Graph g;
    // Read graph edges
    for (;NC>0;--NC) {
      unsigned int from(0);
      unsigned int to(0);

      cin >> from >> to;
      g.add(from,to);

    }

    // Read pairs of vertes, ttl
    unsigned int vertex(0);
    unsigned int ttl(0);
    while (cin >> vertex >> ttl) {
      if ((vertex == 0) && (ttl == 0)) break;

      unsigned int nodes=find_nodes_from(g,vertex,ttl);
      // solve the reachability question
      cout << "Case "<< ++i << ": " << g.V() - nodes << " nodes not reachable from node " << vertex << " with TTL = " << ttl << ".\n";
    }

  }

}
