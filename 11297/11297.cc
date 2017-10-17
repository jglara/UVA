/**
Input
In the first line you will find N (0 ≤ N ≤ 500), in following the N lines you will be given N numbers,
wich represent, the initial population of city C[i, j]. In the following line is the number Q (Q ≤ 40000),
followed by Q lines with queries:
There are two possible queries:
• ‘q x1 y1 x2 y2’ which represent the coordinates of the upper left and lower right of where you
must calculate the maximum and minimum change in population.
• ‘c x y v’ indicating a change of the population of city C[x, y] by value v.

Output
For each query, ‘q x1 y1 x2 y2’ print in a single line the greatest and least amount of current population.
Separated each output by a space.
*/

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <limits>

using namespace std;

struct Point {
  unsigned int x_;
  unsigned int y_;

  Point(unsigned int x, unsigned int y) : x_(x), y_(y) { }

};

bool operator<(const Point &p1, const Point &p2)
{
  return ((p1.x_ < p2.x_) and (p1.y_ < p2.y_));
}

bool operator<=(const Point &p1, const Point &p2)
{
  return ((p1.x_ <= p2.x_) and (p1.y_ <= p2.y_));
}


bool operator==(const Point &p1, const Point &p2) {
  return (p1.x_ == p2.x_) and (p1.y_ == p2.y_);
}

struct Square {
  Point l_;
  Point r_;

  Square(Point l, Point r) : l_(l), r_(r) {
    if (!(l_ < r_)) { r_=l_;}
  }

  unsigned int cells() const {
    return (r_.x_ - l_.x_) * (r_.y_ - l_.y_);
  }

  unsigned int deltax() const {
    return r_.x_ - l_.x_;
  }

  unsigned int deltay() const {
    return r_.y_ - l_.y_;
  }

  Square getQuad(unsigned int pos) const {

    unsigned int mid_delta_x= deltax() / 2 ;
    unsigned int mid_delta_y= deltay() / 2;

    switch (pos) {
    case 0:
      return Square( l_,
                     Point(l_.x_ + mid_delta_x, l_.y_ + mid_delta_y));

    case 1:
      return Square( Point(l_.x_ + mid_delta_x, l_.y_),
                     Point(r_.x_, l_.y_ + mid_delta_y) );
    case 2:
      return Square( Point(l_.x_ , l_.y_ + mid_delta_y),
                     Point(l_.x_ + mid_delta_x, r_.y_) );

    default:
      return Square( Point(l_.x_ + mid_delta_x, l_.y_ + mid_delta_y),
                     r_);
    }
  }

  bool includes (const Point &p) const {
    return (p < r_) and (l_ <= p);
  };

};


bool operator==(const Square &s1, const Square &s2) {
  return (s1.l_ == s2.l_) and (s1.r_ == s2.r_);
}

Square intersect(const Square &s1, const Square &s2) {
  return Square( Point(max(s1.l_.x_, s2.l_.x_), max(s1.l_.y_, s2.l_.y_)),
                 Point(min(s1.r_.x_, s2.r_.x_), min(s1.r_.y_, s2.r_.y_) ));
}




////////////////////////////////////////
class Census {
  vector< vector<unsigned int> >grid_;
  vector< pair<unsigned int, unsigned int> > ranges_;

  // recalculate max & min in a range
  void recalculate(unsigned int range) {
    ranges_[range].first = std::max( std::max(ranges_[range*4+1].first, ranges_[range*4+2].first),
                                     std::max(ranges_[range*4+3].first, ranges_[range*4+4].first));

    ranges_[range].second = std::min( std::min(ranges_[range*4+1].second, ranges_[range*4+2].second),
                                      std::min(ranges_[range*4+3].second, ranges_[range*4+4].second));
  }


public:
  Census(unsigned int n) : grid_(n, vector<unsigned int>(n, 0))
    {
      unsigned int total_cells(n*n);
      unsigned int k(1);
      unsigned int sum(1);
      while (k<=total_cells) {
        k=k*4;
        sum+=k;
      }



      ranges_.resize(sum);
    }

  ////////////////////////////////////////
  void set(unsigned int x, unsigned int y, unsigned int pop) {
    grid_[y][x] = pop;
  }

  ////////////////////
  unsigned int get(const Point &p) const {
    return grid_[p.y_][p.x_];
  }

  ////////////////////////////////////////
  void compile() {
    compile(0, Square( Point(0,0),
                       Point(grid_.size(), grid_.size())) );
  }

  ////

  void compile(unsigned int range, const Square &s) {
    if(s.cells() == 0) { // empty
      ranges_[range].first = 0;
      ranges_[range].second = numeric_limits<unsigned int>::max();
      
    } else if (s.cells() == 1) { // we reached the leaf: 1 cell
      ranges_[range].second = ranges_[range].first = get(s.l_); // min & max value

    } else {

      for (int i=0; i<4; ++i) {
        compile(range*4 + i + 1, s.getQuad(i));
      }

      // get max and min
      recalculate(range);

    }
  }

  

  ////////////////////////////////////////
  unsigned int max(const Square &s) const {
    return max(0, Square( Point(0,0),Point(grid_.size(), grid_.size())) , s);
  }

  unsigned int max(unsigned int range, const Square &rs, const Square &s) const {
    const Square s2 = intersect(rs, s);

    if (s2.cells() == 0) {
      return 0;
    } else if (s2 == rs) {
      return ranges_[range].first;
    } else {
      unsigned int local_max=0;
      for (int i=0; i<4; ++i) {
        auto m = max(range*4 + i + 1, rs.getQuad(i), s2);
        if (m > local_max) {
          local_max = m;
        }
      }
      return local_max;
    }
  }

  unsigned int min(const Square &s) const {
    return min(0, Square( Point(0,0),Point(grid_.size(), grid_.size())) , s);
  }

  unsigned int min(unsigned int range, const Square &rs, const Square &s) const {
    Square s2 = intersect(rs, s);

    if (s2.cells() == 0) {
      return numeric_limits<unsigned int>::max();
    } else if (s2 == rs) {
      return ranges_[range].second;
    } else {
      unsigned int local_min=numeric_limits<unsigned int>::max();
      for (int i=0; i<4; ++i) {
        auto m = min(range*4 + i + 1, rs.getQuad(i), s2);
        if (m < local_min) {
          local_min = m;
        }
      }
      return local_min;
    }
  }


  ////////////////////////////////////////
  void change(const Point &p, unsigned int pop) {
    change(0,Square( Point(0,0),Point(grid_.size(), grid_.size())),  p, pop);
  }

  void change(unsigned int range, const Square &rs, const Point &p, unsigned int pop) {
    if (rs.cells() == 1) {
      // we have reached the cell limit, update max and min
      ranges_[range].first = ranges_[range].second = pop;
    } else {
      for (int i=0; i<4; ++i) {

        // recalcule the max and min in the quad that contains the point
        const Square s=  rs.getQuad(i);
        if (s.includes(p)) {
          change(range*4 + i +1, s, p, pop);
        }

        // update current max & min
        recalculate(range);

      }
    }
  }

  

};

////////////////////////////////////////
class CensusBuilder {
  unique_ptr<Census> pCensus_;
  unsigned int n_=0;
  unsigned int x_=0;
  unsigned int y_=0;
public:
  void start(unsigned int n)
    {
      pCensus_.reset(new Census(n));
      n_=n;
      x_=0; y_=0;
    }

  // fill by columns
  void add(unsigned int pop) {
    pCensus_->set(x_,y_, pop);

    ++y_;
    if (y_ == n_) {
      y_=0;
      ++x_;
    }
  }

  unique_ptr<Census> census() {
    return move(pCensus_);
  }
};

////////////////////////////////////////
class CensusCommand
{
public:
  virtual void action(Census &c)=0;
  static unique_ptr<CensusCommand> read(istream &istr);
};

////////////////////
class QueryCommand: public CensusCommand {
  const Square s_;

public:
  QueryCommand(const Point &left, const Point &right) : s_(left, right)  { }
  void action(Census &c) {
    cout << c.max(s_) << " " << c.min(s_) << "\n";
  };
};

////////////////////
class ChangeCommand: public CensusCommand {
  const Point p_;
  const unsigned int pop_;
public:
  ChangeCommand(const Point p, unsigned int pop) : p_(p), pop_(pop) { }
  void action(Census &c) {
    c.change(p_, pop_);
  };
};


unique_ptr<CensusCommand> CensusCommand::read(istream &istr) {
  char c;
  istr >> c;
  switch (c) {
  case 'q':
  {
    unsigned int px,py,qx,qy;
    cin >> px >> py >> qx >> qy;
    return unique_ptr<CensusCommand> (new QueryCommand(Point(px-1,py-1), Point(qx,qy)));
  }
  case 'c':
  {
    unsigned int px,py,pop;
    cin >> px >> py >> pop;
    return unique_ptr <CensusCommand> (new ChangeCommand(Point(px-1,py-1) , pop));
  }
  default:
    ;
  }

  return unique_ptr <CensusCommand> (nullptr);
};



////////////////////////////////////////
int main()
{

  unsigned int N(0);
  cin >> N;
  
  CensusBuilder cb;
  cb.start(N);
  unsigned int pop(0);
  for (auto i=N*N;i>0;--i) {
    cin >> pop;
    cb.add(pop);
  }

  auto pCensus = cb.census();
  pCensus->compile();

  // Read the queries
  unsigned int q(0);
  cin >> q;
  for (;q>0;--q) {
    auto pCmd = CensusCommand::read(cin);
    pCmd->action(*pCensus);
  }

}
