/**
 * @file errors.cpp
 * @brief Реализация класса ErrorTracker
 */
#include "errors.h" 
#include <iostream> 
#include <ctime> 

/**
 * @brief Конструктор класса ErrorTracker
 * @param logFileName Имя файла журнала
 */
ErrorTracker::ErrorTracker(const std::string& logFileName) { 
    logFile.open(logFileName, std::ios::app); 
    if (!logFile.is_open()) { 
        std::cerr << "Failed to open log file: " << logFileName << std::endl; 
    } 
} 
 
ErrorTracker::~ErrorTracker() { 
    logFile.close(); 
} 

/**
 * @brief Запись ошибок
 * @param message Сообщение
 * @param isError Значение ошибки
 */
void ErrorTracker::writeToLog(const std::string& message, bool isError) { 
    if (logFile.is_open()) { 
        std::time_t currentTime = std::time(nullptr); 
        std::tm* localTime = std::localtime(&currentTime); 
        char timeBuffer[80]; 
        std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", localTime); 
 
        std::string severity = (isError) ? "ERROR" : "INFO"; 
 
        logFile << "[" << timeBuffer << "] " << severity << ": " << message << std::endl; 
        logFile.flush(); 
    } 
}