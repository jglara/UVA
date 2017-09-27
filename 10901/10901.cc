#include <iostream>
#include <string>
#include <queue>
#include <memory>
#include <algorithm>
#include <iterator>
 

using namespace std;


////////////////////////////////////////
class FerrySim;

struct Event {
  unsigned int time_;
  bool onLeftSide_;

  Event(unsigned int t, bool onLeftSide) : time_(t), onLeftSide_(onLeftSide) { }
};


////////////////////////////////////////
class FerrySim {

  const unsigned int delay_;
  const unsigned int capacity_;

  bool onLeftSide_ = true;
  unsigned int time_=0;

  vector< queue<unsigned int> > cars_{queue<unsigned int>(), queue<unsigned int>()};

  vector<unsigned int> carOutputTimes_;

public:
  FerrySim(unsigned int t,unsigned int n, unsigned int m): delay_(t), capacity_(n) { carOutputTimes_.reserve(m); }

  void addCar(const Event &e) {
    runUntil(e.time_);

    // cout << "Arrived: t=" << e.time_ << " side: " << ((e.onLeftSide_)?"left":"right") << "\n";
    carOutputTimes_.push_back(0); // add a new car in the list, time will be filled when it comes out from the queue
    cars_[ e.onLeftSide_ ].push( carOutputTimes_.size()-1 );
  }

  void runUntil(unsigned int next_event_time) {

    // cout << "now= " << time_ << " cl= " << cars_[true].size() << " cr= " << cars_[false].size() << " s= " << ((onLeftSide_)?"left":"right")
    //      << ". next: t=" << next_event_time << "\n";
    while (time_ < next_event_time) {
      if(cars_[onLeftSide_].empty() && cars_[!onLeftSide_].empty()) {
        // just wait
        time_ = next_event_time;
        break;
      }

      if(!cars_[onLeftSide_].empty()) {
        unsigned int cargo = min(capacity_,static_cast<unsigned int>(cars_[onLeftSide_].size()));
        time_+=delay_;

        for (; cargo!=0; --cargo) {
          carOutputTimes_[ cars_[onLeftSide_].front() ] = time_;
          cars_[onLeftSide_].pop();
        }
        onLeftSide_ = !onLeftSide_;
      } else {

        // change side
        time_+=delay_;
        onLeftSide_ = !onLeftSide_;
      }
    }

  };

  void print() {
    copy(carOutputTimes_.begin(), carOutputTimes_.end(), ostream_iterator<unsigned int>(cout,"\n"));
  }

};

////////////////////////////////////////

int main()
{

  unsigned int N;
  for (cin >> N; N>0; --N) {

    // Read t,n,m
    unsigned int t(0);
    unsigned int n(0);
    unsigned int m(0);

    cin >> n >> t >> m;

    FerrySim fs(t,n,m);

    for (;m>0;--m) {

      // Read arrival time,side
      unsigned int arrival_time(0);
      string side;
      cin >> arrival_time >> side;

      fs.addCar(Event(arrival_time,side[0]=='l'));

    }
    fs.runUntil(-1); // run until it is finished
    fs.print();

    if (N>1) {
      cout << "\n";
    }

  }



}
