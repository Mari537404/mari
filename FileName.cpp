#include<iostream>
#include<string>
#include<list>
#include<vector>

using namespace std;

struct User
{
    int id;
    string name;

    User(int id, const string& name) : id(id), name(name) {}//создали конструктор
};
class HashTable {
private:
    vector<list<User>> table; //Вектор списков для хранения данных
    size_t size; // Размер хэш-таблицы
    int count; // Количество элементов в хэш-таблице

         // Хэш-функция (полиномиальное хэширование)
    int hashFunction(const string& key) {
        int hash = 0;
        int p = 31; // Простое число
        int p_pow = 1;

        for (char c : key) {
            hash += (c - 'a' + 1) * p_pow; // Преобразуем символ в число
            p_pow *= p; // Увеличиваем степень
        }
        return hash % size; // Возвращаем индекс
    }
public:
    HashTable(size_t size = 10) : size(size) {//конструктор
        table.resize(size);
    }


    // Внутренние методы
    int getIndex(string name) {// Получить индекс по ключу
        return hashFunction(name);
    }
    // Рехэширование
    void rehash() {
        size_t oldSize = size;
        size *= 2; // Увеличиваем размер хэш-таблицы в 2 раза
        vector<list<User>> oldTable = table;
        table.clear();//удаление эл-тов из старого вектора
        table.resize(size);
        count = 0; // Сброс счетчика 
        // Переносим элементы в новую таблицу
        for (int i = 0; i < oldSize; ++i) {
            for (const auto& i : oldTable[i]) {
                insert(i); // Вставляем элементы заново
            }
        }
    }

public:
    HashTable(int initialSize) : size(initialSize), count(0) {
        table.resize(size);
    }

    // Метод вставки элемента
    void insert(const User& user) {
        if (count >= size * 0.7) { // Если загрузка больше 70%, рехэшируем
            rehash();
        }
        int index = getIndex(user.name);
        table[index].push_back(user); // Добавляем эл-т в соответствующий список
        count++; // Увеличиваем счетчик эл-тов в списке
    }

    // Метод поиска элемента
    bool find(string name, int& id) {
        int index = getIndex(name);
        for (const auto& user : table[index]) {
            if (user.name == name) {
                id = user.id; // Находим id пользователя
                return true; // id найден
            }
        }
        return false; // id не найден
    }

    // Метод удаления элемента
    bool remove(string name) {
        int index = getIndex(name);
        auto& userList = table[index];
        for (auto iter = userList.begin(); iter != userList.end(); ++iter) {
            if (iter->name == name) {
                userList.erase(iter); // Удаляем пользователя
                count--; // Уменьшаем счетчик
                return true; // Успешно удалено
            }
        }
        return false; // пользователь не найден для удаления
    }

    // Метод вывода хэш-таблицы
    void print() {
        for (int i = 0; i < size; ++i) {
            cout << "Index " << i << ": ";
            for (const auto& user : table[i]) {
                cout << "{" << user.name << ", " << user.id << "} ";
            }
            cout << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    HashTable hashTable(10); // Создаем хэш-таблицу размером 10

    // создаем пользователей
    hashTable.insert(User(1, "Женя"));
    hashTable.insert(User(2, "Аня"));
    hashTable.insert(User(12, "Саша")); // Коллизия с id=2
    hashTable.insert(User(3, "Ира"));

    // Вывод хэш-таблицы
    cout << "Hash Table:" << endl;
    hashTable.print();

    // Поиск пользователя
    int id = 0;
    if (hashTable.find("Аня", id)) {
        cout << "User found: " << id << endl;
    }
    else {
        cout << "User not found." << endl;
    }

    // Удаление пользователя
    if (hashTable.remove("Аня")) {
        cout << "User with name Аня removed." << endl;
    }
    else {
        cout << "User not found for removal." << endl;
    }
    return 0;
}
