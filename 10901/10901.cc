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
  unsigned int cars_[2] = {0,0};

  queue<Event> events_;

public:
  FerrySim(unsigned int t,unsigned int n): delay_(t), capacity_(n) { }

  void add(const Event &e) {
    events_.push(e);
  }

  void run() {
    unsigned int currentTime(0);

    while (!events_.empty()) {

      // execute event
//      cout << "Arrived: t=" << events_.front().time_ << " side: " << ((events_.front().onLeftSide_)?"left":"right") << "\n";
      while (!events_.empty() && events_.front().time_ <= currentTime) {
        cars_[events_.front().onLeftSide_] ++;
        events_.pop();
      }

      // cout << "now= " << currentTime << " cl= " << cars_[true] << " cr= " << cars_[false] << " s= " << ((onLeftSide_)?"left":"right")
      //      << ". next: t=" << events_.front().time_ << "\n";
      unsigned int next_event_time=events_.empty()?-1:events_.front().time_;
      while (currentTime < next_event_time) {
        if(cars_[onLeftSide_] == 0 && cars_[!onLeftSide_] == 0) {
          // just wait
          currentTime = next_event_time;
          break;
        }

        if(cars_[onLeftSide_] > 0) {
          unsigned int cargo = min(capacity_,cars_[onLeftSide_]);
          cars_[onLeftSide_]-=cargo;
          currentTime+=delay_;
          onLeftSide_ = !onLeftSide_;
          fill_n(ostream_iterator<unsigned int>(cout,"\n"), cargo, currentTime);
        } else {

          // change side
          currentTime+=delay_;
          onLeftSide_ = !onLeftSide_;
        }
      }


    }

  };

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

    FerrySim fs(t,n);

    for (;m>0;--m) {

      // Read arrival time,side
      unsigned int arrival_time(0);
      string side;
      cin >> arrival_time >> side;

      fs.add(Event(arrival_time,side[0]=='l'));

    }
    fs.run();

    if (N>1) {
      cout << "\n";
    }

  }



}
