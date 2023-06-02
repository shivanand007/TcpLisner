#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

// Function to create a directory
bool CreateDirectory(const std::string& directory);

// Function to get the current date and time as a string
std::string GetCurrentDateTime();

// Function to create a log entry in a log file
void Log(const std::string& message);

#endif // LOGGER_H
