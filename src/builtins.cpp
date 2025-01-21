#include "builtins.h"
#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <filesystem>
#include <fstream>

void Builtins::changeDirectory(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "cd: missing argument" << std::endl;
        return;
    }
    if (chdir(args[1].c_str()) != 0) {
        perror("cd failed");
    }
}

void Builtins::printWorkingDirectory() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cout << cwd << std::endl;
    } else {
        perror("pwd failed");
    }
}
void Builtins::listDirectory(const std::vector<std::string>& args) {
        std::string directory = ".";
        if (args.size() > 1) {
            directory = args[1];
        }

        try {
            for (const auto& entry : std::filesystem::directory_iterator(directory)) {
                std::cout << entry.path().filename().string();
                if (entry.is_directory()) {
                    std::cout << "/";
                }
                std::cout << " ";
            }
            std::cout << std::endl;
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
void Builtins::displayFileContents(const std::string& filename){
    std::ifstream file(filename);
    if(!file){
        std::cerr << "Error: Could not open file" << filename << std::endl;
        return;
    }
    std::string line;
    while(std::getline(file,line)){
        std::cout << line << std::endl;
    }
}
void Builtins::createFile(const std::string& filename){
    std::ofstream file(filename,std::ios::app);
    if(!file){
        std::cerr << "Could not create file" << filename << std::endl;
    }
}
void Builtins::removeFile(const std::string& filename){
    if(unlink(filename.c_str()) != 0){
        std::cerr << "Could not delete file" << filename << std::endl;
    } else {
        std::cout << "File " << filename << " deleted successfully!" << std::endl;
    }
}