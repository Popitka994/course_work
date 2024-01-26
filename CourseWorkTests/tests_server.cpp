//tests_server.cpp 
#include "server.h" 
#include "auth.h" 
#include "errors.h" 
#include <iostream> 
#include <iomanip> 
#include <fstream> 
#include <sstream> 
#include <openssl/md5.h> 
#include <algorithm>
#include <UnitTest++/UnitTest++.h>
using namespace std;

SUITE(ServerTests) {
    TEST(ValidAuth) { //Верный ID
        cout<<"Тест с верной аутентификацией:"<<endl;
        Server server(nullptr);
        cout<<"Имя и пароль совпадает с базой данных."<<endl;
        CHECK_EQUAL(true, server.authenticateClient("Nikitina", "Margosha994", "usersdata.txt"));
    }
    
    TEST(InvalidAuth) { //Неверный ID
        cout<<endl<<"Тест с неверной аутентификацией:"<<endl;
        Server server(nullptr);
        cout<<"Имя и/или пароль не совпадает с базой данных."<<endl;
        CHECK_EQUAL(false, server.authenticateClient("invalid_user", "invalid_password", "usersdata.txt"));
    }
    
    TEST(NormalVector) { 
        cout<<endl<<"Передача нормального вектора:"<<endl;
        cout<<"Элементы: 10 20 30 40 50"<<endl;
        Server server(nullptr);
        std::vector<int64_t> normalVector = {10, 20, 30, 40, 50};
        double result = server.processVector(normalVector);
        CHECK_EQUAL(30.0, result); 
    }
    
    TEST(NoIntResult) { 
        cout<<endl<<"Нецелый результат вычислений:"<<endl;
        cout<<"Элементы: 6 7"<<endl;
        Server server(nullptr);
        std::vector<int64_t> NoIntVector = {6, 7};
        double result = server.processVector(NoIntVector);
        CHECK_EQUAL(6.5, result); 
    }
    
    TEST(Negative) { 
        cout<<endl<<"Отрицательные элементы вектора:"<<endl;
        cout<<"Элементы: -10 -20 -30 -40 -50"<<endl;
        Server server(nullptr);
        std::vector<int64_t> NegativeVector = {-10, -20, -30, -40, -50};
        double result = server.processVector(NegativeVector);
        CHECK_EQUAL(-30, result); 
    }
    
    TEST(NegativeAndPositive) { 
        cout<<endl<<"Отрицательные и положительные элементы вектора:"<<endl;
        cout<<"Элементы: 10 -20 30 -40"<<endl;
        Server server(nullptr);
        std::vector<int64_t> NegativePositiveVector = {10, -20, 30, -40};
        double result = server.processVector(NegativePositiveVector);
        CHECK_EQUAL(-5, result); 
    }
    
    TEST(MaxPositive) { 
        cout<<endl<<"Максимальные положительные элементы вектора:"<<endl;
        cout<<"Элементы: 32767 32767 32767"<<endl;
        Server server(nullptr);
        std::vector<int64_t> MaxPositiveVector = {32767, 32767, 32767};
        double result = server.processVector(MaxPositiveVector);
        CHECK_EQUAL(32767, result); 
    }
    
    TEST(MaxNegative) { 
        cout<<endl<<"Максимальные отрицательные элементы вектора:"<<endl;
        cout<<"Элементы: -32768 -32768 -32768"<<endl;
        Server server(nullptr);
        std::vector<int64_t> MaxNegativeVector = {-32768, -32768, -32768};
        double result = server.processVector(MaxNegativeVector);
        CHECK_EQUAL(-32768, result); 
    }
    
    TEST(Clear) { 
        cout<<endl<<"Пустой вектор:"<<endl;
        //cout<<"Элементы: -32768 -32768 -32768"<<endl;
        Server server(nullptr);
        std::vector<int64_t> ClearVector = {};
        double result = server.processVector(ClearVector);
        CHECK_EQUAL(0, result); 
    }
}
