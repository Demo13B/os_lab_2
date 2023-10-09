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

void merge(int* array, int start, int end) {
    int left = start;
    int right = (start + end) / 2;

    int temp[end - start];
    size_t i = 0;

    while (left != (start + end) / 2 && right != end) {
        if (array[left] <= array[right]) {
            temp[i++] = array[left++];
        } else {
            temp[i++] = array[right++];
        }
    }

    if (right == end) {
        while (i != end) {
            temp[i++] = array[left++];
        }
    } else {
        while (i != end) {
            temp[i++] = array[right++];
        }
    }

    for (size_t i = 0; i < end; ++i) {
        array[i] = temp[i];
    }
}

int main() {
    int a[8] = {4, 3, 2, 1, 4, 3, 2, 1};
    insertion_sort(a, 0, 4);
    printArr(a, 8);
    insertion_sort(a, 4, 8);
    printArr(a, 8);
    merge(a, 0, 8);
    printArr(a, 8);
}