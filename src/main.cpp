// #include <iostream>
// #include <string>
// using namespace std;

// int main()
// {
//     cout << unitbuf;
//     cerr << unitbuf;

//     while (true)
//     {
//         cout << "$ ";

//         string input;
//         if (!getline(cin, input))
//         {
//             break;
//         }
//         if (input == "exit 0")
//         {
//             break;
//         }
//         else if (input.find("echo ") == 0)
//         {
//             cout << input.substr(5) << endl;
//         }
//         else if (input.substr(0, 5) == "type ")
//         {
//             cout << "Showing info about " << input.substr(5) << endl;
//         } else if (input.substr(0,9)== "type echo" || input .substr(0,9) || input.substr(0,9)=="type type") {
//           cout << input.substr(5) + " is a shell builtin" << endl;

//         }
//         else
//         {
//             cout << input << ": command not found" << endl;
//         }
//     }
// }
 
// #include <iostream>
// #include <string>
// #include <cstring>


// int main() {
//   // Flush after every std::cout / std:cerr
//   std::cout << std::unitbuf;
//   std::cerr << std::unitbuf;

//   while (true) {
//     std::string input;

//     std::cout << "$ ";
//     std::getline(std::cin, input);

//     if (input == "exit 0") {
//       break;
//     } else if (input.substr(0, 4) == "echo") {
//         std::cout << input.substr(5) << std::endl;
//     } else if (input.substr(0, 7) == "invalid") {
//         std::cout << input + ": command not found" << std::endl;
//     } else if (input.substr(0, 9) == "type echo" || input.substr(0, 9) == "type exit" || input.substr(0, 9) == "type type") {
//         std::cout << input.substr(5) + " is a shell builtin" << std::endl;
//     } else {
//         std::cout << input.substr(5) + ": not found" << std::endl;
//     }
//   }
//   return 0;
// }