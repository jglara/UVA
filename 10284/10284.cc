#include <iostream>
#include <vector>
#include <map>
#include <cctype>

enum class DIRECTION {
  N,
    S,
    E,
    W,
    NE,
    NW,
    SE,
    SW
    };


class Board {

public:
  static const unsigned char SIZE=8;

  struct PieceMov {
    int deltaRow;
    int  deltaCol;
    bool repeat;

    bool apply(unsigned char &row, unsigned char &col, Board &b) const {
      int irow(row + deltaRow);
      int icol(col + deltaCol);

      if (irow >= Board::SIZE) {
        return false;
      } else if (irow < 0) {
        return false;
      } else if (icol >= Board::SIZE) {
        return false;
      } else if (icol < 0) {
        return false;
      } else if (not b.free(static_cast<unsigned char>(irow), static_cast<unsigned char>(icol))) {
        return false;
      } else {
        row += deltaRow;
        col += deltaCol;
        b.update_attacked(row,col);
      }

      return repeat;
    }

    PieceMov( int dr, int dc, bool r) : deltaRow(dr), deltaCol(dc), repeat(r) { }
    PieceMov(const PieceMov &other) : deltaRow(other.deltaRow), deltaCol(other.deltaCol), repeat(other.repeat) { }
    PieceMov() : deltaRow(0), deltaCol(0), repeat(0) { }
  };

  struct PiecePos {
    unsigned char row;
    unsigned char col;
    char piece;

    static constexpr const char* PIECES="PNBRQKpnbrqk";
    PiecePos(char r, char c, char p) : row(r), col(c), piece(p) { }
  };

  Board() : free_non_attacked_(64) {
    for (unsigned char i=0; i<SIZE; ++i) {
      for (unsigned char j=0; j<SIZE; ++j) {
        free_[i][j] = true;
        attacked_[i][j] = false;
      }
    }
  }


  bool parse(const std::string line) {

    char row=0;
    char col=0;
    for (char c: line) {
      if (std::isdigit(c)) {
          col += (c - '0');
      } else if (c == '/') {
        ++row;
        col=0;
      } else {
        add(PiecePos(row,col,c));
        ++col;
      }
    }

    // generate movements
    for (PiecePos p: pieces_) {
      for(DIRECTION d : piece_directions[p.piece]) {
        unsigned char row(p.row);
        unsigned char col(p.col);
        const PieceMov &pm(piece_direction_mov[ std::make_pair(std::toupper(p.piece), d) ]);
        while(pm.apply(row,col,*this)) {
          ;
        }
      };
    }

    return true;

  }

  unsigned int free_non_attacked() const { return free_non_attacked_; }
  bool free(unsigned char row, unsigned char col) const {
    return free_[row][col];
  }

private:
  static std::map<char, std::vector<DIRECTION> > piece_directions;
  static std::map< std::pair< char, DIRECTION>, PieceMov > piece_direction_mov;

  
  void add(const PiecePos &piece) {
    pieces_.push_back(piece);
    free_[piece.row][piece.col] = false;
    --free_non_attacked_;
  }

  void update_attacked(unsigned char row, unsigned char col) {
    if (not attacked_[row][col]) {
      attacked_[row][col] = true;
      --free_non_attacked_;
    }
  };


  bool free_[SIZE][SIZE];
  bool attacked_[SIZE][SIZE];
  unsigned int free_non_attacked_;

  std::vector<PiecePos> pieces_;

};


std::map<char, std::vector<DIRECTION> > Board::piece_directions  = {
  {'P', {DIRECTION::NW, DIRECTION::NE}},
  {'p', {DIRECTION::SW, DIRECTION::SE}},
  {'N', {DIRECTION::S, DIRECTION::N, DIRECTION::W, DIRECTION::E, DIRECTION::SW, DIRECTION::SE, DIRECTION::NW, DIRECTION::NE}},
  {'B', { DIRECTION::SW, DIRECTION::SE, DIRECTION::NW, DIRECTION::NE}},
  {'R', {DIRECTION::S, DIRECTION::N, DIRECTION::W, DIRECTION::E}},
  {'Q', {DIRECTION::S, DIRECTION::N, DIRECTION::W, DIRECTION::E, DIRECTION::SW, DIRECTION::SE, DIRECTION::NW, DIRECTION::NE}},
  {'K', {DIRECTION::S, DIRECTION::N, DIRECTION::W, DIRECTION::E, DIRECTION::SW, DIRECTION::SE, DIRECTION::NW, DIRECTION::NE}},
  {'n', {DIRECTION::S, DIRECTION::N, DIRECTION::W, DIRECTION::E, DIRECTION::SW, DIRECTION::SE, DIRECTION::NW, DIRECTION::NE}},
  {'b', { DIRECTION::SW, DIRECTION::SE, DIRECTION::NW, DIRECTION::NE}},
  {'r', {DIRECTION::S, DIRECTION::N, DIRECTION::W, DIRECTION::E}},
  {'q', {DIRECTION::S, DIRECTION::N, DIRECTION::W, DIRECTION::E, DIRECTION::SW, DIRECTION::SE, DIRECTION::NW, DIRECTION::NE}},
  {'k', {DIRECTION::S, DIRECTION::N, DIRECTION::W, DIRECTION::E, DIRECTION::SW, DIRECTION::SE, DIRECTION::NW, DIRECTION::NE}},

} ;

std::map< std::pair< char, DIRECTION>, Board::PieceMov > Board::piece_direction_mov = {
  { {'P', DIRECTION::NW}, {-1,-1,0}},
  { {'P', DIRECTION::NE}, {-1,1,0}},
  { {'P', DIRECTION::SW}, {1,-1,0}},
  { {'P', DIRECTION::SE}, {1,1,0}},

  { {'N', DIRECTION::N}, {-2,1,0}},
  { {'N', DIRECTION::S}, {2,-1,0}},
  { {'N', DIRECTION::E}, {1,2,0}},
  { {'N', DIRECTION::W}, {-1,-2,0}},
  { {'N', DIRECTION::NW}, {-2,-1,0}},
  { {'N', DIRECTION::NE}, {-1,2,0}},
  { {'N', DIRECTION::SW}, {1,-2,0}},
  { {'N', DIRECTION::SE}, {2,1,0}},

  { {'B', DIRECTION::NW}, {-1,-1,1}},
  { {'B', DIRECTION::NE}, {-1,1,1}},
  { {'B', DIRECTION::SW}, {1,-1,1}},
  { {'B', DIRECTION::SE}, {1,1,1}},

  { {'R', DIRECTION::N}, {-1,0,1}},
  { {'R', DIRECTION::S}, {1,0,1}},
  { {'R', DIRECTION::E}, {0,1,1}},
  { {'R', DIRECTION::W}, {0,-1,1}},

  { {'Q', DIRECTION::NW}, {-1,-1,1}},
  { {'Q', DIRECTION::NE}, {-1,1,1}},
  { {'Q', DIRECTION::SW}, {1,-1,1}},
  { {'Q', DIRECTION::SE}, {1,1,1}},
  { {'Q', DIRECTION::N}, {-1,0,1}},
  { {'Q', DIRECTION::S}, {1,0,1}},
  { {'Q', DIRECTION::E}, {0,1,1}},
  { {'Q', DIRECTION::W}, {0,-1,1}},

  { {'K', DIRECTION::NW}, {-1,-1,0}},
  { {'K', DIRECTION::NE}, {-1,1,0}},
  { {'K', DIRECTION::SW}, {1,-1,0}},
  { {'K', DIRECTION::SE}, {1,1,0}},
  { {'K', DIRECTION::N}, {-1,0,0}},
  { {'K', DIRECTION::S}, {1,0,0}},
  { {'K', DIRECTION::E}, {0,1,0}},
  { {'K', DIRECTION::W}, {0,-1,0}},

}; 

int main()
{
  std::string line;
  while (std::cin >> line) {
    Board b;
    if (b.parse(line)) {
      std::cout << b.free_non_attacked() << "\n";
    }
  }

  return 0;

}
