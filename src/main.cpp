#include <iostream>
#include <string>
using namespace std;

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
        else if (input.substr(0, 5) == "type ")
        {
            cout << "Showing info about " << input.substr(5) << endl;
        } else if (input.substr(0,9)== "type echo" || input .substr(0,9) || input.substr(0,9)=="type type") {
          cout << input.substr(5) + " is a shell builtin" << std::endl;

        }
        else
        {
            cout << input << ": command not found" << endl;
        }
    }
}
