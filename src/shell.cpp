#include "shell.h"
#include "builtins.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <unordered_set>
#include <unordered_map>
#include <fstream>

const std::string ALIAS_FILE = "aliases.txt";


const std::unordered_set<std::string> supportedCommands = {
    "cd",
    "exit",
    "help",
    "alias",
    "unalias",
    "ls"
};

// Aliases for supported commands
std::unordered_map<std::string, std::string> commandAliases = {
    {"quit", "exit"}  // Example predefined alias
};

// void Shell::loadAliases() {
//     std::ifstream infile(ALIAS_FILE);
//     if (!infile) return; // If the file doesn't exist, skip loading

//     std::string line;
//     while (std::getline(infile, line)) {
//         size_t equalsPos = line.find('=');
//         if (equalsPos == std::string::npos || equalsPos == 0 || equalsPos == line.length() - 1) {
//             continue; // Skip invalid lines
//         }

//         std::string aliasName = line.substr(0, equalsPos);
//         std::string aliasCommand = line.substr(equalsPos + 1);
//         commandAliases[aliasName] = aliasCommand;
//     }

//     infile.close();
// }
// void Shell::saveAliases() {
//     std::ofstream outfile(ALIAS_FILE);
//     if (!outfile) {
//         std::cerr << "Error: Unable to save aliases to file.\n";
//         return;
//     }

//     for (const auto& alias : commandAliases) {
//         outfile << alias.first << "=" << alias.second << "\n";
//     }

//     outfile.close();
// }
void Shell::loadAliases() {
    std::ifstream infile(aliasFile);
    if (!infile) return; // If the file doesn't exist, skip loading

    std::string line;
    while (std::getline(infile, line)) {
        size_t equalsPos = line.find('=');
        if (equalsPos == std::string::npos || equalsPos == 0 || equalsPos == line.length() - 1) {
            continue; // Skip invalid lines
        }

        std::string aliasName = line.substr(0, equalsPos);
        std::string aliasCommand = line.substr(equalsPos + 1);
        commandAliases[aliasName] = aliasCommand;
    }

    infile.close();
}

void Shell::saveAliases() {
    std::ofstream outfile(aliasFile);
    if (!outfile) {
        std::cerr << "Error: Unable to save aliases to file.\n";
        return;
    }

    for (const auto& alias : commandAliases) {
        outfile << alias.first << "=" << alias.second << "\n";
    }

    outfile.close();
}

void Shell::run() {
    loadAliases();
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
    std::vector<std::string> args = splitInput(command);

    if (args.empty()) return;

    // Resolve alias if applicable
    if (commandAliases.find(args[0]) != commandAliases.end()) {
        args[0] = commandAliases.at(args[0]);
    }

    if (isBuiltinCommand(args[0])) {
        handleBuiltinCommands(args);
    } else {
        std::cerr << "Error: Command not supported: " << args[0] << std::endl;
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

bool Shell::isBuiltinCommand(const std::string& command) {
    return supportedCommands.find(command) != supportedCommands.end();
}

void Shell::handleAliasCommand(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "Usage: alias <name>=<command>\n";
        return;
    }

    std::string aliasDefinition = args[1];
    size_t equalsPos = aliasDefinition.find('=');
    if (equalsPos == std::string::npos || equalsPos == 0 || equalsPos == aliasDefinition.length() - 1) {
        std::cerr << "Invalid alias format. Use: alias <name>=<command>\n";
        return;
    }

    std::string aliasName = aliasDefinition.substr(0, equalsPos);
    std::string aliasCommand = aliasDefinition.substr(equalsPos + 1);

    // Add alias
    commandAliases[aliasName] = aliasCommand;
    std::cout << "Alias added: " << aliasName << " -> " << aliasCommand << std::endl;
}

void Shell::handleUnaliasCommand(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "Usage: unalias <name>\n";
        return;
    }

    std::string aliasName = args[1];

    if (commandAliases.erase(aliasName)) {
        std::cout << "Alias removed: " << aliasName << std::endl;
    } else {
        std::cerr << "Alias not found: " << aliasName << std::endl;
    }
}

void Shell::handleBuiltinCommands(const std::vector<std::string>& args) {
    if (args[0] == "cd") {
        Builtins::changeDirectory(args);
    } else if (args[0] == "exit") {
        saveAliases();
        exit(0);
    } else if (args[0] == "pwd") {
        Builtins::printWorkingDirectory();
    } else if (args[0] == "help") {
        std::cout << "Supported commands:\n";
        std::cout << "- cd <directory>: Change directory\n";
        std::cout << "- exit: Exit the shell\n";
        std::cout << "- help: Display this help message\n";
        std::cout << "- alias <name>=<command>: Define a custom alias\n";
        std::cout << "- unalias <name>: Remove a custom alias\n";
    } else if (args[0] == "alias") {
        handleAliasCommand(args);
    } else if (args[0] == "unalias") {
        handleUnaliasCommand(args);
    } else if(args[0] == "ls"){
        Builtins::listDirectory(args);
    } else {
        std::cerr << "Error: Command not implemented: " << args[0] << std::endl;
    }
}