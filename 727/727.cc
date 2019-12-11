#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

unordered_map<char, int>precedence{
  {'+',1},
  {'-',1},
  {'*',2},
  {'/',2}};

int foo()
{
  return 1;
}

int main()
{

  unsigned int N;
  cin >> N; cin.ignore(100, '\n');
  cin.ignore(100, '\n'); // ignore first line
  for (;N>0;--N) {
    stack<char> oper;

    for (char c=cin.get(); c!='\n' && !cin.eof(); c=cin.get()) {

      switch (c) {
      case '(':
        oper.push(c);
        break;

      case ')':
        while (oper.top() != '(') {
          cout << oper.top(); oper.pop();
        }
        oper.pop(); // extract '('
        break;

      case '+':
      case '-':
      case '*':
      case '/':
        if (oper.empty() || precedence[c] > precedence[oper.top()] )  {
          oper.push(c);
        } else {

          while (!oper.empty() and precedence[c] <= precedence[oper.top()]) {
            cout << oper.top();
            oper.pop();
          }
          oper.push(c);
        }
        break;

      default: // operand
        cout << c;
        break;

      }
      cin.get(); // read the '\n'
    }

    while (!oper.empty()) {
      cout << oper.top();
      oper.pop();
    }
    cout << "\n";

    if (N>1) cout << "\n";
  }
  

}
