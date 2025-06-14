#include <iostream>
#include <string>
using namespace std;

int main()
{
    cout << unitbuf;
    cerr << unitbuf;

    while (true) {
        cout << "$ ";

        string input;
        if (!getline(cin, input)) {
            break;
        }
        
        if (input == "exit 0") {
            break;
        }
        else if (input.find("echo ") == 0) { // starts with "echo "
            cout << input.substr(5) << endl;
        }
        else {
            cout << input << ": command not found" << endl;
        }
    }
}
