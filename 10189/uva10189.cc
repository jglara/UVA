#include <iostream>
#include <vector>
#include <string>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////
// MineField class
class MineField {
  std::vector< std::vector<char> > board_;
  
public:
  MineField(unsigned int rows, unsigned int cols) :
    board_(rows, std::vector<char>(cols, '0'))
    {

    }

  int rows() const { return board_.size(); }

  void setMine(int row,int col) {
    board_[row][col] = '*';

    for(int r=row==0?0:row-1; r<static_cast<int>(board_.size()) && r <= row+1; ++r) {
      for (int c=col==0?0:col-1; c<static_cast<int>(board_[r].size()) && c<= col+1; ++c) {
        if (board_[r][c] != '*') {
          board_[r][c] += 1;
        }
      }
    }
  }

  void print() const {
    for (auto r: board_) {
      for (auto c: r) {
        std::cout << c;
      }
      std::cout << '\n';
    }
  }

};

////////////////////////////////////////////////////////////////////////////////
// MineFieldReader
MineField parse(std::istream &istr) {
  // parse rows & cols
  int cols(0);
  int rows(0);

  std::string line;
  std::getline(istr, line);

  std::stringstream istrstr(line);

  istrstr >> rows >> cols;
  MineField mf(rows, cols);

  // read rows
  for (int r=0; r<rows; r++) {

    std::getline(istr,line);
    for (unsigned int c=0; c<line.size(); ++c) {
      if (line[c] == '*') {
        mf.setMine(r,c);
      }
    }

  }
  return mf;

}




int main()
{
  unsigned int fields(0);
  while(std::cin) {
    MineField mf=parse(std::cin);
    ++fields;

    if (mf.rows() > 0) {
      if (fields>1) {
        std::cout << "\n";
      }
      std::cout << "Field #" << fields <<":\n";
      mf.print();
    }
  }
}
