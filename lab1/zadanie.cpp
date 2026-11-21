#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Employee {
private:
    string name;
    string position;
    double salary;

public:

    static int count;

    Employee(const string& n, const string& pos, double sal) 
        : name(n), position(pos), salary(sal) {
        count++;
        cout << "Создан сотрудник \"" << name << "\"" << endl;
    }

    ~Employee() {
        count--;
        cout << "Удалён сотрудник \"" << name << "\"" << endl;
    }


    string getName() const { return name; }

    void print() const {
        cout << " - " << name << ", должность: " << position 
             << ", оклад: " << salary << " руб." << endl;
    }
};

int Employee::count = 0;

class Department {
private:
    string name;
    vector<Employee*> employees; 

public:
    Department(const string& n) : name(n) {
        cout << "Создан отдел \"" << name << "\"" << endl;
    }

    ~Department() {
        cout << "Удалён отдел \"" << name << "\"" << endl;
    }

    void addEmployee(Employee* emp) {
        employees.push_back(emp);
        cout << "Сотрудник \"" << emp->getName() 
             << "\" добавлен в отдел \"" << name << "\"" << endl;
    }

    void print() const {
        cout << "Отдел \"" << name << "\" содержит:" << endl;
        for (const auto* emp : employees) {
            emp->print();
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    Employee e1("Иванов И.И.", "Менеджер", 50000);
    Employee e2("Петров П.П.", "Разработчик", 80000);
    Employee e3("Сидоров С.С.", "Директор", 120000);

    cout << "\nТекущее количество сотрудников: " << Employee::count << "\n" << endl;

    {
        Department dept("IT-отдел");
        dept.addEmployee(&e1);
        dept.addEmployee(&e2);
        dept.print();
        
        cout << "\nКоличество сотрудников внутри блока: " << Employee::count << "\n" << endl;
    } 

    cout << "--- Отдел уничтожен ---" << endl;
    cout << "Сотрудники всё ещё существуют! Текущее количество: " << Employee::count << "\n" << endl;

    e1.print();
    e2.print();

    cout << "\nПри выходе из main будут удалены все сотрудники..." << endl;

    return 0;
}