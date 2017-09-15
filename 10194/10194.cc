#include <cstring>
#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>


////////////////////////////////////////
//
class TeamClassification
{
  int points_;
  int games_;
  int wins_;
  int ties_;
  int losses_;
  int goalsFav_;
  int goalsCon_;

public:

  void update(int goalsFav, int goalsCon) {
    ++games_;
    if (goalsFav > goalsCon) {
      points_ +=3;
      ++wins_;
    } else if (goalsFav == goalsCon) {
      points_ +=1;
      ++ties_;
    } else {
      ++losses_;
    }
    goalsFav_ += goalsFav;
    goalsCon_ += goalsCon;
  }

  int goalDiff() const { return goalsFav_ - goalsCon_; }

  int comp(const TeamClassification &other) const {
    if (points_ != other.points_) {
      return points_ - other.points_;
    } else if (wins_ != other.wins_) {
      return wins_ - other.wins_;
    } else if (goalDiff() != other.goalDiff()) {
      return goalDiff() - other.goalDiff();
    } else if (goalsFav_ != other.goalsFav_) {
      return goalsFav_ - other.goalsFav_;
    } else if (games_ != other.games_) {
      return other.games_ - games_;
    }

    return 0;
  }

  std::string toStr() const {
    std::stringstream str;
    str << points_ << "p, "
        << games_ << "g "
        << "(" << wins_ << "-" << ties_ << "-" << losses_ << "), "
        << goalsFav_ - goalsCon_ << "gd "
        << "(" << goalsFav_ << "-" << goalsCon_ << ")";

    return str.str();
  }

};



////////////////////////////////////////////////////////////////////////////////
// Tournament Reader
class TournamentReader
{

  class TNameState;
  class TTeamsState;
  class TMatchesState;
  ////////////////////////////////////////
  class TReaderState {
  public:
    virtual bool parseLine(TournamentReader &reader, const std::string &line) = 0;
  };


  ////////////////////
  class TNameState : public TReaderState {
  public:
    bool parseLine(TournamentReader &reader, const std::string &line) {
      reader.handleName(line);

      reader.changeState(new TTeamsState());
      return true;
    };
  };
  ////////////////////
  class TTeamsState : public TReaderState {
    int teams_;
  public:
    TTeamsState() : teams_(-1) { }
    bool parseLine(TournamentReader &reader, const std::string &line) {
      if (teams_ == -1) {
        teams_ = atoi(line.c_str());
      } else if (teams_ > 0) {
        reader.handleTeam(line);
        --teams_;
      }

      if (teams_ == 0) {
        reader.changeState(new TMatchesState());
      }

      return true;
    };
  };

  ////////////////////
  class TMatchesState : public TReaderState {
    int matches_;
  public:
    TMatchesState() : matches_(-1) { }
    bool parseLine(TournamentReader &reader, const std::string &line) {
      if (matches_ == -1) {
        matches_ = atoi(line.c_str());
      } else if (matches_ >0)  {
        char team1[100];
        char goals1[10];
        char team2[100];
        char goals2[10];
        sscanf(line.c_str(), "%[^#]#%[0-9]@%[0-9]#%[^#]", team1, goals1, goals2, team2);

        reader.handleMatch(team1, atoi(goals1), team2, atoi(goals2));
        --matches_;
      }

      return matches_ > 0;
    };
  };
  ////////////////////////////////////////

  std::map<std::string, TeamClassification> teams_;
  std::unique_ptr<TReaderState> state_;
public:

  TournamentReader() : state_( new TNameState()) { }
  bool parseLine(std::string &line) {
    return state_->parseLine(*this, line);
  }

  void changeState(TReaderState *next) {
    state_.reset(next);
  }

  void handleName(const std::string &name) {
    std::cout << name << "\n";
  }

  void handleTeam(const std::string &name) {
    teams_[name]=TeamClassification();
  }

  void handleMatch(const char *team1, int goals1, const char *team2, int goals2) {
    teams_[team1].update(goals1, goals2);
    teams_[team2].update(goals2, goals1);
  }

  void print() {
    std::vector< std::pair<std::string, TeamClassification> >ordered_teams( teams_.begin(), teams_.end());

    std::sort(ordered_teams.begin(), ordered_teams.end(),
              [] (const std::pair<std::string, TeamClassification> &t1,
                  const std::pair<std::string, TeamClassification> &t2) {
                int cmp=t2.second.comp(t1.second);

                if (cmp == 0) {
                  return strcasecmp(t1.first.c_str(), t2.first.c_str()) < 0;
                } else {
                  return cmp <0;
                }
              });

    unsigned int i(0);
    std::for_each(ordered_teams.begin(), ordered_teams.end(),
                  [&i] (const std::pair<std::string, TeamClassification> &t1) {
                    std::cout << ++i << ") " << t1.first << " " << t1.second.toStr() << "\n" ;
                  });
                  
  }

};




int main()
{

  // Read number of tournaments
  unsigned int n;
  std::cin >> n;

  std::string line;
  std::getline(std::cin, line);

  for (;n>0;--n) {
  
    TournamentReader tr;
    
    while (std::getline(std::cin, line)) {
      if (!tr.parseLine(line)) {
        tr.print();
        break;
      }
    }

    if (n>1) {
      std::cout << "\n";
    }
  }
}
