#include "shell.h"
#include <csignal>
#include <iostream>
Shell* shellInstance = nullptr; // Global pointer to the Shell instance

void handleSigint(int signal) {
    if (shellInstance) {
        std::cout << "\nSaving aliases before exit...\n";
        shellInstance->saveAliases();
    }
    exit(signal); // Exit gracefully
}

int main() {
    Shell shell;
    shellInstance = &shell; // Assign the global pointer to the Shell instance

    std::signal(SIGINT, handleSigint); // Set up signal handler for SIGINT

    shell.run();
    return 0;
}
