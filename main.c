#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 2 
#define ARRAY_SIZE 12  

int arr[ARRAY_SIZE] = {12, 11, 13, 5, 6, 7, 18, 9, 4, 2, 15, 8};

void bubbleSort(int start, int end) {
    for (int i = start; i < end; i++) {
        for (int j = start; j < end - i - 1 + start; j++) {
            if (arr[j] > arr[j + 1]) {

                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void* sortFirstHalf(void* arg) {
    int mid = ARRAY_SIZE / 2;
    bubbleSort(0, mid);
    return NULL;
}

void* sortSecondHalf(void* arg) {
    int mid = ARRAY_SIZE / 2;
    bubbleSort(mid, ARRAY_SIZE);
    return NULL;
}

void merge() {
    int mid = ARRAY_SIZE / 2;
    int temp[ARRAY_SIZE];
    int i = 0, j = mid, k = 0;

    while (i < mid && j < ARRAY_SIZE) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i < mid) {
        temp[k++] = arr[i++];
    }

    while (j < ARRAY_SIZE) {
        temp[k++] = arr[j++];
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = temp[i];
    }
}

int main() {
    pthread_t threads[NUM_THREADS];

    pthread_create(&threads[0], NULL, sortFirstHalf, NULL);

    pthread_create(&threads[1], NULL, sortSecondHalf, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    merge();

    printf("Sorted array: \n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
