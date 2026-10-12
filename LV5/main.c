#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int *V, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && V[left] > V[largest])
        largest = left;

    if (right < n && V[right] > V[largest])
        largest = right;

    if (largest != i) {
        swap(&V[i], &V[largest]);
        heapify(V, n, largest);
    }
}

void heap_sort(int *V, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(V, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(&V[0], &V[i]);
        heapify(V, i, 0);
    }
}

void bubble_sort(int *V, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (V[j] > V[j + 1]) {
                swap(&V[j], &V[j + 1]);
            }
        }
    }
}

void merge(int *V, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = V[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = V[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            V[k++] = L[i++];
        } else {
            V[k++] = R[j++];
        }
    }

    while (i < n1)
        V[k++] = L[i++];

    while (j < n2)
        V[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort(int *V, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(V, l, m);
        merge_sort(V, m + 1, r);
        merge(V, l, m, r);
    }
}

void generate_random_array(int *V, int n) {
    for (int i = 0; i < n; i++) {
        V[i] = rand() % 1000;
    }
}

int main() {
    
    int n = 1250;

    int *V = (int *)malloc(n * sizeof(int));
    srand(time(NULL));

    generate_random_array(V, n);

    int *V_copy1 = (int *)malloc(n * sizeof(int));
    int *V_copy2 = (int *)malloc(n * sizeof(int));

    memcpy(V_copy1, V, n * sizeof(int));
    memcpy(V_copy2, V, n * sizeof(int));

    clock_t start, end;
    double time_ms;
    
    start = clock();
    heap_sort(V, n);
    end = clock();
    time_ms = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
    printf("Heap Sort vrijeme: %f ms\n", time_ms);

    start = clock();
    bubble_sort(V_copy1, n);
    end = clock();
    time_ms = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
    printf("Bubble Sort vrijeme: %f ms\n", time_ms);

    start = clock();
    merge_sort(V_copy2, 0, n - 1);
    end = clock();
    time_ms = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
    printf("Merge Sort vrijeme: %f ms\n", time_ms);

    free(V);
    free(V_copy1);
    free(V_copy2);

    return 0;
}
