#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100

int povrh(int n, int m);
void push_stack1(int x);
void push_stack2(int x);
int pop1();
int pop2();
void povrhStog(int a, int b);

int x1 = 0;
int x2 = 0;
int stack1[N];
int stack2[N];
int stackpush1 = 0;
int stackpush2 = 0;

typedef struct oe {
    int X;
    struct oe* sljedeci;
} oe;

oe* vrh1 = NULL;
oe* vrh2 = NULL;

void push_list1(int x);
void push_list2(int x);
int pop_list1();
int pop_list2();
void povrhStogLista(int a, int b);

int main() {
    
    time_t t1, t2, t3, t4, t5, t6;
    
    int n = 4;
    int m = n / 2;
    
    printf("Broj elemenata n: %d", n);
    t1 = clock();
    printf("\nRezultat %d povrh %d / 2: %d", n, n, povrh(n, m));
    t2 = clock();
    printf("\nVrijeme rekurzije: %d ms", t2 - t1);
    t3 = clock();
    printf("\nRezultat %d povrh %d / 2: ", n, n);
    povrhStog(n, m);
    t4 = clock();
    printf("\nVrijeme sa stogom: %d ms", t4 - t3);
    t5 = clock();
    printf("\nRezultat %d povrh %d / 2: ", n, n);
    povrhStogLista(n, m);
    t6 = clock();
    printf("\nVrijeme kad je stog izveden kao PP: %d ms", t6 - t5);

    return 0;
    
}

int povrh(int n, int m){
    if (m > n) return 0;
    if (m == 0 || m == n) return 1;
    return povrh(n - 1, m - 1) + povrh(n - 1, m);
}

void push_stack1(int x){
    if (stackpush1 == N) printf("Stack overflow");
    else stack1[++stackpush1] = x;
}

void push_stack2(int x){
    if (stackpush2 == N) printf("Stack overflow");
    else stack2[++stackpush2] = x;
}

int pop1(){
    if (stackpush1 == 0) printf("Stack underflow");
    else return stack1[stackpush1--];
}

int pop2(){
    if (stackpush2 == 0) printf("Stack underflow");
    else return stack2[stackpush2--];
}

void povrhStog(int a, int b){
    push_stack1(a);
    push_stack2(b);
    int povrh = 0;

    while (stackpush1 != 0){
        a = pop1();
        b = pop2();

        if (a == b || b == 0){
            povrh++;
        } else {
            push_stack1(a - 1);
            push_stack2(b - 1);
            push_stack1(a - 1);
            push_stack2(b);
        }
    }
    printf("%d", povrh);
}

void push_list1(int x) {
    oe* novi = (oe*)malloc(sizeof(oe));
    novi->X = x;
    novi->sljedeci = vrh1;
    vrh1 = novi;
}

void push_list2(int x) {
    oe* novi = (oe*)malloc(sizeof(oe));
    novi->X = x;
    novi->sljedeci = vrh2;
    vrh2 = novi;
}

int pop_list1() {
    if (vrh1 == NULL) {
        printf("Underflow!\n");
        return -1;
    }
    oe* temp = vrh1;
    int x = temp->X;
    vrh1 = vrh1->sljedeci;
    free(temp);
    return x;
}

int pop_list2() {
    if (vrh2 == NULL) {
        printf("Underflow!\n");
        return -1;
    }
    oe* temp = vrh2;
    int x = temp->X;
    vrh2 = vrh2->sljedeci;
    free(temp);
    return x;
}

void povrhStogLista(int a, int b){
    vrh1 = NULL;
    vrh2 = NULL;

    push_list1(a);
    push_list2(b);
    int povrh = 0;

    while (vrh1 != NULL){
        a = pop_list1();
        b = pop_list2();

        if (a == b || b == 0){
            povrh++;
        } else {
            push_list1(a - 1);
            push_list2(b - 1);
            push_list1(a - 1);
            push_list2(b);
        }
    }
    printf("%d", povrh);
}
