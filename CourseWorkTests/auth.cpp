//auth.cpp 
#include "auth.h" 
#include <iostream> 
#include <iomanip> 
#include <fstream> 
#include <sstream> 
#include <openssl/md5.h> 
 
std::string Auth::generateRandomSalt() { 
    std::string salt; 
    for (int i = 0; i < 16; ++i) { 
        salt += rand() % 16 < 10 ? (rand() % 10) + '0' : (rand() % 6) + 'A'; 
    } 
    return salt; 
} 
 
std::string Auth::hashPassword(const std::string& password, const std::string& salt) { 
    std::string input = salt + password; 
    unsigned char hash[MD5_DIGEST_LENGTH]; 
    MD5(reinterpret_cast<const unsigned char*>(input.c_str()), input.length(), hash); 
 
    std::stringstream ss; 
    ss << std::hex << std::setfill('0'); 
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) { 
        ss << std::setw(2) << static_cast<unsigned>(hash[i]); 
    } 
 
    return ss.str(); 
} 
 
bool Auth::authenticate(const std::string& username, const std::string& password, const std::string& databaseFile) { 
    std::ifstream database(databaseFile); 
    if (!database.is_open()) { 
        std::cerr << "Не удалось открыть файл базы данных." << std::endl; 
        return false; 
    } 
 
    std::string line; 
    while (std::getline(database, line)) { 
        std::istringstream iss(line); 
        std::string storedUsername, storedPassword; 
 
        if (iss >> storedUsername >> storedPassword) { 
            if (storedUsername == username) { 
                std::string storedSalt; 
                iss >> storedSalt; 
 
                std::string hashedPassword = hashPassword(password, storedSalt); 
 
                if (storedPassword == hashedPassword) { 
                    return true; // Аутентификация успешна 
                } 
            } 
        } 
    } 
 
    return false; // Аутентификация неуспешна 
}