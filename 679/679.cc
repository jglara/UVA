#include <iostream>
#include <iterator>
#include <algorithm>
#include <cstdint>

using namespace std;

uint32_t calculate_result(uint32_t node, uint32_t tree_height, uint32_t balls)
{

  if (balls == 1) {
    return node * (1 << (tree_height-1));
  } else if (balls%2) {
    // ODD: going left
    return calculate_result(2*node, tree_height-1, (balls/2)+1);

  } else {
    // EVEN: going right
    return calculate_result((2*node)+1, tree_height-1, balls/2);


  }
}

////////////////////////////////////////
int main()
{

  uint32_t testcases(0);
  cin >> testcases;
  for(;testcases>0;--testcases) {
    uint32_t tree_height(0);
    uint32_t balls(0);

    cin >> tree_height >> balls;

    cout << calculate_result(1, tree_height, balls) << "\n";

  }

}

