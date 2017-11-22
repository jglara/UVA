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
    vector<int> nodes; nodes.reserve(n_nodes);
    for(;k_edges>0; --k_edges) {
      int from(0);
      int to(0);

      cin >> from >> to;
      if (graph[from].empty()) {
        nodes.push_back(from);
      }
      graph[from].push_back(to);

      if (graph[to].empty()) {
        nodes.push_back(to);
      }
      graph[to].push_back(from);
    }

    // SORT nodes by descending number of adj. edges
    sort(nodes.begin(), nodes.end(), [graph] (int node1, int node2) {
        return (graph[node1].size() < graph[node2].size());
      });

    // take nodes one by one, adding to the black list, and adj. to the white list
    vector<int> blacks;
    unordered_set<int> whites;

    for( auto node : nodes) {
      if (whites.find(node) == whites.end()) {
        blacks.push_back(node);
        copy(graph[node].begin(), graph[node].end(), inserter(whites, whites.end()));
      }
    }

    // print the solution
    sort(blacks.begin(), blacks.end());
    cout << blacks.size() << "\n";
    if (!blacks.empty()) {
      copy_n(blacks.begin(), blacks.size()-1, ostream_iterator<int>(cout, " "));
      cout << blacks.back() << "\n";
    }

    // if (m_graphs>1) {
    //   cout << "\n";
    // }

  }

}
