#include <iostream>
#include <stdexcept>

using namespace std;


template <typename T>
T findMin(T arr[], int n) {

    if (n <= 0) {
        throw invalid_argument("Массив пуст или размер некорректен");
    }


    T minElement = arr[0];


    for (int i = 1; i < n; ++i) {
        if (arr[i] < minElement) {
            minElement = arr[i];
        }
    }

    return minElement;
}

int main() {
    setlocale(LC_ALL, "ru");

  
    int intArr[] = {5, 2, 9, 1, 7};
    int n1 = sizeof(intArr) / sizeof(intArr[0]);
    cout << "Минимальный элемент (int): " << findMin(intArr, n1) << endl;

 
    double doubleArr[] = {3.14, 1.41, 2.71, 0.58};
    int n2 = sizeof(doubleArr) / sizeof(doubleArr[0]);
    cout << "Минимальный элемент (double): " << findMin(doubleArr, n2) << endl;


    char charArr[] = {'z', 'a', 'm', 'b'};
    int n3 = sizeof(charArr) / sizeof(charArr[0]);
    cout << "Минимальный элемент (char): " << findMin(charArr, n3) << endl;

    return 0;
}