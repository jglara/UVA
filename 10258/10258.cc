#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <iterator>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//
class Submission {
  unsigned int player_;
  unsigned int id_;
  unsigned int time_;
  char veredict_;
public:
  Submission(): player_(0), id_(0), time_(0), veredict_('U') { }
  Submission(const Submission &s) = default;
  Submission &operator=(const Submission &s) = default;
  Submission(unsigned int p, unsigned int id, unsigned int t, char v) :
    player_(p), id_(id), time_(t), veredict_(v) { }

  unsigned int player() const {return player_;}
  unsigned int id() const {return id_;}
  unsigned int time() const {return time_;}
  char veredict() const {return veredict_;}

  friend istream&operator>>(istream &istr, Submission &s);
};

istream&operator>>(istream &istr, Submission &s) {

  unsigned int p;
  unsigned int id;
  unsigned int t;
  char v;

  istr >> p >> id >> t >> v;
  istr.ignore(100,'\n');

  s.player_ = p;
  s.id_ = id;
  s.time_ = t;
  s.veredict_ = v;

  return istr;

};

////////////////////
class ProblemScore {
  bool correct_;
  unsigned int tries_;
  unsigned int penalty_;
  static const unsigned int PENALTY_INCORRECT=20;

public:
  ProblemScore(): correct_(false), tries_(0), penalty_(0) { }
  ProblemScore(const ProblemScore &prev) = default;
  ProblemScore& operator=(const ProblemScore &prev) = default;
  ProblemScore(const ProblemScore &prev, const Submission &s) : correct_(prev.correct_), tries_(prev.tries_), penalty_(prev.penalty_) {
    ++ tries_;
    if (correct_) return;

    switch (s.veredict()) {
    case 'C':
      correct_=true;
      penalty_ += s.time();
      break;
    case 'I':
      penalty_ += PENALTY_INCORRECT;
      break;
    default:
      ;
    }
  }

  bool correct() const {return correct_;}
  unsigned int penalty() const {return penalty_;}
  unsigned int tries() const {return tries_;}

};

////////////////////
class PlayerScore {
  unsigned int player_;
  unsigned int correct_;
  unsigned int incorrect_;
  unsigned int penalty_;
public:
  PlayerScore(unsigned int player) : player_(player), correct_(0), incorrect_(0), penalty_(0) { }
  PlayerScore(const PlayerScore &prev) = default;
  PlayerScore & operator=(const PlayerScore &prev) = default;
  PlayerScore(const PlayerScore &prev, const ProblemScore &prob) : player_(prev.player_), correct_(prev.correct_), incorrect_(prev.incorrect_), penalty_(prev.penalty_) {
    if (prob.correct()) {
      ++correct_;
      penalty_+=prob.penalty();
    } else if (prob.tries() >0) {
      ++incorrect_;
    }
  }

  bool valid() const {return (correct_+ incorrect_)>0;}

  friend bool operator<(const PlayerScore &one, const PlayerScore &two);
  friend ostream &operator<<(ostream &ostr, const PlayerScore &ps);

};

PlayerScore operator+(const PlayerScore &ps, const ProblemScore &prob) {
  return PlayerScore(ps, prob);
}

bool operator<(const PlayerScore &one, const PlayerScore &two) {
  if (one.correct_ != two.correct_) {
    return one.correct_ > two.correct_;
  } else if (one.penalty_ != two.penalty_) {
    return one.penalty_ < two.penalty_;
  } else {
    return one.player_ < two.player_;
  }
}

ostream &operator<<(ostream &ostr, const PlayerScore &ps)
{
  ostr << ps.player_ << " " << ps.correct_ << " " << ps.penalty_;

  return ostr;
}

////////////////////////////////////////////////////////////////////////////////
int main()
{

  unsigned int N;
  cin >> N;
  cin.ignore(100, '\n');
  cin.ignore(100, '\n');
  for (;N>0; --N) {
    static const int MAX_PLAYERS=100;
    static const int MAX_PROBLEMS=9;

    vector< vector< ProblemScore > >players(MAX_PLAYERS, vector< ProblemScore >(MAX_PROBLEMS));
    Submission s;
    // Read submissions
    while (cin.peek()!= '\n' && cin>>s) {
      players[ s.player()-1 ][ s.id()-1 ] = ProblemScore(players[ s.player()-1 ][ s.id()-1 ], s);
    }

    // Extract scores
    set< PlayerScore > scores;
    unsigned int i(0);
    transform( players.begin(), players.end(), inserter(scores, scores.end()),
               [&i](vector< ProblemScore > &prob) -> PlayerScore {

                 return accumulate(prob.begin(), prob.end(), PlayerScore(++i));

               });

    // print
    copy_if(scores.begin(), scores.end(), ostream_iterator<PlayerScore>(cout,"\n"),
            [](const PlayerScore &ps) {
              return ps.valid();
            }
      );

    cin.ignore(100, '\n');
    if (N>1) {
      cout << "\n";
    }

  }

  return 0;
}
