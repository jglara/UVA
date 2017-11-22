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
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;


void backtrack(vector< vector<int> > &graph, map<int,bool> &colors, unsigned int blacks, vector<int> &best, map<int,bool>::iterator it) {

  // cout << "node= " << it->first << ". blacks= " << blacks<< "\n";
  if (it == colors.end()) {
    // cout << "Finished.. backtracking\n";
    if (blacks >= best.size()) {
      best.clear();
      for_each(colors.begin(), colors.end(), [&best] (const pair<int, bool> &k_v) {
          if (k_v.second) {
            best.push_back(k_v.first);
          }
        });
    }

    return;
  }

  int node= it->first;
  if (any_of(graph[node].begin(), graph[node].end(), [&colors] (int node) {
        return colors[node];})) {

    // cout << "1. paint white " << node <<"\n";
    // paint white and backtrack
    colors[node] = false;
    map<int,bool>::iterator next(it); next++;
    backtrack(graph, colors, blacks, best, next);
  } else {

    map<int,bool>::iterator next(it); next++;

    // paint black
    // cout << "2.1. paint black " << node <<"\n";
    colors[node] = true;
    backtrack(graph, colors, blacks+1, best, next);

    // paint white
    // cout << "2.2. paint white " << node <<"\n";
    colors[node] = false;
    backtrack(graph, colors, blacks, best, next);

  }

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

    vector< vector<int> >graph(MAX_NODES+1, vector<int>());
    map<int,bool> colors;
    for(int i=1;i<=n_nodes;i++) {
      colors[i] = false;
    }
    for(;k_edges>0; --k_edges) {
      int from(0);
      int to(0);

      cin >> from >> to;
      graph[from].push_back(to);
      graph[to].push_back(from);
    }

    vector<int> blacks;
    backtrack(graph, colors, 0, blacks, colors.begin());

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
