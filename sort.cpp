#include <pthread.h>
#include <iostream>

typedef struct args_ins {
    int* array;
    int start;
    int end;
} args_ins_t;

typedef struct args_merge {
    int* array;
    int start_l;
    int start_r;
    int end;
} args_merge_t;

void* insertion_sort(void* input) {
    int* array = ((args_ins_t*)input)->array;
    int start = ((args_ins_t*)input)->start;
    int end = ((args_ins_t*)input)->end;
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

void* merge(void* input) {
    int* array = ((args_merge_t*)input)->array;
    int start_l = ((args_merge_t*)input)->start_l;
    int start_r = ((args_merge_t*)input)->start_r;
    int end = ((args_merge_t*)input)->end;

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
        while (i != end - start_l) {
            temp[i++] = array[left++];
        }
    } else {
        while (i != end - start_l) {
            temp[i++] = array[right++];
        }
    }

    for (size_t i = start_l; i < end; ++i) {
        array[i] = temp[i - start_l];
    }
}

void TimSort(int* array, size_t size, int threads) {
    size_t run = 4;
    pthread_t tid[threads];

    for (size_t i = 0; i < size; i += run) {
        int created = 0;
        while (created != threads && i < size) {
            args_ins_t* data = (args_ins_t*)malloc(sizeof(args_ins_t));

            data->array = array;
            data->start = i;
            data->end = std::min(i + run, size);

            pthread_create(&tid[created], NULL, insertion_sort, data);
            ++created;
            i += run;
        }
        i -= run;

        for (size_t i = 0; i < threads; ++i) {
            pthread_join(tid[i], NULL);
        }
    }

    for (size_t mergeSize = run; mergeSize < size; mergeSize *= 2) {
        for (size_t start_l = 0; start_l < size; start_l += 2 * mergeSize) {
            int created = 0;

            while (created != threads && start_l < size) {
                int start_r = start_l + mergeSize;
                int end = std::min(start_l + 2 * mergeSize, size);

                if (end > start_r) {
                    args_merge_t* data = (args_merge_t*)malloc(sizeof(args_merge_t));

                    data->array = array;
                    data->start_l = start_l;
                    data->start_r = start_r;
                    data->end = end;

                    pthread_create(&tid[created], NULL, merge, data);
                }
                created++;
                start_l += 2 * mergeSize;
            }
            start_l -= 2 * mergeSize;

            for (size_t i = 0; i < threads; ++i) {
                pthread_join(tid[i], NULL);
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

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Something is wrong with the arguments\n";
        return 1;
    }

    int threads = atoi(argv[1]);

    int a[16] = {4, 3, 2, 1, 4, 3, 2, 1, 4, 3, 2, 1, 4, 3, 2, 1};
    TimSort(a, 16, threads);
    printArr(a, 16);
}