// auth.h 
#ifndef AUTH_H 
#define AUTH_H 
 
#include <string> 
 
class Auth { 
public: 
    static std::string generateRandomSalt(); 
    static std::string hashPassword(const std::string& password, const std::string& salt); 
    static bool authenticate(const std::string& username, const std::string& password, const std::string& databaseFile); 
}; 
 
#endif // AUTH_H