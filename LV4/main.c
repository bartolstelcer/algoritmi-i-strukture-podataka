#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
 
typedef struct SLOVO {
    char c;
    struct SLOVO* left;
    struct SLOVO* right;
} slovo;
 
slovo* root = NULL, * parent = NULL;
 
int nadji_p(char c) {
    
    int flag = 0;
    slovo* slovo_t = root;
    parent = NULL;
    
    if (slovo_t == NULL) {
        return -1;
    }
    
    while (1) {
        if (slovo_t->c == c) {
            flag = 1;
        }
        else {
            parent = slovo_t;
            if (slovo_t->c > c)
            {
                if (slovo_t->left != NULL)slovo_t = slovo_t->left;
                else flag = -1;
            }
            else if (slovo_t->right != NULL)slovo_t = slovo_t->right;
            else flag = -1;
        }
        if (flag == 1 || flag == -1) break;
    }
    return flag;
}

void dodaj_p(char c) {
    
    slovo* novi;
    int flag = 0;
    flag = nadji_p(c);
    
    if (flag == 1) { 
        return;
    }
    else {
        novi = (slovo*)malloc(sizeof(slovo));
        novi->c = c;
        novi->left = novi->right = NULL;
        if (parent == NULL) {
            root = novi;
        }
        else {
            if (parent->c > novi->c) {
                parent->left = novi;
            }
            else {
                parent->right = novi;
            }
        }
    }
}

void preorder(slovo* root) {
    
    if (root == NULL) {
        return;
    }
    else {
        printf("%c", root->c);
        preorder(root->left);
        preorder(root->right);
    }
}
 
void inorder(slovo* root) {
    
    if (root == NULL) {
        return;
    }
    else {
        inorder(root->left);
        printf("%c", root->c);
        inorder(root->right);
    }
}

void postorder(slovo* root) {
    
    if (root == NULL) {
        return;
    }
    else{
        postorder(root->left);
        postorder(root->right);
        printf("%c", root->c);
    }
}
 
int main() {
    
    char ime_prez[] = { 'B', 'A', 'R', 'T', 'O', 'L', 'S', 'T', 'E', 'L', 'C', 'E', 'R', '\0'};
    
    for (int i = 0; ime_prez[i] != '\0'; i++) {
        dodaj_p(ime_prez[i]);
    }
    
    printf("Preorder: ");
    preorder(root);
    printf("\nInorder: ");
    inorder(root);
    printf("\nPostorder: ");
    postorder(root);
}
