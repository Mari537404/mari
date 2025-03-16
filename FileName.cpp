#include<iostream>
#include<string>
#include<list>
#include<vector>

using namespace std;

struct User
{
    int id;
    string name;

    User(int id, const string& name) : id(id), name(name) {}//������� �����������
};
class HashTable {
private:
    vector<list<User>> table; //������ ������� ��� �������� ������
    size_t size; // ������ ���-�������
    int count; // ���������� ��������� � ���-�������

         // ���-������� (�������������� �����������)
    int hashFunction(const string& key) {
        int hash = 0;
        int p = 31; // ������� �����
        int p_pow = 1;

        for (char c : key) {
            hash += (c - 'a' + 1) * p_pow; // ����������� ������ � �����
            p_pow *= p; // ����������� �������
        }
        return hash % size; // ���������� ������
    }
public:
    HashTable(size_t size = 10) : size(size) {//�����������
        table.resize(size);
    }


    // ���������� ������
    int getIndex(string name) {// �������� ������ �� �����
        return hashFunction(name);
    }
    // �������������
    void rehash() {
        size_t oldSize = size;
        size *= 2; // ����������� ������ ���-������� � 2 ����
        vector<list<User>> oldTable = table;
        table.clear();//�������� ��-��� �� ������� �������
        table.resize(size);
        count = 0; // ����� �������� 
        // ��������� �������� � ����� �������
        for (int i = 0; i < oldSize; ++i) {
            for (const auto& i : oldTable[i]) {
                insert(i); // ��������� �������� ������
            }
        }
    }

public:
    HashTable(int initialSize) : size(initialSize), count(0) {
        table.resize(size);
    }

    // ����� ������� ��������
    void insert(const User& user) {
        if (count >= size * 0.7) { // ���� �������� ������ 70%, ����������
            rehash();
        }
        int index = getIndex(user.name);
        table[index].push_back(user); // ��������� ��-� � ��������������� ������
        count++; // ����������� ������� ��-��� � ������
    }

    // ����� ������ ��������
    bool find(string name, int& id) {
        int index = getIndex(name);
        for (const auto& user : table[index]) {
            if (user.name == name) {
                id = user.id; // ������� id ������������
                return true; // id ������
            }
        }
        return false; // id �� ������
    }

    // ����� �������� ��������
    bool remove(string name) {
        int index = getIndex(name);
        auto& userList = table[index];
        for (auto iter = userList.begin(); iter != userList.end(); ++iter) {
            if (iter->name == name) {
                userList.erase(iter); // ������� ������������
                count--; // ��������� �������
                return true; // ������� �������
            }
        }
        return false; // ������������ �� ������ ��� ��������
    }

    // ����� ������ ���-�������
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
    HashTable hashTable(10); // ������� ���-������� �������� 10

    // ������� �������������
    hashTable.insert(User(1, "����"));
    hashTable.insert(User(2, "���"));
    hashTable.insert(User(12, "����")); // �������� � id=2
    hashTable.insert(User(3, "���"));

    // ����� ���-�������
    cout << "Hash Table:" << endl;
    hashTable.print();

    // ����� ������������
    int id = 0;
    if (hashTable.find("���", id)) {
        cout << "User found: " << id << endl;
    }
    else {
        cout << "User not found." << endl;
    }

    // �������� ������������
    if (hashTable.remove("���")) {
        cout << "User with name ��� removed." << endl;
    }
    else {
        cout << "User not found for removal." << endl;
    }
    return 0;
}
