// tests_main.cpp
#include <UnitTest++/UnitTest++.h>
#include "server.h"
#include "errors.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string words, text_of_error;

string check(int argc, char *argv[])
{
    try {
        //Установка значений по умолчанию для параметров
        std::string databaseFile = "usersdata.txt";
        std::string logFile = "log.txt";
        int port = 33333;

        if (argc < 2 || (argc == 2 && std::string(argv[1]) == "-h")) { //Если запуск без аргументов или с аргументом -h,
        //то выводится справка
            words="Использование: "+string(argv[0])+" [--port <порт>] [--database <файл_базы_данных>] [--log <файл_журнала>]"
            +"\n"+"Параметры:"+"\n"+"  --port <порт>: Порт сервера (по умолчанию: 33333)"+"\n"
            +"  --database <файл_базы_данных>: Путь к файлу базы данных (по умолчанию: usersdata.txt)"+"\n"+"  --log <файл_журнала>: Путь к файлу журнала работы (по умолчанию: log.txt)"
            +"\n"; //Обычный вывод стал срокой
            cout<<words; //Выыод справки
            /*std::cout << "Использование: " << argv[0] << " [--port <порт>] [--database <файл_базы_данных>] [--log <файл_журнала>]" << std::endl;
            std::cout << "Параметры:" << std::endl;
            std::cout << "  --port <порт>: Порт сервера (по умолчанию: 33333)" << std::endl;
            std::cout << "  --database <файл_базы_данных>: Путь к файлу базы данных (по умолчанию: usersdata.txt)" << std::endl;
            std::cout << "  --log <файл_журнала>: Путь к файлу журнала работы (по умолчанию: log.txt)" << std::endl;*/
            return words; //Передача справки (для теста)
        }
        for (int i = 1; i < argc; i += 2) {
            if (i + 1 < argc) {
                std::string option = argv[i]; //Параметр
                std::string value = argv[i + 1]; //Значение параметра

                if (option == "--port") {
                    port = std::stoi(value); //Установка порта
                } else if (option == "--database") {
                    if (!std::fstream(value)) { //Проверка сущестования файла базы данных
                        text_of_error="Не удалось открыть файл базы данных.\n";
                        return text_of_error;
                    }
                    databaseFile=value; //Установка файла базы данных
                } else if (option == "--log") {
                    logFile = value; //Установка файла журнала
                } else {
                    //option=argv[i]="--unknown";
                    text_of_error="Неизвестный параметр: "+string(option)+"\n";
                    //cout<<text_of_error<<endl;
                    return text_of_error;
                }
            } else {
                text_of_error="Отсутствует значение для параметра: "+string(argv[i])+"\n";
                return text_of_error; // Завершение программы с ошибкой
            }
        }

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return "";
    }
}

int runTests()
{
    return UnitTest::RunAllTests();
}

SUITE(CommandLineTests)
{
    TEST(NoArguments) { //Нет аргументов
        cout<<"Тест с отсутствием аргументов:"<<endl;
        const char *argv[] = {"program_name"};
        CHECK_EQUAL(words, check(1, const_cast<char**>(argv))); //Если выодится инструкция (т.е. words), то нет аргументов
    }

    TEST(HelpOption) { //Аргумент -h
        cout<<endl<<"Тест с аргументом -h:"<<endl;
        const char *argv[] = {"program_name", "-h"};
        CHECK_EQUAL(words, check(2, const_cast<char**>(argv)));
    }

    TEST(UnknownOption) { //Неизвестный аргумент
        cout<<endl<<"Тест с неизвестным аргументом:"<<endl;
        const char *argv[] = {"program_name", "--unknown"};
        cout<<"Неизвестный параметр: --unknown"<<endl;
        CHECK_EQUAL(text_of_error, check(2, const_cast<char**>(argv)));
    }

    TEST(NonexistentDatabaseFile) { //Файл базы данных не существует
        cout<<endl<<"Тест с передачей несуществующей базы данных:"<<endl;
        const char *argv[] = {"program_name", "--database", "database.txt"};
        cout<<"Не удалось открыть файл базы данных."<<endl;
        CHECK_EQUAL(text_of_error, check(3, const_cast<char **>(argv)));
    }
    
    TEST(ClearOption) { //Передача пустого параметра
        cout<<endl<<"Тест с передачей пустого параметра:"<<endl;
        const char *argv[] = {"program_name", "--database"};
        cout<<"Отсутствует значение для параметра: --database"<<endl<<endl;
        CHECK_EQUAL(text_of_error, check(2, const_cast<char **>(argv)));
    }
}

int main(int argc, char **argv)
{
    runTests();
    return 0;
}