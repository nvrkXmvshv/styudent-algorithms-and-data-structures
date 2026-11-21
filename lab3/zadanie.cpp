#include <iostream>
#include <utility> 
#include <stdexcept>

using namespace std;

class Vector {
private:
    int* data;      
    size_t size;   
    size_t capacity; 

    void reallocate(size_t new_capacity) {
        int* new_data = new int[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:

    Vector() : data(nullptr), size(0), capacity(0) {}

    Vector(size_t initial_size, int value = 0) : size(initial_size), capacity(initial_size) {
        data = new int[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = value;
        }
    }

    ~Vector() {
        delete[] data;
        cout << "Деструктор: память освобождена." << endl;
    }

    Vector(const Vector& other) : size(other.size), capacity(other.capacity) {
        data = new int[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        cout << "Конструктор копирования вызван." << endl;
    }

    Vector(Vector&& other) noexcept 
        : data(other.data), size(other.size), capacity(other.capacity) {

        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
        cout << "Конструктор перемещения вызван." << endl;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) { 
            Vector temp(other); 
            swap(temp);         
        } // <--- ИСПРАВЛЕНО: добавлена закрывающая скобка
        cout << "Оператор копирующего присваивания вызван." << endl;
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data; 
            
            data = other.data;
            size = other.size;
            capacity = other.capacity;

            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        cout << "Оператор перемещающего присваивания вызван." << endl;
        return *this;
    }

    void swap(Vector& other) noexcept {
        std::swap(data, other.data);
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
    }

    void push_back(int value) {
        if (size >= capacity) {
            size_t new_cap = (capacity == 0) ? 1 : capacity * 2;
            reallocate(new_cap);
        }
        data[size++] = value;
    }

    Vector concat(const Vector& other) const {
        Vector result;

        result.capacity = this->size + other.size;
        result.data = new int[result.capacity];
        
        for (size_t i = 0; i < this->size; ++i) {
            result.data[i] = this->data[i];
        }

        for (size_t i = 0; i < other.size; ++i) {
            result.data[this->size + i] = other.data[i];
        }
        result.size = this->size + other.size;
        
        return result;
    }

    void print() const {
        cout << "[ ";
        for (size_t i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
        cout << "]" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    cout << "--- Создание векторов ---" << endl;
    Vector v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    cout << "Вектор v1: ";
    v1.print();

    Vector v2;
    v2.push_back(4);
    v2.push_back(5);
    cout << "Вектор v2: ";
    v2.print();

    cout << "\n--- Тест метода concat ---" << endl;
    Vector v3 = v1.concat(v2);
    cout << "Вектор v3 (результат v1.concat(v2)): ";
    v3.print();

    cout << "\n--- Тест конструктора копирования ---" << endl;
    Vector v4 = v3; 
    cout << "Вектор v4 (копия v3): ";
    v4.print();

    cout << "\n--- Тест конструктора перемещения ---" << endl;
    Vector v5 = std::move(v4);
    cout << "Вектор v5 (перемещенный v4): ";
    v5.print();
    
    cout << "\n--- Конец программы (вызов деструкторов) ---" << endl;
    return 0;
}