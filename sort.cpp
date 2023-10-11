#include <pthread.h>
#include <iostream>

struct args {
    int* array;
    int start;
    int end;
};

void* insertion_sort(void* input) {
    int* array = ((struct args*)input)->array;
    int start = ((struct args*)input)->start;
    int end = ((struct args*)input)->end;
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
    pthread_exit(0);
}

void merge(int* array, int start_l, int start_r, int end) {
    int left = start_l;
    int right = start_r;

    int temp[end - start_l];
    size_t i = 0;

    while (left != start_r && right != end) {
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

void TimSort(int* array, size_t size) {
    size_t run = 4;
    pthread_t tid[4];

    for (size_t i = 0; i < size; i += run) {
        struct args* data = (struct args*)malloc(sizeof(struct args));
        data->array = array;
        data->start = i;
        data->end = std::min(i + run, size);
        pthread_create(&tid[i], NULL, insertion_sort, data);
    }

    for (size_t i = 0; i < size; i += run) {
        pthread_join(tid[i], NULL);
    }

    for (size_t mergeSize = run; mergeSize < size; mergeSize *= 2) {
        for (size_t start_l = 0; start_l < size; start_l += 2 * mergeSize) {
            int start_r = start_l + mergeSize;
            int end = std::min(start_l + 2 * mergeSize, size);

            if (end > start_r) {
                merge(array, start_l, start_r, end);
            }
        }
    }
}

void printArr(int* a, size_t size) {
    std::cout << "[ ";
    for (size_t i = 0; i != size - 1; ++i) {
        std::cout << a[i] << ", ";
    }
    std::cout << a[size - 1] << " ]\n";
}

int main() {
    int a[10] = {4, 3, 2, 1, 4, 3, 2, 1, 1, 1};
    TimSort(a, 10);
    printArr(a, 10);
}