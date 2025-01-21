#ifndef BUILTINS_H
#define BUILTINS_H

#include <vector>
#include <string>

class Builtins {
public:
    static void changeDirectory(const std::vector<std::string>& args);
    static void printWorkingDirectory();
    static void listDirectory(const std::vector<std::string>& args);
};

#endif // BUILTINS_H
