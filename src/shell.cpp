#include "shell.h"
#include "builtins.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>


void Shell::run() {
    while (true) {
        std::cout << "mysh> ";
        std::string command = readCommand();
        if (command.empty()) continue;

        parseAndExecute(command);
    }
}

std::string Shell::readCommand() {
    std::string command;
    std::getline(std::cin, command);
    return command;
}

void Shell::parseAndExecute(const std::string& command) {
    std::istringstream stream(command);
    std::vector<std::string> args;
    std::string arg;

    while (stream >> arg) {
        args.push_back(arg);
    }

    if (args.empty()) return;

    if (isBuiltinCommand(args[0])) {
        handleBuiltinCommands(args);
    } else {
        std::cerr << "Error: Command not supported: " << args[0] << std::endl;
        return;
    }
}
std::vector<std::string> Shell::splitInput(const std::string& input) {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// void Shell::executeCommand(const std::vector<std::string>& args) {
//     pid_t pid = fork();
//     if (pid == 0) {
//         // Child process
//         std::vector<char*> c_args;
//         for (const auto& arg : args) {
//             c_args.push_back(const_cast<char*>(arg.c_str()));
//         }
//         c_args.push_back(nullptr);

//         execvp(c_args[0], c_args.data());
//         perror("execvp failed");
//         exit(EXIT_FAILURE);
//     } else if (pid > 0) {
//         // Parent process
//         int status;
//         waitpid(pid, &status, 0);
//     } else {
//         perror("fork failed");
//     }
// }

bool Shell::isBuiltinCommand(const std::string& command) {
    return command == "cd" || command == "exit" || command == "pwd" || command == "ls";
}

void Shell::handleBuiltinCommands(const std::vector<std::string>& args) {
    if (args[0] == "cd") {
        Builtins::changeDirectory(args);
    } else if (args[0] == "exit") {
        exit(0);
    } else if (args[0] == "pwd") {
        Builtins::printWorkingDirectory();
    } else if (args[0] == "help") {
        std::cout << "Supported commands:\n";
        std::cout << "- cd <directory>: Change directory\n";
        std::cout << "- exit: Exit the shell\n";
        std::cout << "- help: Display this help message\n";
        return;
    } else if (args[0] == "ls") {
        Builtins::listDirectory(args);
    } else {
        std::cerr << "Error: Command not implemented: " << args[0] << std::endl;
        return;
        // Logger::getInstance().log("Unimplemented command: " + args[0], "ERROR");
    }

}
