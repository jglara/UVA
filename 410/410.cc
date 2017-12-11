/*
  Input
Input to this program will be a file with multiple sets of input. The first line of each set will contain
two numbers. The first number (1 ≤ C ≤ 5) defines the number of chambers in the centrifuge and the
second number (1 ≤ S ≤ 2C) defines the number of specimens in the input set. The second line of
input will contain S integers representing the masses of the specimens in the set. Each specimen mass
will be between 1 and 1000 and will be delimited by the beginning or end of the line and/or one or
more blanks.

Output
For each input set, you are to print a line specifying the set number (starting with 1) in the format
‘Set #X’ where X is the set number.
The next C lines will contain the chamber number in column 1, a colon in column number 2, and
then the masses of the specimens your program has assigned to that chamber starting in column 4.
The masses in your output should be separated by exactly one blank.
Your program should then print ‘IMBALANCE = X’ on a line by itself where X is the computed
imbalance of your specimen assignments printed to 5 digits of precision to the right of the decimal.
The final line of output for each set should be a blank line. (Follow the sample output format.)

*/

#include <iostream>
#include <cstdint>
#include <iterator>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <numeric>

using namespace std;

class InputSet {
public:
  InputSet(unsigned int nchambers=0) : chambers_( nchambers, vector<unsigned int>() )  {
  }

  template <class InputIt>
  void addSpecimens(InputIt first, unsigned int n) {
    vector<unsigned int> specimens; specimens.reserve(n);
    copy_n(first, n, back_inserter(specimens));
    vector<unsigned int> sorted_specimens((chambers_.size() * 2) - n, 0);
    copy(specimens.begin(), specimens.end(), back_inserter(sorted_specimens));

    sort(sorted_specimens.begin(), sorted_specimens.end());
    double avgMass=accumulate(specimens.begin(), specimens.end(), 0.0) / chambers_.size();
    imbalance_=0;

    int i(0);
    for(auto &ch: chambers_) {
      while (i <= specimens.size() and specimens[i] == 0) i++;
      if (i >= specimens.size()) break;
      ch.push_back(specimens[i]);
      auto it =find(sorted_specimens.begin(), sorted_specimens.end(), specimens[i]);
      auto pos = sorted_specimens.size() - distance(sorted_specimens.begin(), it) - 1;
      if (sorted_specimens[pos] > 0) {
        ch.push_back(sorted_specimens[pos]);
        auto it1 = find(specimens.begin(), specimens.end(), sorted_specimens[pos]);
        *it1=0;
      }
      *it=0;
      i++;
    }

    imbalance_ = accumulate(chambers_.begin(), chambers_.end(), 0.0, [avgMass] (double acum, const vector<unsigned int> &ch) {
        return acum + abs(accumulate(ch.begin(), ch.end(), 0) - avgMass);
      });

  }

  double imbalance() const {
    return imbalance_;
  };

  typedef vector< vector<unsigned int> >::iterator chamber_iterator;
  typedef vector< vector<unsigned int> >::const_iterator const_chamber_iterator;

  chamber_iterator chamber_begin() { return chambers_.begin(); }
  chamber_iterator chamber_end() { return chambers_.end(); }

  const_chamber_iterator chamber_cbegin() { return chambers_.cbegin(); }
  const_chamber_iterator chamber_cend() { return chambers_.cend(); }

  friend istream &operator>>(istream &istr, InputSet &is);
  friend ostream &operator<<(ostream &ostr, const InputSet &is);

private:
  vector< vector<unsigned int> > chambers_;
  double imbalance_=0.0;

};


////////////////////////////////////////
istream &operator>>(istream &istr, InputSet &is)
{
  is.chambers_.clear();
  unsigned int nchambers(0), nspecimens(0);
  istr >> nchambers >> nspecimens;

  is.chambers_.resize(nchambers);
  is.addSpecimens(istream_iterator<unsigned int>(istr), nspecimens);

  return istr;
}

////////////////////////////////////////
ostream &operator<<(ostream &ostr, const InputSet &is)
{
  unsigned int n(0);
  for (const auto &ch: is.chambers_) {
    ostr << " " << n++ << ":";
    if (ch.size() > 0) {
      ostr << " ";
      copy(ch.begin(), prev(ch.end()), ostream_iterator<unsigned int>(ostr, " "));
      if (ch.size()>0) {
        ostr << ch.back();
      }
    }
    ostr << "\n";
  }

  ostr << "IMBALANCE = " << fixed << setprecision(5) << is.imbalance() << "\n";

  return ostr;
}

int main()
{

  InputSet is;
  uint16_t n(1);
  while (cin >> is) {
    // if (n>1) {
    //   cout << "\n";
    // }

    cout << "Set #" << n++ << "\n";
    cout << is << "\n";
  }

}
