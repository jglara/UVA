#include <iostream>
#include <limits>

int main(void)
{

  unsigned int participants;
  unsigned int budget;
  unsigned int hotels;
  unsigned int weeks;

  while(std::cin >> participants >> budget >> hotels >> weeks) {
    unsigned int best_price=std::numeric_limits<int>::max();
    unsigned int price;
    unsigned int beds;

    while (hotels --) {
      std::cin >> price;
      for (auto i=weeks;i;i--) {
        std::cin>>beds;

        if (beds >= participants)  {
          unsigned int total_price = (price * participants);
          if ((total_price <= budget) and (total_price < best_price)) {
            best_price = total_price;
          }

      }
      }
    }

    if (best_price==std::numeric_limits<int>::max()) {
      std::cout << "stay home\n";
    } else {
      std::cout << best_price << '\n';
    }


  }

}
