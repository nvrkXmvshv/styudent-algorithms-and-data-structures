#include <iostream>
#include <string>
#include <vector>

using namespace std;

class HashTable {
private:
    struct Entry {
        int key;
        string value;
        bool isDeleted;

        Entry() : key(0), value(""), isDeleted(false) {}
    };

    vector<Entry> table;
    int size;       // Текущее количество активных элементов
    int capacity;   // Общий размер массива

    // Хеш-функция (метод деления)
    int hashFunc(int key) {
        return key % capacity;
    }

    // Рехеширование (расширение таблицы)
    void rehash() {
        vector<Entry> oldTable = table;
        capacity *= 2; // Увеличиваем размер в 2 раза
        table.clear();
        table.resize(capacity);
        size = 0;

        // Пересыпаем старые элементы в новую таблицу
        for (const auto& entry : oldTable) {
            if (entry.value != "" && !entry.isDeleted) {
                insert(entry.key, entry.value);
            }
        }
    }

public:
    HashTable(int initialCapacity = 10) {
        capacity = initialCapacity;
        size = 0;
        table.resize(capacity);
    }

    // Вставка элемента
    void insert(int key, const string& value) {
        // Если таблица заполнена более чем на 70%, расширяем её
        if (size >= capacity * 0.7) {
            rehash();
        }

        int index = hashFunc(key);
        int startIndex = index;

        // Ищем свободную ячейку или ячейку, помеченную как удаленная
        while (table[index].value != "" && !table[index].isDeleted) {
            if (table[index].key == key) {
                // Если ключ уже есть, обновляем значение
                table[index].value = value;
                return;
            }
            index = (index + 1) % capacity; // Линейное пробирование
            
            // Защита от бесконечного цикла, если таблица полна
            if (index == startIndex) {
                cout << "Ошибка: таблица переполнена!" << endl;
                return;
            }
        }

        // Вставляем новый элемент
        table[index].key = key;
        table[index].value = value;
        table[index].isDeleted = false;
        size++;
    }

    // Поиск элемента по ключу
    string find(int key) {
        int index = hashFunc(key);
        int startIndex = index;

        while (table[index].value != "") {
            if (table[index].key == key && !table[index].isDeleted) {
                return table[index].value; // Нашли
            }
            index = (index + 1) % capacity;
            
            if (index == startIndex) break; // Прошли круг
        }
        return ""; // Не нашли
    }

    // Удаление элемента (ленивое удаление)
    void remove(int key) {
        int index = hashFunc(key);
        int startIndex = index;

        while (table[index].value != "") {
            if (table[index].key == key && !table[index].isDeleted) {
                table[index].isDeleted = true; // Помечаем как удаленное
                size--;
                return;
            }
            index = (index + 1) % capacity;
            
            if (index == startIndex) break;
        }
        cout << "Ключ " << key << " не найден для удаления." << endl;
    }

    // Вывод содержимого таблицы
    void print() {
        cout << "--- Хеш-таблица (Размер: " << size << ", Емкость: " << capacity << ") ---" << endl;
        for (int i = 0; i < capacity; i++) {
            cout << i << ": ";
            if (table[i].value == "") {
                cout << "[пусто]" << endl;
            } else if (table[i].isDeleted) {
                cout << "[удалено]" << endl;
            } else {
                cout << "{" << table[i].key << " : " << table[i].value << "}" << endl;
            }
        }
        cout << endl;
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    HashTable ht(10);

    cout << "--- Вставка элементов ---" << endl;
    ht.insert(10, "Десять");
    ht.insert(20, "Двадцать");
    ht.insert(15, "Пятнадцать"); // Коллизия с 20? (20 % 10 = 0, 15 % 10 = 5)
    ht.insert(25, "Двадцать пять"); // Коллизия с 15 (25 % 10 = 5)
    ht.insert(12, "Двенадцать");
    ht.print();

    cout << "--- Поиск ---" << endl;
    cout << "Поиск ключа 15: " << ht.find(15) << endl;
    cout << "Поиск ключа 25: " << ht.find(25) << endl;
    cout << "Поиск ключа 99: " << (ht.find(99) == "" ? "не найден" : ht.find(99)) << endl;
    cout << endl;

    cout << "--- Удаление ключа 20 ---" << endl;
    ht.remove(20);
    ht.print();

    cout << "--- Проверка после удаления (ленивое удаление не рвет цепочку) ---" << endl;
    cout << "Поиск ключа 10 (был до удаленного): " << ht.find(10) << endl;
    cout << "Поиск ключа 15 (после удаленного): " << ht.find(15) << endl;

    return 0;
}