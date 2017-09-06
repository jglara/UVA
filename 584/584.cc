#include <iostream>
#include <string>

template <class InputIt>
int calcScore(InputIt it, InputIt end, int finalScore, int frame, int bonus)
{
  if (it == end) return finalScore;

  char roll1(*it++); 
  char roll2('0');
  int points1(0);
  int points2(0);

  if (roll1 == 'X') {
    points1=10;
    points2=0;
  } else {
    points1 = roll1 - '0';
    if (it != end) {
      roll2 = *it++;
    }

    if (roll2 == '/') {
      points2 = 10 - points1;
    } else {
      points2 = roll2 - '0';
    }
  }

//  std::cout << frame << " " << roll1 << " " << roll2 << " " << finalScore << " " << bonus << " - ";

  finalScore += points1 + points2;
  if (roll1 == 'X') {
    if (bonus == 3) {
      finalScore += 2* points1;
      bonus -=2;
    } else if (bonus > 0) {
      finalScore += points1;
      bonus -=1;
    }

  } else {
    if (bonus == 1) {
      finalScore += points1;
    } else if (bonus == 2) {
      finalScore += points1 + points2;
    } else if (bonus == 3) {
      finalScore += 2*points1 + points2;
    }
    bonus = 0;
  }

  if (frame <10) {
    if (roll1 == 'X') {
      bonus +=2;
    } else if (roll2 == '/') {
      bonus += 1;
    }

    frame +=1;

  }

//  std::cout << finalScore << " " << bonus << "\n";

  return calcScore(it, end, finalScore, frame, bonus);

}

int main()
{
    std::string line;
    while(std::getline(std::cin, line)) {
      if (line[0] == 'G') return 0;
      std::string scores;
      for (auto c: line) {
        if (c != ' ') {
          scores.push_back(c);
        }
      }

      int finalScore=calcScore(scores.begin(), scores.end(), 0, 1, 0);
      std::cout << finalScore << '\n';

    }

    return 0;

}
