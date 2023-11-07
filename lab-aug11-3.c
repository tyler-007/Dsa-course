#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    int exponent;
    struct node* next;
}* head1, * head2, * head3;

// Function declarations
void input1(int degree);
void input2(int degree);
void display1();
void display2();
void multiplication();
void pop();

int main() {
    int deg1, deg2;
    printf("Enter the highest degree of the first polynomial\n");
    scanf("%d", &deg1);
    printf("Enter the highest degree of the second polynomial\n");
    scanf("%d", &deg2);
    printf("Enter the 1st polynomial:\n");
    input1(deg1);
    printf("Enter the 2nd polynomial:\n");
    input2(deg2);
    display1();
    display2();
    printf("Values input successfully, now multiplying the polynomials\n");
    multiplication();
    printf("Multiplication carried out successfully, now printing the result\n");
    pop();
    return 0;
}

void input1(int degree) {
    // Implementation for input1 function
}

void input2(int degree) {
    // Implementation for input2 function
}

void display1() {
    // Implementation for display1 function
}

void display2() {
    // Implementation for display2 function
}

void multiplication() {
    struct node* ptr1 = head1;
    while (ptr1 != NULL) {
        struct node* ptr2 = head2;
        while (ptr2 != NULL) {
            int temp_coeff = ptr1->data * ptr2->data;
            int temp_deg = ptr1->exponent + ptr2->exponent;

            struct node* result_node = (struct node*)malloc(sizeof(struct node));
            result_node->data = temp_coeff;
            result_node->exponent = temp_deg;
            result_node->next = NULL;

            if (head3 == NULL) {
                head3 = result_node;
            } else {
                struct node* temp = head3;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = result_node;
            }

            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
}

void pop() {
    struct node* o = head3;
    while (o != NULL) {
        printf("(%dx^%d)+", o->data, o->exponent);
        o = o->next;
    }
    printf("\n");
}
void reduce(struct node* head3) {
    struct node* current = head3;
    while (current != NULL) {
        struct node* runner = current->next;
        while (runner != NULL) {
            if (runner->exponent == current->exponent) {
                current->data += runner->data; // Add coefficients
                // Remove the runner node
                struct node* temp = runner;
                runner = runner->next;
                free(temp);
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
}
