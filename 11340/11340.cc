#include <iostream>
#include <algorithm>
#include <iomanip>
#include <numeric>

using namespace std;

int main()
{

  // Read number of tests
  unsigned int tests;
  cin >> tests;
  for (;tests>0; --tests) {

    // Read number of letters
    unsigned int letters;
    cin >> letters;
    unsigned int payment[256] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    cin.get();
    for(;letters>0;--letters) {
      // Read letters value
      char letter;
      unsigned int money;
      cin.get(letter);
      cin >> money;
      payment[static_cast<unsigned char>(letter)] = money;
      cin.get();
    }

    // Read number of lines
    unsigned int lines;
    cin >> lines;
    std::string line;
    long long total(0);
    cin.ignore(100,'\n');
    for(;lines>0;--lines) {
      std::getline(cin,line);

      total += accumulate(line.begin(), line.end(), 0, [payment](long long acum, unsigned char c) {
          return acum + payment[c];
        });
      total += payment['\n'];

      //cout << ": " << total << "\n";
    }

    cout << fixed << setprecision(2) << total/100.0 << "$\n";

  }


}
