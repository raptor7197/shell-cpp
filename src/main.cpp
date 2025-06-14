#include <iostream>
#include <string>
using namespace std

int main() {
  cout << unitbuf;
  cerr << unitbuf;

  cout << "$ ";

  string input;
  getline(cin, input);
    if (input == "exit 0") exit(0);  

  cout << input << ": command not found" << endl;
  main();
}
