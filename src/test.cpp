#include <vector>
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <iostream>

using namespace std;

enum CommandType
{
    Builtin,
    Executable,
    Nonexistent,
};
// assigns a string to an interger mapping

struct FullCommandType
{
    CommandType type;
    string executable_path;
};

vector<string> parse_command_to_string_vector(string command);
FullCommandType command_to_full_command_type(string command);
string find_command_executable_path(string command);
string find_command_in_path(string command, string path);

int main()
{
    // Flush after every cout / std:cerr
    cout << unitbuf;
    cerr << unitbuf;

    while (true)
    {
        cout << "$ ";

        string input;
        getline(cin, input);

        vector<string> command_vector = parse_command_to_string_vector(input);

        if (command_vector.size() == 0)
        {
            continue;
        }

        FullCommandType fct = command_to_full_command_type(command_vector[0]);

        // handle builtin commands
        if (fct.type == Builtin)
        {
            if (command_vector[0] == "exit")
            {
                int exit_code = stoi(command_vector[1]);
                return exit_code;
            }

            if (command_vector[0] == "echo")
            {
                for (int i = 1; i < command_vector.size(); i++)
                {
                    // print a space before every item that is not the first
                    if (i != 1)
                    {
                        cout << " ";
                    }

                    cout << command_vector[i];
                }

                cout << "\n";
                continue;
            }

            if (command_vector[0] == "type")
            {
                if (command_vector.size() < 2)
                {
                    continue;
                }

                string command_name = command_vector[1];
                FullCommandType command_type = command_to_full_command_type(command_name);

                switch (command_type.type)
                {
                case Builtin:
                    cout << command_name << " is a shell builtin\n";
                    break;
                case Executable:
                    cout << command_name << " is " << command_type.executable_path << "\n";
                    break;
                case Nonexistent:
                    cout << command_name << ": not found\n";
                    break;
                default:
                    break;
                }

                continue;
            }

            continue;
        }

        if (fct.type == Executable)
        {
            string command_with_full_path = fct.executable_path;

            for (int argn = 1; argn < command_vector.size(); argn++)
            {
                command_with_full_path += " ";
                command_with_full_path += command_vector[argn];
            }

            const char *command_ptr = command_with_full_path.c_str();

            system(command_ptr);
            continue;
        }

        cout << input << ": command not found\n";
    }
}

vector<string> parse_command_to_string_vector(string command)
{
    vector<string> args;
    string arg_acc = "";

    for (char c : command)
    {
        if (c == ' ')
        {
            args.push_back(arg_acc);
            arg_acc = "";
        }
        else
        {
            arg_acc += c;
        }
    }

    if (arg_acc != "")
    {
        args.push_back(arg_acc);
    }

    return args;
}

// returns the full command type of a command (without arguments)
FullCommandType command_to_full_command_type(string command)
{
    vector<string> builtin_commands = {"exit", "echo", "type"};

    // handle builtin commands
    if (find(builtin_commands.begin(), builtin_commands.end(), command) != builtin_commands.end())
    {
        FullCommandType fct;
        fct.type = CommandType::Builtin;

        return fct;
    }

    // check if the command is found in path
    string exec_path = find_command_executable_path(command);
    if (exec_path != "")
    {
        FullCommandType fct;
        fct.type = Executable;
        fct.executable_path = exec_path;
        return fct;
    }

    // nonexistent types
    FullCommandType fct;
    fct.type = CommandType::Nonexistent;
    return fct;
}

string find_command_executable_path(string command)
{
    char *path = getenv("PATH");

    if (path == NULL)
    {
        return "";
    }

    string path_acc = "";

    // accumulate values in path_acc
    // and search whenever the directory is complete
    char *p = path;
    while (*p != '\0')
    {
        // search for end of paths
        if (*p == ':')
        {
            string exec_path = find_command_in_path(command, path_acc);

            if (exec_path != "")
            {
                return exec_path;
            }

            path_acc = "";
        }
        else
        {
            path_acc += *p;
        }
        p++;
    }

    // handle the last path in the string
    string exec_path = find_command_in_path(command, path_acc);

    if (exec_path != "")
    {
        return exec_path;
    }

    return "";
}

// checks for a command in the directory path
string find_command_in_path(string command, string path)
{
    for (const auto &entry : filesystem::directory_iterator(path))
    {
        if (entry.path() == (path + "/" + command))
        {
            return entry.path();
        }
    }
    return "";
  }