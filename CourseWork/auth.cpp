/**
 * @file auth.cpp
 * @brief Реализация класса Auth
 */
#include "auth.h" 
#include <iostream> 
#include <iomanip> 
#include <fstream> 
#include <sstream> 
#include <openssl/md5.h> 
#include <random>
#include <ctime>

/**
 * @brief Хэширование пароля с использованием соли
 * @details Этот метод принимает пароль и соль, объединяет их, затем хэширует с использованием алгоритма MD5.
 * @param password Пароль
 * @param salt Соль
 * @return Хэшированный пароль в виде строки
 */
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

/**
 * @brief Аутентификация пользователя
 * @details Этот метод проверяет подлинность пользователя, сравнивая предоставленные имя пользователя и пароль с данными из базы данных.
 * @param username Имя пользователя
 * @param password Пароль
 * @param databaseFile Путь к файлу базы данных
 * @return true, если аутентификация успешна, false в противном случае
 */
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