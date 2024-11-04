#ifndef NewTerminal_H
#define NewTerminal_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <sstream>

void openNewTerminal();

void sendMessageToTerminal(const std::string& message);

void writeMessageToFile(const std::string& message);

#endif  // NewTerminal_H