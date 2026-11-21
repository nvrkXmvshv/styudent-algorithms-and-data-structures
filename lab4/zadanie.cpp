#include <iostream>

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* next;
        Node* prev;
        Node(int val) : data(val), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Метод для добавления элемента в конец (для тестирования)
    void push_back(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // --- МЕТОД ПРОВЕРКИ НА ПАЛИНДРОМ ---
    bool isPalindrome() {
        if (head == nullptr || head == tail) {
            return true;
        }

        Node* left = head;
        Node* right = tail;

        // Условие left != right для нечетных, left->prev != right для четных
        while (left != right && left->prev != right) {
            if (left->data != right->data) {
                return false;
            }
            left = left->next;
            right = right->prev;
        }
        return true;
    }

    // Деструктор
    ~DoublyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    // Тест 1: Палиндром
    DoublyLinkedList list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    list1.push_back(2);
    list1.push_back(1);
    
    std::cout << "List 1 is palindrome: " 
              << (list1.isPalindrome() ? "Yes" : "No") << std::endl;

    // Тест 2: Не палиндром
    DoublyLinkedList list2;
    list2.push_back(1);
    list2.push_back(2);
    list2.push_back(3);
    list2.push_back(4);

    std::cout << "List 2 is palindrome: " 
              << (list2.isPalindrome() ? "Yes" : "No") << std::endl;

    return 0;
}