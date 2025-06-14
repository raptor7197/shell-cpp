#include <iostream>
#include <string>
using namespace std;

int main()
{
  cout << unitbuf;
  cerr << unitbuf;

  cout << "$ ";

  string input;
  getline(cin, input);
  if (input == "exit 0")
  {
    exit(0);
  } else if (input.find("echo")  != string::npos)
  {
    cout << input.substr(5) << endl;
  }

  cout << input << ": command not found" << endl;
  main();
}
