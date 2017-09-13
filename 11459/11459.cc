#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <sstream>


////////////////////////////////////////
// SnakeLadders Game State
class SnakeLadders {
  std::vector< unsigned int >player_; // player positions
  std::unordered_map <unsigned int , unsigned int>jump_;
  unsigned int currentPlayer_;
  bool gameEnd_;

public:
  static const unsigned int BOARD_MAX=100; // BOARD MAX position

  ////////////////////////////////////////
  // Builder interface
  SnakeLadders(unsigned int players) :
    player_(players, 1),
    jump_(BOARD_MAX),
    currentPlayer_(0),
    gameEnd_(false)
    { }

  void addJump(unsigned int from, unsigned int to) {
    jump_[from] = to;
  }
  ////////////////////////////////////////


  ////////////////////////////////////////
  void updateRoll(unsigned int roll) {
    if (gameEnd_) return;

    unsigned int newPos = player_[currentPlayer_];
    newPos += roll;

    // lookup for a jump
    auto jump=jump_.find(newPos);
    if (jump != jump_.end()) {
      newPos = jump->second;
    }

    // test game end
    if (newPos >= BOARD_MAX) {
      newPos = BOARD_MAX;
      gameEnd_ = true;
    }

    player_[currentPlayer_] = newPos;
    currentPlayer_ = (currentPlayer_ + 1) % player_.size();
  }

  ////////////////////////////////////////
  typedef std::vector< unsigned int>::iterator iterator;

  iterator begin() { return player_.begin(); }
  iterator end() { return player_.end(); }

};

////////////////////////////////////////////////////////////////////////////////
void printBoard(SnakeLadders::iterator begin, SnakeLadders::iterator end)
{
  unsigned int player(0);
  std::for_each(begin, end, [&player](unsigned int pos) { std::cout << "Position of player " <<++player<<" is " << pos << ".\n"; });

}

////////////////////////////////////////////////////////////////////////////////
void readSnakeLadders(std::istream &istr)
{
  std::string str;

  
  // Read # players, #jumps, #roll dices
  std::getline(istr, str);
  std::stringstream sstr(str);
  unsigned int players(0);
  unsigned int jumps(0);
  unsigned int rolls(0);
  sstr >> players >> jumps >> rolls;

  SnakeLadders sl(players);

  // Read jumps
  for (unsigned int i=0; i<jumps; i++) {
    std::getline(istr, str);
    std::stringstream sstr(str);

    unsigned int from(0);
    unsigned int to(0);
    sstr >> from >> to;
    sl.addJump(from, to);
  }

  // Read rolls
  for (unsigned int i=0; i<rolls; i++) {
    std::getline(istr, str);
    std::stringstream sstr(str);

    unsigned int roll(0);
    sstr >> roll;

    sl.updateRoll(roll);
  }

  // print final Board
  printBoard(sl.begin(), sl.end());

}


int main()
{
  
  // REad number of tests
  std::string str;
  std::getline(std::cin, str);
  std::stringstream sstr(str);

  unsigned int tests(0);
  sstr >> tests;
  for (unsigned int i=0; i < tests; ++i) {
    readSnakeLadders(std::cin);
  }

}
