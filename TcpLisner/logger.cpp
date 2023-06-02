#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

#ifdef _WIN32
#include <direct.h> // For Windows
#else
#include <sys/stat.h> // For Linux/Unix
#endif

bool CreateDirectory(const std::string& logDir)
{
#ifdef _WIN32
    int result = _mkdir(logDir.c_str()); // For Windows
#else
    int result = mkdir(directory.c_str(), 0777); // For Linux/Unix
#endif

    if (result != 0)
    {
        // Failed to create directory, print the error message
#ifdef _WIN32
        char errorMessage[256];
        strerror_s(errorMessage, sizeof(errorMessage), errno);
        std::cerr << "Failed to create log directory: " << logDir << ". Error: " << errorMessage << std::endl;
#else
        std::cerr << "Failed to create log directory: " << logDir << ". Error: " << strerror(errno) << std::endl;
#endif

        return false;
    }

    return true;
}

// Function to get the current date and time as a string
std::string GetCurrentDateTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
    struct tm localTime;
    localtime_s(&localTime, &nowTime);
    std::stringstream ss;
    ss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

// Function to create a log entry in a log file
void Log(const std::string& message)
{
    // Get the current date and time
    std::string currentDateTime = GetCurrentDateTime();

    // Create a string stream to format the log entry
    std::stringstream ss;
    ss << currentDateTime << " - " << message << std::endl;
    std::string logEntry = ss.str();

    // Create the log directory if it doesn't exist
    std::string logDir = "C:\Tcp_client_logs";

    if (!CreateDirectory(logDir)) {
        std::cerr << "Failed to create log directory: " << logDir << std::endl;

        return;
    }

    // Get the current date as a string
    std::string currentDate = currentDateTime.substr(0, 10);

    // Get the log file path
    std::string logFilePath = logDir + "/" + currentDate + ".log";

    // Check if the log file exceeds the maximum size
    std::ifstream logFile(logFilePath, std::ios::ate | std::ios::binary);
    std::streampos fileSize = logFile.tellg();
    logFile.close();

    // Create a new log file if the current log file exceeds the maximum size
    const std::streampos maxFileSize = 20 * 1024 * 1024; // 20MB
    if (fileSize >= maxFileSize) {
        std::stringstream newFilePathSS;
        newFilePathSS << logDir << "/" << currentDate << "_" << currentDateTime << ".log";
        std::string newFilePath = newFilePathSS.str();
        std::rename(logFilePath.c_str(), newFilePath.c_str());
    }

    // Open the log file in append mode and write the log entry
    std::ofstream logfile(logFilePath, std::ios::app);
    if (logfile.is_open()) {
        logfile << logEntry;
        logfile.close();
    }
}
