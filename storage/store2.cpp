#include <iostream>
#include <string>
#include <unordered_set>
#include <filesystem>

using namespace std;

string cmd_in_path(const string& cmd) ;

int main() {
  cout << unitbuf;
  cerr << unitbuf;
  unordered_set<string> cmds {"exit", "echo", "type"};
  while (true)
  {
    cout << "$ ";

    string input, cmd, args, cmd_path;
    getline(cin, input);
    cmd = input.substr(0, input.find_first_of(' '));
    args = input.substr(input.find_first_of(' ') + 1);

    if(cmd == "exit") {
      exit(stoi(args));
    }
    else if(cmd == "echo") {
      cout << args << endl;
    }
    else if(cmd == "type") {
      if(cmds.find(args) != cmds.end()) {
        cout << args << " is a shell builtin" << endl;
      }
      else if(cmd_path = cmd_in_path(args); !cmd_path.empty()) {
        cout << args << " is " << cmd_path << endl;
      }
      else {
        cout << args << ": not found"<< endl;
      }
    }
    else if(cmd_patch = cmd_in_path(cmd); !cmd_path.empty()) {
        int res = system(input.c_str());
    }
    else {
      cout << input << ": command not found" << endl;
    }
  }
}

string cmd_in_path(const string& cmd) {
  string path = getenv("PATH");
  string search_dir;
  int left_occ = 0;

  for(int i = 0; i < path.size(); i++) {
    if(path[i] == ':') {
      search_dir = path.substr(left_occ, i - left_occ);
      if(filesystem::exists(search_dir + '/' + cmd)) {
        return search_dir + '/' + cmd;
      }
      left_occ = i + 1;
    }
  }

  search_dir = path.substr(path.find_last_of(':'));
  if(filesystem::exists(search_dir + '/' + cmd)) {
        return search_dir + '/' + cmd;
  }

  return "";
}