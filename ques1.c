#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct node {
    float a;
    int b;
    struct node* next;
} node;


typedef struct Polynomial {
    int max_exp;
    node* head;
} Polynomial;


Polynomial* pread() {
    Polynomial* A = (Polynomial*)malloc(sizeof(Polynomial));
    A->head = (node*)malloc(sizeof(node));
    A->head->next = A->head;
    A->max_exp = 0;


    int nodes_count;
    printf("Enter number of nodes in polynomial A: ");
    scanf("%d", &nodes_count);
    printf("\n");


    node* temp = A->head;
    for (int i = 0; i < nodes_count; ++i) {
        node* last = (node*)malloc(sizeof(node));
        printf("Enter coefficient and exponents of node %d: ", (i + 1));
        scanf("%f %d", &last->a, &last->b);


        temp->next = last;
        last->next = A->head;
        temp = last;


        if (last->b > A->max_exp) {
            A->max_exp = last->b;
        }
        printf("\n");
    }


    return A;
}


void Pwrite(Polynomial* A) {
    node* head1 = A->head->next;
    if (head1 == A->head) {
        printf("0");
    } else {
        while (head1 != A->head) {
            printf("%.2fx^%d", head1->a, head1->b);
            head1 = head1->next;
            if (head1 != A->head) {
                printf(" + ");
            }
        }
    }
    printf("\n");
}


Polynomial* Padd(Polynomial* head2, Polynomial* head3) {
    Polynomial* var1 = (Polynomial*)malloc(sizeof(Polynomial));
    var1->head = (node*)malloc(sizeof(node));
    var1->head->next = var1->head;
    var1->max_exp = 0;


    node* head1 = head2->head->next;
    node* last = head3->head->next;
    node* temp = var1->head;


    while (head1 != head2->head || last != head3->head) {
        node* node = (struct node*)malloc(sizeof(node));
        node->next = var1->head;


        if (head1->b > last->b) {
            node->a = head1->a;
            node->b = head1->b;
            head1 = head1->next;
        } else if (last->b > head1->b) {
            node->a = last->a;
            node->b = last->b;
            last = last->next;
        } else {
            node->a = head1->a + last->a;
            node->b = head1->b;
            head1 = head1->next;
            last = last->next;
        }


        temp->next = node;
        temp = node;


        if (node->b > var1->max_exp) {
            var1->max_exp = node->b;
        }
    }


    return var1;
}


Polynomial* Psub(Polynomial* head2, Polynomial* head3) {
    Polynomial* var1 = (Polynomial*)malloc(sizeof(Polynomial));
    var1->head = (node*)malloc(sizeof(node));
    var1->head->next = var1->head;
    var1->max_exp = 0;


    node* head1 = head2->head->next;
    node* last = head3->head->next;
    node* temp = var1->head;


    while (head1 != head2->head || last != head3->head) {
        node* node = (struct node*)malloc(sizeof(node));
        node->next = var1->head;


        if (head1->b > last->b) {
            node->a = head1->a;
            node->b = head1->b;
            head1 = head1->next;
        } else if (last->b > head1->b) {
            node->a = -last->a;
            node->b = last->b;
            last = last->next;
        } else {
            node->a = head1->a - last->a;
            node->b = head1->b;
            head1 = head1->next;
            last = last->next;
        }


        temp->next = node;
        temp = node;


        if (node->b > var1->max_exp) {
            var1->max_exp = node->b;
        }
    }


    return var1;
}


Polynomial* Pmult(Polynomial* head2, Polynomial* head3) {
    Polynomial* var1 = (Polynomial*)malloc(sizeof(Polynomial));
    var1->head = (node*)malloc(sizeof(node));
    var1->head->next = var1->head;
    var1->max_exp = 0;


    node* head1 = head2->head->next;


    while (head1 != head2->head) {
        node* last = head3->head->next;
        while (last != head3->head) {
            node* node = (struct node*)malloc(sizeof(node));
            node->next = var1->head;
            node->a = head1->a * last->a;
            node->b = head1->b + last->b;


            node* temp = var1->head;
            while (temp->next != var1->head && temp->next->b > node->b) {
                temp = temp->next;
            }


            node->next = temp->next;
            temp->next = node;


            if (node->b > var1->max_exp) {
                var1->max_exp = node->b;
            }


            last = last->next;
        }
        head1 = head1->next;
    }


    return var1;
}


float Zeval(Polynomial* A, float x) {
    float temp = 0.0;
    node* last = A->head->next;


    while (last != A->head) {
        temp += last->a * pow(x, last->b);
        last = last->next;
    }


    return temp;
}


void Perase(Polynomial* A, int b) {
    node* head1 = A->head->next;
    node* last = A->head;


    while (head1 != A->head) {
        if (head1->b == b) {
            last->next = head1->next;
            free(head1);
            head1 = last->next;
        } else {
            last = head1;
            head1 = head1->next;
        }
    }
}


int main() {
    Polynomial* head2 = pread();
    Polynomial* head3 = pread();


    printf("Polynomial A: ");
    Pwrite(head2);
    printf("Polynomial B: ");
    Pwrite(head3);


    Polynomial* tot = Padd(head2, head3);
    printf("Sum (A + B): ");
    Pwrite(tot);


    Polynomial* diff = Psub(head2, head3);
    printf("Difference (A - B): ");
    Pwrite(diff);


    Polynomial* prod = Pmult(head2, head3);
    printf("Product (A * B): ");
    Pwrite(prod);


    float x;
    printf("Write a value at which you wvar1 to evaluate the polynomials: ");
    scanf("%f", &x);
    printf("\n");
    printf("Evaluation of Polynomial A at %.2f: %.2f\n", x, Zeval(head2, x));
    printf("Evaluation of Polynomial B at %.2f: %.2f\n", x, Zeval(head3, x));


    int b;
    printf("Write the exponent of node you wvar1 to remove from Polynomial A: ");
    scanf("%d", &b);
    Perase(head2, b);
    printf("\nPolynomial A after erasing node with exponent %d: ", b);
    Pwrite(head2);
    printf("\n");
    printf("Enter the exponent of node you wvar1 to erase from polynomial B: ");
    scanf("%d", &b);
    Perase(head3, b);
    printf("Polynomial B after erasing node with exponent %d: ", b);
    Pwrite(head3);


    node* temp = head2->head->next;
    while (temp != head2->head) {
        node* last = temp;
        temp = temp->next;
        free(last);
    }
    free(head2->head);
    free(head2);


    temp = head3->head->next;
    while (temp != head3->head) {
        node* last = temp;
        temp = temp->next;
        free(last);
    }
    free(head3->head);
    free(head3);


    temp = tot->head->next;
    while (temp != tot->head) {
        node* last = temp;
        temp = temp->next;
        free(last);
    }
    free(tot->head);
    free(tot);


    temp = diff->head->next;
    while (temp != diff->head) {
        node* last = temp;
        temp = temp->next;
        free(last);
    }
    free(diff->head);
    free(diff);


    temp = prod->head->next;
    while (temp != prod->head) {
        node* last = temp;
        temp = temp->next;
        free(last);
    }
    free(prod->head);
    free(prod);


    return 0;
}
