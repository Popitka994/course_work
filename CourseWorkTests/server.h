// server.h 
#pragma once 
#include "errors.h" 
#include <string> 
#include <vector> 
#include <algorithm> 
 
class Server { 
public: 
    Server(ErrorTracker* errorTracker); 
    void run(int port, const std::string& databaseFile, const std::string& logFile); 
    bool authenticateClient(const std::string& username, const std::string& password, const std::string& databaseFile); //Перенос в паблик для тестирования
    double processVector(const std::vector<int64_t>& vector);
 
private: 
    int port; 
    //bool authenticateClient(const std::string& username, const std::string& password, const std::string& databaseFile); 
    std::string generateRandomSalt(); 
    std::string hashPassword(const std::string& password, const std::string& salt); 
    //double processVector(const std::vector<int64_t>& vector);
 
    ErrorTracker* errorTracker; 
};