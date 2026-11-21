#include <iostream>
#include <stack>
#include <queue>
#include <deque>
#include <vector>

using namespace std;

// ==========================================
// 1. СТЕК: Удалить все нечётные элементы
// ==========================================
void taskStack() {
    cout << "--- 1. СТЕК (удаление нечетных) ---" << endl;
    stack<int> originalStack;
    
    // Заполняем стек (снизу вверх: 1, 2, 3, 4, 5)
    for (int i = 1; i <= 5; ++i) originalStack.push(i);
    
    stack<int> tempStack;
    // Извлекаем элементы и оставляем только чётные
    while (!originalStack.empty()) {
        int val = originalStack.top();
        originalStack.pop();
        if (val % 2 == 0) {
            tempStack.push(val);
        }
    }
    
    // Возвращаем элементы обратно в исходный стек, чтобы сохранить порядок
    while (!tempStack.empty()) {
        originalStack.push(tempStack.top());
        tempStack.pop();
    }
    
    // Вывод результата
    cout << "Стек после удаления нечетных: ";
    while (!originalStack.empty()) {
        cout << originalStack.top() << " ";
        originalStack.pop();
    }
    cout << "\n\n";
}

// ==========================================
// 2. ОЧЕРЕДЬ: Проверить на палиндром
// ==========================================
void taskQueue() {
    cout << "--- 2. ОЧЕРЕДЬ (проверка на палиндром) ---" << endl;
    queue<int> q1, q2;
    
    // Тест 1: Палиндром (1, 2, 3, 2, 1)
    int arr1[] = {1, 2, 3, 2, 1};
    for (int x : arr1) q1.push(x);
    
    // Тест 2: Не палиндром (1, 2, 3, 4, 5)
    int arr2[] = {1, 2, 3, 4, 5};
    for (int x : arr2) q2.push(x);
    
    auto isPalindrome = [](queue<int> q) {
        vector<int> vec;
        while (!q.empty()) {
            vec.push_back(q.front());
            q.pop();
        }
        int left = 0, right = vec.size() - 1;
        while (left < right) {
            if (vec[left] != vec[right]) return false;
            left++; right--;
        }
        return true;
    };
    
    cout << "Очередь 1 палиндром? " << (isPalindrome(q1) ? "Да" : "Нет") << endl;
    cout << "Очередь 2 палиндром? " << (isPalindrome(q2) ? "Да" : "Нет") << "\n\n";
}

// ==========================================
// 3. ДЕК: Удалить все нечётные элементы
// ==========================================
void taskDeque() {
    cout << "--- 3. ДЕК (удаление нечетных) ---" << endl;
    deque<int> dq = {10, 21, 32, 43, 54, 65}; // Исходный дек
    
    cout << "Исходный дек: ";
    for (int x : dq) cout << x << " ";
    cout << endl;
    
    // Итератор для прохода по деку
    for (auto it = dq.begin(); it != dq.end(); ) {
        if (*it % 2 != 0) {
            it = dq.erase(it); // erase возвращает итератор на следующий элемент
        } else {
            ++it;
        }
    }
    
    cout << "Дек после удаления нечетных: ";
    for (int x : dq) cout << x << " ";
    cout << "\n\n";
}

// ==========================================
// 4. ПРИОРИТЕТНАЯ ОЧЕРЕДЬ: Реализовать min-heap
// ==========================================
void taskPriorityQueue() {
    cout << "--- 4. ПРИОРИТЕТНАЯ ОЧЕРЕДЬ (min-heap) ---" << endl;
    
    // По умолчанию priority_queue в C++ - это max-heap (самый большой элемент сверху).
    // Чтобы сделать min-heap (самый маленький сверху), используются компараторы:
    
    // Вариант 1 (современный): greater<int>
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    minHeap.push(5);
    minHeap.push(2);
    minHeap.push(8);
    minHeap.push(1);
    minHeap.push(9);
    
    cout << "Извлечение из min-heap (должно идти по возрастанию): ";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    
    taskStack();
    taskQueue();
    taskDeque();
    taskPriorityQueue();
    
    return 0;
}