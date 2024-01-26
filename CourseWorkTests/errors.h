// errors.h 
#pragma once 
 
#include <string> 
#include <fstream> 
#include <ctime> 
 
class ErrorTracker { 
public: 
    ErrorTracker(const std::string& logFilePath); 
    ~ErrorTracker(); 
 
    void writeToLog(const std::string& message, bool isError); 
 
private: 
    std::ofstream logFile; 
    std::string getCurrentDateTime() const; 
};
