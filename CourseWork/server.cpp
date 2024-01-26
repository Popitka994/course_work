/**
 * @file server.cpp
 * @brief Реализация класса Server
 */
#include "server.h" 
#include "auth.h" 
#include "errors.h" 
#include <iostream> 
#include <iomanip> 
#include <fstream> 
#include <sstream> 
#include <openssl/md5.h> 
#include <algorithm>
using namespace std;

/**
 * @brief Конструктор класса Server
 * @param errorTracker Указатель на объект ErrorTracker для отслеживания ошибок
 */
Server::Server(ErrorTracker* errorTracker) : errorTracker(errorTracker) { 
    // Инициализация объекта Server с переданным ErrorTracker 
} 

/**
 * @brief Запуск сервера
 * @param port Порт сервера
 * @param databaseFile Путь к файлу базы данных
 * @param logFile Путь к файлу журнала
 */
void Server::run(int port, const std::string& databaseFile, const std::string& logFile) { 
    // Здесь реализуется код для запуска сервера, включая инициализацию и обработку параметров 
    setlocale(LC_ALL, "Russian"); // Установка русской локали

    errorTracker->writeToLog("Сервер запущен.", false); 
 
    std::string clientUsername; 
    std::string clientPassword; 
 
    std::cout << "Введите Ваше имя пользователя: "; 
    std::cin >> clientUsername; 
 
    std::cout << "Введите Ваш пароль: "; 
    std::cin >> clientPassword; 
 
    if (authenticateClient(clientUsername, clientPassword, databaseFile)) { 
        std::cout << "OK" << std::endl; 
        errorTracker->writeToLog("Успешная аутентификация.", false); 
        std::cout << "Аутентификация успешна. Передаем HASH." << std::endl; 
 
        // Генерация и передача HASH клиенту 
        std::string salt = generateRandomSalt(); 
        std::string hashedPassword = hashPassword(clientPassword, salt); 
 
        // Передача salt и хэшированного пароля клиенту 
        std::cout << "SALT: " << salt << std::endl;
        std::cout << "HASH: " << hashedPassword << std::endl; 

        int numVectors; 
        std::cout << "Введите количество векторов: "; 
        std::cin >> numVectors; 
 
        for (int i = 0; i < numVectors; ++i) { 
            int vectorSize; 
            std::cout << "Введите длину " << i + 1 << " вектора: "; 
            std::cin >> vectorSize; 
 
            std::vector<int64_t> vectorData(vectorSize); 
            std::cout << "Введите элементы вектора через пробел: "; 
            for (int j = 0; j < vectorSize; ++j) { 
                uint64_t value; 
                std::cin >> value; 
                vectorData[j] = value; 
            } 

            uint64_t average = processVector(vectorData); 
            std::cout.write(reinterpret_cast<char*>(&average), sizeof(uint64_t)); 
        } 
 
        // Завершение соединения 
        std::cout << "Connection completed." << std::endl; 
    } else { 
        std::cout << "ERR" << std::endl; 
        std::cout << "Ошибка аутентификации. Закрываем соединение." << std::endl; 
        errorTracker->writeToLog("Ошибка аутентификации. Закрываем соединение.", true); 
    } 
} 

/**
 * @brief Аутентификация клиента
 * @param username Имя пользователя
 * @param password Пароль
 * @param databaseFile Путь к файлу базы данных
 * @return true, если аутентификация успешна, иначе false
 */
bool Server::authenticateClient(const std::string& username, const std::string& password, const std::string& databaseFile) { 
    // Открываем файл базы данных для чтения 
    std::ifstream database(databaseFile); 
    if (!database.is_open()) { 
        std::cerr << "Не удалось открыть файл базы данных." << std::endl; 
        return false; 
    } 
 
    std::string line; 
    while (std::getline(database, line)) { 
        std::istringstream iss(line); 
        std::string storedUsername, storedPassword; 
 
        // Считываем имя и пароль из строки 
        if (iss >> storedUsername >> storedPassword) { 
            // Проверяем совпадение имени пользователя и пароля 
            if (storedUsername == username && storedPassword == password) { 
                // Если совпадение найдено, возвращаем true для успешной аутентификации 
                return true; 
            } 
        } 
    } 
 
    // Если не найдено совпадение в базе данных, возвращаем false 
    return false; 
} 

/**
 * @brief Генерация случайной соли
 * @return Сгенерированная соль
 */
std::string Server::generateRandomSalt() { 
    srand(static_cast<unsigned>(time(0)));  // Инициализация rand() текущим временем
    std::string salt; 
    for (int i = 0; i < 16; ++i) { 
        salt += rand() % 16 < 10 ? (rand() % 10) + '0' : (rand() % 6) + 'A'; 
    } 
    return salt; 
} 

/**
 * @brief Хэширование
 * @param password Пароль
 * @param salt Соль
 * @return Строка хэша
 */
std::string Server::hashPassword(const std::string& password, const std::string& salt) { 
    //Хэширование пароля с использованием salt и MD5 
    std::string input = salt + password; 
    unsigned char hash[MD5_DIGEST_LENGTH]; 
    MD5(reinterpret_cast<const unsigned char*>(input.c_str()), input.length(), hash); 
 
    // Преобразование хэша в строку в шестнадцатеричной форме 
    std::stringstream ss; 
    ss << std::hex << std::setfill('0'); 
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) { 
        ss << std::setw(2) << static_cast<unsigned>(hash[i]); 
    } 
 
    return ss.str(); 
} 

/**
 * @brief Вычисление по вектору
 * @param vector Вектор
 * @param salt Соль
 * @return 0, если вектор пуст или average - среднее врифметическое, 
 */
double Server::processVector(const std::vector<int64_t>& vector) { 
    int64_t sum = 0; 
    int64_t count = vector.size(); // Используем размер вектора как общий счетчик 
 
    for (int64_t value : vector) { 
        sum += value; 
    } 
 
    if (count > 0) { 
        double average = static_cast<double>(sum) / count; 
        std::cout << "Average: " << average << std::endl; 
        //return average; 
    } else { 
        std::cout << "Вектор пуст, возвращаем 0." << std::endl; 
        return 0; 
    } 
}