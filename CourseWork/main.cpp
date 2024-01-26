/** @file
* @author Никитина М. А. 22ПИ2
* @version 1.0
* @date 25.01.2024
* @copyright ИБСТ ПГУ
* @brief Главный файл программы
*/
#include "server.h"
#include "errors.h" 
#include <iostream> 
#include <string>
using namespace std;

/**
 * @brief Точка входа в программу
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @return Код завершения программы
 */
int main(int argc, char *argv[]) { 
    //Установка значений по умолчанию для параметров 
    std::string databaseFile = "usersdata.txt"; 
    std::string logFile = "log.txt"; 
    int port = 33333; // Порт по умолчанию 
 
    // Проверка наличия параметров командной строки 
    if (argc < 2 || (argc == 2 && std::string(argv[1]) == "-h")) { 
        // Вывод справки и завершение программы 
        std::cout << "Использование: " << argv[0] << " [--port <порт>] [--database <файл_базы_данных>] [--log <файл_журнала>]" << std::endl; 
        std::cout << "Параметры:" << std::endl; 
        std::cout << "  --port <порт>: Порт сервера (по умолчанию: 33333)" << std::endl;
        std::cout << "  --database <файл_базы_данных>: Путь к файлу базы данных (по умолчанию: usersdata.txt)" << std::endl; 
        std::cout << "  --log <файл_журнала>: Путь к файлу журнала работы (по умолчанию: log.txt)" << std::endl; 
        return 0; // Завершение программы 
    } 
 
    // Обработка параметров командной строки 
    for (int i = 1; i < argc; i += 2) { 
        if (i + 1 < argc) { 
            std::string option = argv[i]; // Параметр 
            std::string value = argv[i + 1]; // Значение параметра 
 
            if (option == "--port") {    
                port = std::stoi(value); //Установка порта
            } else if (option == "--database") { 
                if (!std::fstream(value)) { //Проверка сущестования файла базы данных
                    cerr<<"Не удалось открыть файл базы данных."<<endl;
                    return 1;
                }
                databaseFile=value; //Установка файла базы данных
            } else if (option == "--log") { 
                logFile = value; // Установка файла журнала 
            } else { 
                std::cerr << "Неизвестный параметр: " << option << std::endl; // Вывод сообщения об ошибке в стандартный поток ошибок 
                return 1; // Завершение программы с ошибкой 
            } 
        } else { 
            std::cerr << "Отсутствует значение для параметра: " << argv[i] << std::endl; // Вывод сообщения об ошибке в стандартный поток ошибок 
            return 1; // Завершение программы с ошибкой 
        } 
    } 
    
    // Создание объекта ErrorTracker с указанием файла логов 
    ErrorTracker errorTracker(logFile); 
 
    // Создание объекта сервера и запуск, передача errorTracker в конструктор 
    Server server(&errorTracker); 
    server.run(port, databaseFile, logFile); 
 
    return 0; 
}