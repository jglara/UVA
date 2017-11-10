/**
 Write a program that will select the longest strictly increasing subsequence from a sequence of integers.
 
Input
The input file will contain a sequence of integers (positive, negative, and/or zero). Each line of the
input file will contain one integer.

Output
The output for this program will be a line indicating the length of the longest subsequence, a newline,
a dash character (‘-’), a newline, and then the subsequence itself printed with one integer per line. If
the input contains more than one longest subsequence, the output file should print the one that occurs
last in the input file.
Hint: Notice that the second 8 was not included — the subsequence must be strictly increasing

*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>

using namespace std;

////////////////////////////////////////
class LSIS {

  struct TreeNode {
    int value_;
    int parentIndex_;
    TreeNode(int value, int parentIndex) : value_(value), parentIndex_(parentIndex) { }
  };

  vector<TreeNode> nodes_; // All values are stored here
  vector<int> ends_; // only end of active sequences are stored here, pointing to the TreeNode index of the last element in the sequence
 
  
public:

  void add(int value) {
    if (nodes_.empty()) { // First node inserted
      nodes_.emplace_back(value, -1);
      ends_.push_back(0);
      return;
    } else if ( nodes_[ ends_.front() ].value_ >= value) { // new lower element
      ends_[0] = nodes_.size();
      nodes_.emplace_back(value, -1);
    } else if (nodes_ [ ends_.back() ].value_ < value) { // extend the longest list
      int parentIndex = ends_.back();
      ends_.push_back(nodes_.size());
      nodes_.emplace_back(value, parentIndex);
    } else { // find the list that should be extended
      int newIndex=nodes_.size();
      nodes_.emplace_back(value, -1);

      auto it = lower_bound(ends_.begin(), ends_.end(), newIndex, [this] (int index1, int index2) {
          return (nodes_[index1].value_ < nodes_[index2].value_ ) ;
        });

      *it = newIndex; // replace the list end
      nodes_[newIndex].parentIndex_ =  *(--it); // parent is the previous one

    }

  }


  void printLongest() {
    cout << ends_.size() << "\n-\n";
    vector<int> sequence; sequence.reserve(ends_.size());
    for (int i=ends_.back(); i!=-1; i = nodes_[i].parentIndex_) {
      sequence.push_back(nodes_[i].value_);
    };

    // print sequence
    copy(sequence.rbegin(),
         sequence.rend(),
         ostream_iterator<int>(cout, "\n"));
  }

};



// ////////////////////////////////////////
// class LSIS {

//   struct node {
//     unsigned int len_;
//     int parentIndex_;
//     int value_;

//     node(unsigned int len, int parentIndex, int value) : len_(len), parentIndex_(parentIndex), value_(value) { }
//   };

//   vector<node> nodes_;

//   unsigned int longestLen_;
//   int longestIndex_;

// public:
//   LSIS() : longestLen_(0), longestIndex_(0) { }

//   // Add a value and update the longest sequence
//   void add(int value) {
//     unsigned int len=1;
//     int parentIndex= -1;

//     for (auto it=nodes_.begin(); it!= nodes_.end(); ++it) {
//       if ((value > it->value_) and (len < (it->len_+1))) {
//         len = it->len_+1;
//         parentIndex= distance(nodes_.begin(), it);
//       }
//     }

//     nodes_.emplace_back(len,parentIndex,value);

//     if ((len > longestLen_) or
//         ((len == longestLen_) and (value < nodes_[longestIndex_].value_))) {
//       longestLen_ = len;
//       longestIndex_= nodes_.size()-1;
//     }
//   };

//   //
//   void printLongest() {
//     cout << longestLen_ << "\n-\n";
//     auto it=longestIndex_;
//     vector<int> sequence;
//     do {
//       sequence.push_back(nodes_[it].value_);
//       it = nodes_[it].parentIndex_;
//     } while (it != -1);

//     // print sequence
//     copy(sequence.rbegin(),
//          sequence.rend(),
//          ostream_iterator<int>(cout, "\n"));
//   }


// };

int main()
{
  // Read the sequence

  LSIS lsis;
  
  for_each(istream_iterator<int>(cin),
           istream_iterator<int>(),
           [&lsis] (int n) { lsis.add(n); }
    );

  lsis.printLongest();

}
