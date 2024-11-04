#include "NewTerminal.h"

void openNewTerminal() {
    // Use this command to open a cmd terminal
    const char* command = "cmd.exe /c start cmd.exe /k \"terminal_script.bat\"";

    // Use this command to open a wsl bash terminal
    // First, clean up the script's line endings for compatibility with WSL
    // const char* command = "cmd.exe /c start wsl.exe bash -c \"bash terminal_script.sh; exec bash\"";
    
    system(command);

}

void sendMessageToTerminal(const std::string& message) {
    std::string command = "echo " + message + " > COM1"; // Use COM ports to redirect output
    system(command.c_str());
}

void writeMessageToFile(const std::string& message) {
    // std::ofstream file("temp_messages.txt", std::ios::app); // Open in append mode
    std::ofstream file("temp_messages.txt", std::ios::trunc); // Open in truncation mode
    if (file.is_open()) {
        file << message << std::endl; // Write message to file
        file.close();
    } else {
        std::cerr << "Unable to open file." << std::endl;
    }
}