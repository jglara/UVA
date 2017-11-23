/*
You have a long drive by car ahead. You have a tape recorder, but unfortunately your best music is on
CDs. You need to have it on tapes so the problem to solve is: you have a tape N minutes long. How
to choose tracks from CD to get most out of tape space and have as short unused space as possible.
Assumptions:
• number of tracks on the CD does not exceed 20
• no track is longer than N minutes
• tracks do not repeat
• length of each track is expressed as an integer number
• N is also integer
  
Program should find the set of tracks which fills the tape best and print it in the same sequence as
the tracks are stored on the CD

 Input
Any number of lines. Each one contains value N, (after space) number of tracks and durations of the
tracks. For example from first line in sample data: N = 5, number of tracks=3, first track lasts for 1
minute, second one 3 minutes, next one 4 minutes

Output
Set of tracks (and durations) which are the correct solutions and string ‘sum:’ and sum of duration
times.
 */

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

template <class InputIt>
class CDChooser
{
private:
  InputIt first_;
  InputIt last_;
  unsigned int tapeSize_;

  unsigned int bestSize_;
  vector<typename InputIt::value_type> bestSelection_;
  vector<typename InputIt::value_type> currentSelection_;

  void backtrack(unsigned int currentSize, InputIt current) {
    if ((current == last_) || (currentSize == tapeSize_))  {

      if (currentSize > bestSize_) {
        bestSelection_.assign(currentSelection_.begin(), currentSelection_.end());
        bestSize_ = currentSize;
      }

      return;
    }


    if (currentSize + *current <= tapeSize_) {
      // Try using the current track
      currentSelection_.push_back(*current);
      backtrack(currentSize + *current, next(current));
      currentSelection_.pop_back();
    }

    // try without the current track
    backtrack(currentSize, next(current));

    return;

  };

public:
  CDChooser(InputIt firstTrack, InputIt lastTrack, unsigned int tapeSize) : first_(firstTrack), last_(lastTrack),tapeSize_(tapeSize), bestSize_(0) {
    backtrack(0, first_);
  }


  template < class OutputIt >
  unsigned int getSelection(OutputIt selection)
    {
      copy(bestSelection_.begin(), bestSelection_.end(), selection);

      return bestSize_;
    }

};

int main()
{

  unsigned int tape_length(0);
  while (cin >> tape_length) {
    unsigned int tracks(0);
    cin >> tracks;

    vector<unsigned int>track_lengths; track_lengths.reserve(tracks);

    copy_n(istream_iterator<unsigned int>(cin),
           tracks,
           back_inserter(track_lengths));

    CDChooser< vector<unsigned int>::iterator > cdch(track_lengths.begin(), track_lengths.end(), tape_length);


    unsigned int size = cdch.getSelection(ostream_iterator<unsigned int>(cout, " "));
    cout << "sum:" << size << "\n";

  }

}
