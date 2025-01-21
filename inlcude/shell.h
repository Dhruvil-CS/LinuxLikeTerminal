#ifndef SHELL_H
#define SHELL_H

#include <string>
#include <vector>

class Shell {
public:
    void run();
private:
    std::string readCommand();
    void parseAndExecute(const std::string& command);
    // void executeCommand(const std::vector<std::string>& args);
    void handleBuiltinCommands(const std::vector<std::string>& args);
    bool isBuiltinCommand(const std::string& command);
};

#endif // SHELL_H
