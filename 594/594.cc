#include <iostream>
#include <algorithm>
#include <iterator>


using namespace std;

int main()
{

  for_each(istream_iterator<int>(cin),
           istream_iterator<int>(),
           [] (int n) {
             union {
               int n;
               unsigned char n4[4];
             } tmp1, tmp2;

             tmp1.n = n;
             for (int i=0; i <4 ; ++i) {
               tmp2.n4[i] = tmp1.n4[3-i];
             }
             cout << n << " converts to " << tmp2.n << "\n";
           }
    );

}
