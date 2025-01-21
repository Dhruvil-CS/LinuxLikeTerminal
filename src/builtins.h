#ifndef BUILTINS_H
#define BUILTINS_H

#include <vector>
#include <string>

class Builtins {
public:
    static void changeDirectory(const std::vector<std::string>& args);
    static void printWorkingDirectory();
    static void listDirectory(const std::vector<std::string>& args);
    static void displayFileContents(const std::string& filename);
    static void createFile(const std::string& filename);
    static void removeFile(const std::string& filename);
};

#endif // BUILTINS_H
