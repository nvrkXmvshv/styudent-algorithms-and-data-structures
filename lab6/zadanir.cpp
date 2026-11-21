#include <iostream>
#include <vector>

using namespace std;

// ==========================================
// 1. ПУЗЫРЬКОВАЯ СОРТИРОВКА (Bubble Sort)
// ==========================================
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // Оптимизация: если обменов не было, массив уже отсортирован
    }
}

// ==========================================
// 2. СОРТИРОВКА ВСТАВКАМИ (Insertion Sort)
// ==========================================
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        // Сдвигаем элементы, которые больше key, на одну позицию вправо
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// ==========================================
// 3. ОБЫЧНАЯ СОРТИРОВКА ВЫБОРОМ (Selection Sort)
// ==========================================
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Обмен местами (может нарушить устойчивость)
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// ==========================================
// 4. УСТОЙЧИВАЯ СОРТИРОВКА ВЫБОРОМ (Stable Selection Sort)
// ==========================================
void stableSelectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Вместо swap мы сохраняем минимальный элемент
        int key = arr[minIndex];
        // Сдвигаем все элементы вправо до позиции i
        while (minIndex > i) {
            arr[minIndex] = arr[minIndex - 1];
            minIndex--;
        }
        // Вставляем минимальный элемент на его законное место
        arr[i] = key;
    }
}

// Вспомогательная функция для вывода массива
void printArray(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "ru");

    // Массив для теста (включая одинаковые элементы для проверки устойчивости)
    vector<int> original = {64, 25, 12, 22, 11, 12, 90, 5};

    cout << "Исходный массив: ";
    printArray(original);

    // 1. Пузырьковая
    vector<int> arr1 = original;
    bubbleSort(arr1);
    cout << "\n1. Пузырьковая сортировка: ";
    printArray(arr1);

    // 2. Вставками
    vector<int> arr2 = original;
    insertionSort(arr2);
    cout << "2. Сортировка вставками:   ";
    printArray(arr2);

    // 3. Выбором (обычная)
    vector<int> arr3 = original;
    selectionSort(arr3);
    cout << "3. Обычная сортировка выбором: ";
    printArray(arr3);

    // 4. Выбором (устойчивая)
    vector<int> arr4 = original;
    stableSelectionSort(arr4);
    cout << "4. Устойчивая сортировка выбором: ";
    printArray(arr4);

    return 0;
}