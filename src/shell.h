#ifndef SHELL_H
#define SHELL_H

#include <string>
#include <vector>

class Shell {
private:
    std::string aliasFile;
public:
    Shell(const std::string& aliasFileName = "aliases.txt") : aliasFile(aliasFileName) {}
    void run();
    std::string readCommand();
    void parseAndExecute(const std::string& command);
    // void executeCommand(const std::vector<std::string>& args);
    void handleBuiltinCommands(const std::vector<std::string>& args);
    bool isBuiltinCommand(const std::string& command);
    std::vector<std::string> splitInput(const std::string& input);
    void handleAliasCommand(const std::vector<std::string>& args);   // Declare this function here
    void handleUnaliasCommand(const std::vector<std::string>& args);
    void loadAliases();
    void saveAliases();
};

#endif // SHELL_H
