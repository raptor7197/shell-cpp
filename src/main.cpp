#include <iostream>
#include <string>
#include <unordered_set>
#include <filesystem>

std::string cmd_in_path(const std::string& cmd) ;

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  std::unordered_set<std::string> cmds {"exit", "echo", "type"};
  // Uncomment this block to pass the first stage
  while (true)
  {
    std::cout << "$ ";

    std::string input, cmd, args, cmd_path;
    std::getline(std::cin, input);
    cmd = input.substr(0, input.find_first_of(' '));
    args = input.substr(input.find_first_of(' ') + 1);

    if(cmd == "exit") {
      exit(stoi(args));
    }
    else if(cmd == "echo") {
      std::cout << args << std::endl;
    }
    else if(cmd == "type") {
      if(cmds.find(args) != cmds.end()) {
        std::cout << args << " is a shell builtin" << std::endl;
      }
      else if(cmd_path = cmd_in_path(args); !cmd_path.empty()) {
        std::cout << args << " is " << cmd_path << std::endl;
      }
      else {
        std::cout << args << ": not found"<< std::endl;
      }
    }
    else if(cmd_path = cmd_in_path(cmd); !cmd_path.empty()) {
        int res = system(input.c_str());
    }
    else {
      std::cout << input << ": command not found" << std::endl;
    }
  }
}

std::string cmd_in_path(const std::string& cmd) {
  std::string path = getenv("PATH");
  std::string search_dir;
  int left_occ = 0;

  for(int i = 0; i < path.size(); i++) {
    if(path[i] == ':') {
      search_dir = path.substr(left_occ, i - left_occ);
      if(std::filesystem::exists(search_dir + '/' + cmd)) {
        return search_dir + '/' + cmd;
      }
      left_occ = i + 1;
    }
  }

  search_dir = path.substr(path.find_last_of(':'));
  if(std::filesystem::exists(search_dir + '/' + cmd)) {
        return search_dir + '/' + cmd;
  }

  return "";
}