#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node* next;
}*radix[10];

//struct node* radix[10];

void init() {
    for (int i = 0; i < 10; i++) {
        radix[i] = NULL;
    }
}

struct node* make_new_node(int data) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->next = NULL;
    new_node->data = data;
    return new_node;
}

int get_max_digit(int* arr, int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    int count = 0;
    while (max > 0) {
        max /= 10;
        count++;
    }
    return count;
}

void insert_into_bin(int data, int rad) {
    struct node* new_node = make_new_node(data);
    struct node* temp = radix[rad];
    if (temp == NULL) {
        radix[rad] = new_node;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void radix_sort(int* arr, int n) {
    int max_digits = get_max_digit(arr, n);
    int div = 1;
    
    for (int i = 0; i < max_digits; i++) {
        for (int j = 0; j < n; j++) {
            int digit = (arr[j] / div) % 10;
            insert_into_bin(arr[j], digit);
        }
        
        int index = 0;
        for (int k = 0; k < 10; k++) {
            struct node* temp = radix[k];
            while (temp != NULL) {
                arr[index++] = temp->data;
                temp = temp->next;
            }
            // Free the linked list nodes after processing
            while (radix[k] != NULL) {
                temp = radix[k];
                radix[k] = radix[k]->next;
                free(temp);
            }
        }
        
        div *= 10;
    }
}

void display(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[6] = { 655, 12, 7845, 2, 45, 45122 };
    int n = sizeof(arr) / sizeof(arr[0]);
    
    init();
    radix_sort(arr, n);
    display(arr, n);
    
    return 0;
}
