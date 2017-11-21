/*
  INPUT 
  The first line of the input contains the number of datasets,
and it’s followed by a blank line.
Each dataset contains a pair of positive integers separated
by a single space. The numbers represent the square on which
one of the eight queens must be positioned. A valid square
will be represented; it will not be necessary to validate the
input.
To standardize our notation, assume that the upper leftmost
corner of the board is position (1,1). Rows run horizontally
and the top row is row 1. Columns are vertical and
column 1 is the left-most column. Any reference to a square
is by row then column; thus square (4,6) means row 4, column
6.
Each dataset is separated by a blank line.

OUTPUT
Output for each dataset will consist of a one-line-per-solution representation.
Each solution will be sequentially numbered 1 . . . N. Each solution will consist of 8 numbers. Each
of the 8 numbers will be the ROW coordinate for that solution. The column coordinate will be indicated
by the order in which the 8 numbers are printed. That is, the first number represents the ROW in
which the queen is positioned in column 1; the second number represents the ROW in which the queen
is positioned in column 2, and so on.
*/

#include <iostream>
#include <algorithm>
#include <iterator>
#include <array>
#include <iomanip>

using namespace std;

template<class RandomIt>
bool check_columns(RandomIt first, RandomIt last)
{

  for (auto colIt1 = first; colIt1 != last; ++colIt1) {
    for (auto colIt2 = colIt1+1; colIt2 != last; ++colIt2) {
      auto diff_rows = abs(*colIt1 - *colIt2);
      auto diff_columns = distance(first, colIt2) - distance(first, colIt1);
      if (diff_rows == diff_columns) {
        // cout << "Fail same column: (" << *colIt1 << ","  << distance(first,colIt1) << ") <-> ("
        //      << *colIt2 << ","  << distance(first,colIt2) << ")\n";
        return false;
      }
    }
  }

  return true;
}

////////////////////////////////////////
int main()
{
  int datasets(0);
  cin >> datasets;
  for(;datasets>0;--datasets) {
    int row(0);
    int column(0);

    cin >> row >> column;
    column--;

    cout << "SOLN       COLUMN\n";
    cout << " #      1 2 3 4 5 6 7 8\n\n";
    int i(0);
    array<int, 8> candidate = {1,2,3,4,5,6,7,8};
    while(next_permutation(candidate.begin(), candidate.end())) {
      // cout << "Checking ";
      // copy(candidate.begin(), candidate.end(), ostream_iterator<int>(cout, " "));
      // cout << "\n";

      // 1.check fixed queen
      if (candidate[column] != row) {
        // cout << "Fail "<< candidate[column] << "!=" << row << "\n";
        continue;
      }

      // 2. check not two queens in the same column
      if (!check_columns(candidate.begin(), candidate.end())) {
        continue;
      }

      // print candidate
      cout << setw(2) << ++i << "      ";
      copy_n(candidate.begin(), 7, ostream_iterator<int>(cout, " "));
      cout << candidate.back() << "\n";
    }

    if (datasets>1) {
      cout << "\n";
    }
  }
  

}
