#include <iostream>
#include <vector>

#include "builtin.h"
#include "system.h"

std::vector<std::string> parse_tokens(const std::string &input) {
    std::vector<std::string> tokens;
    std::string token;
    bool in_double_quote = false;
    bool in_quote = false;

    // ignore just \n
    if (input.empty()) {
        return tokens;
    }

    for (char c : input) {
        if (c == ' ' && !in_double_quote && !in_quote) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else if (c == '"' && !in_quote) {
            in_double_quote = !in_double_quote;
        } else if (c == '\'' && !in_double_quote) {
            in_quote = !in_quote;
        } else if (c != '\n' && c != '\r') {
            token += c;
        }
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }

    return std::move(tokens);
}

std::vector<std::string> prompt() {
    std::string input;

    std::cout << "$ ";
    std::getline(std::cin, input);

    return parse_tokens(input);
}

int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    for (;;) {
        std::vector<std::string> tokens = prompt();
        std::string command = tokens[0];

        if (tokens.size() > 0) {
            auto executable = find_executable(command);

            if (builtin_commands.find(command) != builtin_commands.end()) {
                builtin_commands[command](tokens);
            } else if (executable.has_value()) {
                execute(executable.value(), tokens);
            } else {
                std::cout << command << ": command not found" << std::endl;
            }
        }
    }
}