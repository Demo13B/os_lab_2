#include <iostream>

void insertion_sort(int* array, int start, int end) {
    int current, temp, pos;

    for (size_t i = start + 1; i < end; ++i) {
        current = array[i];
        pos = i - 1;

        while (pos >= start && array[pos] > array[pos + 1]) {
            temp = array[pos];
            array[pos] = current;
            array[pos + 1] = temp;
            --pos;
        }
    }
}

void printArr(int* a, int size) {
    std::cout << "[ ";
    for (size_t i = 0; i != size - 1; ++i) {
        std::cout << a[i] << ", ";
    }
    std::cout << a[size - 1] << " ]\n";
}

int main() {
    int a[8] = {4, 3, 2, 1, 4, 3, 2, 1};
    insertion_sort(a, 4, 9);
    printArr(a, 8);
}