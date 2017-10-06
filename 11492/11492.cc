#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <functional>
#include <limits>
#include <algorithm>
#include <iterator>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
class LangHnd {
  unordered_map<string, unsigned int> langs_;
  
public:
  unsigned int getId(string &lang) {
    auto it = langs_.find(lang);
    if (it == langs_.end()) {
      unsigned int id=langs_.size();
      langs_[lang]= id;
      return id;
    } else {
      return it->second;
    }
  }

  unsigned int size() const { return langs_.size(); }
  
};
  
////////////////////////////////////////
struct Edge {
  unsigned int from_;
  unsigned int to_;
  unsigned int w_; // weight
  char fl_; //first letter

  Edge(unsigned from, unsigned int to, unsigned int w, char firstLetter) :
    from_(from), to_(to), w_(w), fl_(firstLetter) { }
  friend bool operator==(const Edge &lhs, const Edge &rhs);
};

bool operator==(const Edge &lhs, const Edge &rhs)
{
  return (lhs.to_ == rhs.to_) and (lhs.w_ == rhs.w_) and (lhs.fl_ == rhs.fl_);
}
////////////////////////////////////////


struct NodeDistance
{
  unsigned int id_;
  unsigned int distance_;
  char letter_;

  NodeDistance(unsigned int id, unsigned int d, char l) : id_(id), distance_(d),letter_(l)  { }

  friend bool operator>(const NodeDistance &lhs, const NodeDistance &rhs);
  
};

bool operator>(const NodeDistance &lhs, const NodeDistance &rhs)
{
  return lhs.distance_ > rhs.distance_;
}

int main()
{

  unsigned int nwords(0);
  while (cin>>nwords && nwords>0) {
    LangHnd langs;
    string src,dst;
    // read src,dst
    cin >> src >> dst;
    unsigned int srcId(langs.getId(src));
    unsigned int dstId(langs.getId(dst));

    // read words
    unordered_multimap<unsigned int, Edge> wG; // words graph
    for(;nwords>0;--nwords) {
      string lang, word;

      cin >> lang;
      unsigned int lang1_id = langs.getId(lang);

      cin >> lang;
      unsigned int lang2_id = langs.getId(lang);
      cin >> word;

      wG.insert(make_pair(lang1_id, Edge(lang1_id, lang2_id, word.size(), word[0])));
      wG.insert(make_pair(lang2_id, Edge(lang2_id, lang1_id, word.size(), word[0])));
    }

    if (srcId == dstId) {
      cout << "impossivel\n";
      continue;
    }


    // Find the path from src to dst
    // vector of langId -> char -> distance
    vector< vector<unsigned int> > distance(langs.size(), vector<unsigned int>(256, numeric_limits<unsigned int>::max()) );
    priority_queue<NodeDistance, vector<NodeDistance>,  greater<NodeDistance> >pq;


    // Add the nodes reachable from first node
    distance[srcId] = vector<unsigned int>(256, 0);
    pq.push(NodeDistance(srcId, 0, 0));

    while(!pq.empty()) {
      const NodeDistance nd = pq.top();
      pq.pop();
      // cout << "visiting " << nd.id_ << " d=" << nd.distance_ << " l=" << nd.letter_ << "\n";
      if (nd.id_ == dstId) break;

      // check if node is visited
      if (distance[nd.id_][nd.letter_] > nd.distance_) {
        continue;
      }

      // Add the nodes reachable from this node
      auto range = wG.equal_range(nd.id_);
      for_each(range.first, range.second,
               [&distance, &pq, nd] (const pair<unsigned int, Edge > &kv) {
                 const Edge &e(kv.second);
                 // cout << "Examining " << kv.first << "->" <<kv.second.to_ << " d=" << kv.second.w_ << " l=" <<kv.second.fl_;
                 if (e.fl_ != nd.letter_) {
                   unsigned int new_distance = nd.distance_ + e.w_;
                   if (new_distance < distance[e.to_][e.fl_]) {
                     pq.push(NodeDistance(e.to_, new_distance, e.fl_));
                     distance[e.to_][e.fl_] = new_distance;
                     // cout << ". Added\n";
                   } else {
                     // cout << ". Discarded (distance)\n";
                   }

                 } else {
                   // cout << ". Discarded (letter)\n";
                 }
               });
    }

    // for_each(distance.begin(), distance.end(), [] (const pair<unsigned int,char> &d) {
    //     cout << d.first << " " << d.second << "\n";
    //   });

    unsigned int min_distance = *min_element(distance[dstId].begin(), distance[dstId].end());

    if (min_distance== numeric_limits<unsigned int>::max()) {
      cout << "impossivel\n";
    } else {
      cout << min_distance << "\n";
    }

  };

}
