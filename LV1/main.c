#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sekvencijalno(int niz[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (niz[i] == x)
            return i;
    }
    return -1;
}

int usporedi(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int binarno(int niz[], int n, int x) {
    int l = 0, d = n - 1;

    while (l <= d) {
        int s = (l + d) / 2;

        if (niz[s] == x)
            return s;
        else if (niz[s] < x)
            l = s + 1;
        else
            d = s - 1;
    }
    return -1;
}

int main() {
    int n;

    printf("Unesite broj elemenata niza: ");
    scanf("%d", &n);

    int *niz = (int*)malloc(n * sizeof(int));

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        niz[i] = rand() % 100000;
    }

    int trazeni = niz[n / 2];

    clock_t start, end;
    start = clock();
    sekvencijalno(niz, n, trazeni);
    end = clock();
    double t_sekv = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;

    start = clock();
    qsort(niz, n, sizeof(int), usporedi);
    end = clock();
    double t_sort = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;

    start = clock();
    binarno(niz, n, trazeni);
    end = clock();
    double t_bin = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;

    printf("Sekvencijalno pretrazivanje: %.4f ms\n", t_sekv);
    printf("Sortiranje: %.4f ms\n", t_sort);
    printf("Binarno pretrazivanje: %.4f ms\n", t_bin);

    free(niz);
    return 0;
}
