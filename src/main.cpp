#include <iostream>
#include <string>
using namespace std;

bool isBuiltin(const string& command)
{
  return command == "echo" || command == "exit" || command == "type";
}

int main()
{
  cout << unitbuf;
  cerr << unitbuf;

  while (true)
  {
    cout << "$ ";

    string input;
    if (!getline(cin, input))
    {
      break;
    }

    if (input == "exit 0")
    {
      break;
    }
    else if (input.find("echo ") == 0)
    {
      cout << input.substr(5) << endl;
    }
    else if (input.substr(0, 5) == "type")
    {
    string command = input.substr(5);
    if (isBuiltin(command))
    {
      cout << command << " is a shell builtin" << '\n';
    }
    else
    {
      cout << command << ": not found" << '\n';
    }
  } else {
     cout << input << ": command not found" << endl;
  }
  }
}
