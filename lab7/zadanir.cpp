#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;
using namespace std::chrono;

// ==========================================
// СОРТИРОВКА СЛИЯНИЕМ (Merge Sort)
// ==========================================

// Функция слияния двух отсортированных половин
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Создаем временные массивы
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Сливаем обратно в arr
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Копируем оставшиеся элементы
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Основная рекурсивная функция
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    // Оптимизация для почти отсортированных массивов:
    // Если последний элемент левой части меньше или равен первому элементу правой,
    // значит, массив уже отсортирован, сливать не нужно.
    if (arr[mid] <= arr[mid + 1]) return;

    merge(arr, left, mid, right);
}

// ==========================================
// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
// ==========================================

// Функция для вывода массива (выводим только часть, если массив большой)
void printArray(const vector<int>& arr, const string& label) {
    cout << label << " (первые 15 элементов): ";
    int size = min((int)arr.size(), 15);
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    if (arr.size() > 15) cout << "...";
    cout << endl;
}

// Генерация почти отсортированного массива
// Берем отсортированный массив и делаем пару случайных перестановок соседних элементов
vector<int> generateNearlySorted(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) arr[i] = i; // Уже отсортирован

    random_device rd;
    mt19937 g(rd());

    // Делаем около 5% случайных перестановок соседних элементов
    int swaps = size * 0.05; 
    for (int i = 0; i < swaps; i++) {
        int idx = rand() % (size - 1);
        swap(arr[idx], arr[idx + 1]);
    }
    return arr;
}

// Замер времени
template <typename Func>
long long measureTime(Func func, vector<int>& arr) {
    auto start = high_resolution_clock::now();
    func(arr, 0, arr.size() - 1);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(0));

    // 1. Тест на маленьком массиве
    cout << "--- Тест 1: Малый массив ---" << endl;
    vector<int> smallArr = {38, 27, 43, 3, 9, 82, 10};
    printArray(smallArr, "До сортировки: ");
    mergeSort(smallArr, 0, smallArr.size() - 1);
    printArray(smallArr, "После сортировки: ");
    cout << endl;

    // 2. Тест на почти отсортированном массиве
    cout << "--- Тест 2: Почти отсортированный массив ---" << endl;
    int n = 10000; // Размер массива
    vector<int> nearlySorted = generateNearlySorted(n);
    
    printArray(nearlySorted, "До сортировки: ");
    
    long long timeNearlySorted = measureTime(mergeSort, nearlySorted);
    
    printArray(nearlySorted, "После сортировки: ");
    
    // Проверка, что массив действительно отсортирован
    if (is_sorted(nearlySorted.begin(), nearlySorted.end())) {
        cout << "Массив успешно отсортирован!" << endl;
    }
    cout << "Время сортировки почти отсортированного массива (" << n << " элементов): " 
         << timeNearlySorted << " мкс.\n\n";

    // 3. Тест на случайном массиве (для сравнения)
    cout << "--- Тест 3: Случайный массив (для сравнения) ---" << endl;
    vector<int> randomArr(n);
    for (int i = 0; i < n; i++) randomArr[i] = rand() % n;

    long long timeRandom = measureTime(mergeSort, randomArr);
    cout << "Время сортировки случайного массива (" << n << " элементов): " 
         << timeRandom << " мкс." << endl;

    return 0;
}