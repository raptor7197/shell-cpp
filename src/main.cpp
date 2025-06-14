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
        }
        else
        {
            cout << input << ": command not found" << endl;
        }
    }
}
