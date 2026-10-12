// 1.

#define _CRT_SECURE_NO_WARNNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DG 0
#define GG 500

typedef struct lista {
	int x;
	struct lista* sljedeci;
} LIST;

void rand_array(int array[], int n);
LIST* pop_listu(int array[], int n);
int sekv_pret_array(int array[], int n, int x);
int sekv_pret_lista(LIST* head, int x);

int main() {
    
	int n = 1000000;
	int x = 2000;
	
	int* array = NULL;
	array = (int*)malloc(n * sizeof(int));

	srand((unsigned)time(NULL));

	time_t t1, t2;

	t1 = clock();
	rand_array(array, n);
	t2 = clock();

	printf("Formiranje niza: %d ms\n", t2 - t1);

	t1 = clock();
	LIST* head = pop_listu(array, n);
	t2 = clock();

	printf("Formiranje povezane liste: %d ms\n", t2 - t1);

	t1 = clock();
	int pron_el = sekv_pret_array(array, n, x);
	t2 = clock();

	printf("Pretrazivanje niza: %d ms\n", (t2 - t1));

	t1 = clock();
	int pron_elem = sekv_pret_lista(head, x);
	t2 = clock();

	printf("Pretrazivanje povezane liste: %d ms", (t2 - t1));

	return 0;
}



void rand_array(int array[], int n) {
	for (int i = 0; i < n; i++) {
		array[i] = DG + (float)rand() / RAND_MAX * (GG - DG);
	}
}

LIST* pop_listu(int array[], int n) {
	LIST* p = NULL;
	LIST* head = NULL;
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			head = (LIST*)malloc(sizeof(LIST));
			p = head;
		}
		else {
			p->sljedeci = (LIST*)malloc(sizeof(LIST));
			p = p->sljedeci;
		}
		p->x = array[i];
	}
	p->sljedeci = NULL;
	return head;
}

int sekv_pret_array(int array[], int n, int x) {
	for (int i = 0; i < n; i++) {
		if (array[i] == x) {
			return i;
			break;
		}
		if (i == n) {
			return -1;
			break;
		}
	}
}

int sekv_pret_lista(LIST* head, int x) {
	LIST* p = head;
	int br = 0;
	while (p != NULL) {
		if (p->x == x)
		{
			return br;
			break;
		}
		else if (p->x != x) {
			p = p->sljedeci;
			br++;
		}
		else {
			return -1;
			break;
		}
  }
}

// 2.

#define _CRT_SECURE_NO_WARNINGS

#define RAM_SIZE_GB 16 
#define RESERVED_MEMORY_GB 8.7
#define AVAILABLE_MEMORY_GB (RAM_SIZE_GB - RESERVED_MEMORY_GB)
#define BYTES_PER_INT 4

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long maksimalni_broj_elemenata_niza() {
    long long available_memory_bytes = (long long)(AVAILABLE_MEMORY_GB * 1024 * 1024 * 1024);
    long long max_elements = available_memory_bytes / BYTES_PER_INT;
    return max_elements;
}

long long maksimalni_broj_elemenata_povezanog_popisa() {
    int size_of_pointer = sizeof(void*);
    int size_of_node = BYTES_PER_INT + size_of_pointer;

    long long available_memory_bytes = (long long)(AVAILABLE_MEMORY_GB * 1024 * 1024 * 1024);
    long long max_elements = available_memory_bytes / size_of_node;

    return max_elements;
}

int main() {
    long long max_elements_array = maksimalni_broj_elemenata_niza();
    printf("Najveći mogući niz: %lld\n", max_elements_array);

    long long max_elements_linked_list = maksimalni_broj_elemenata_povezanog_popisa();
    printf("Najveći mogući povezani popis: %lld\n", max_elements_linked_list);

    return 0;
}
